
#include "master.h"
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define END_OF_PROCESSING -1
// Function to print the world (for debugging)
void printWorld(unsigned short* world, int worldWidth, int worldHeight)
{
    for (int row = 0; row < worldHeight; row++)
    {
        for (int col = 0; col < worldWidth; col++)
        {
            printf("%d ", world[row * worldWidth + col]);
        }
        printf("\n");
    }
}

// Function to calculate worker row ranges
void calculate_worker_rows(int worldHeight, int workers, int worker_rank, int* startRow, int* endRow, int* numRowsToSend)
{
    int rowsPerWorker = worldHeight / workers;
    int extraRows = worldHeight % workers;

    // Calcular rango inicial y final básico
    *startRow = (worker_rank - 1) * rowsPerWorker;
    *endRow = *startRow + rowsPerWorker - 1;

    // Distribuir filas adicionales si hay filas extra
    if (worker_rank <= extraRows)
    {
        (*endRow)++;
    }

    // Ajustar rangos para incluir filas extra de los bordes
    if (worker_rank > 1)
    {
        (*startRow)--; // Agregar fila anterior para no cortar bordes
    }
    if (worker_rank < workers)
    {
        (*endRow)++; // Agregar fila posterior para no cortar bordes
    }

    // Asegurar que los rangos estén dentro de los límites del mundo
    *startRow = MAX(*startRow, 0);
    *endRow = MIN(*endRow, worldHeight - 1);

    // Calcular número de filas totales a enviar
    *numRowsToSend = *endRow - *startRow + 1;
}

void calculate_rows_with_grain(int worldHeight, int workers, int worker_rank, int* startRow, int* endRow, int grain) {
    *startRow = (worker_rank - 1) * grain;
    *endRow = *startRow + grain - 1;

    // Ensure the ranges are within the world's bounds
    *startRow = MAX(*startRow, 0);
    *endRow = MIN(*endRow, worldHeight - 1);
}

void distribucionDistribuida(int iterations, int worldWidth, int worldHeight, unsigned short* worldA, unsigned short* worldB, int workers, SDL_Window* window, SDL_Renderer* renderer, int automode, int grainSize) {
    printf("Comenzando la ejecución dinámica del JUEGO DE LA VIDA\n");
    MPI_Status status;
    int tag = 1;
    unsigned short* buffer = (unsigned short*)malloc(grainSize * worldWidth * sizeof(unsigned short));
    if (!buffer) {
        fprintf(stderr, "Error allocating memory for buffer\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    for (int iter = 0; iter < iterations; iter++) {
        int rowsAssigned = 0;
        int rowsProcessed = 0;

        // Asignar trabajo inicial a todos los trabajadores
        for (int i = 1; i <= workers && rowsAssigned < worldHeight; i++) {
            int startRow = rowsAssigned;
            int endRow = MIN(startRow + grainSize - 1, worldHeight - 1);
            int numRowsToSend = endRow - startRow + 1;

            memcpy(buffer, &worldA[startRow * worldWidth], numRowsToSend * worldWidth * sizeof(unsigned short));
            MPI_Send(buffer, numRowsToSend * worldWidth, MPI_UNSIGNED_SHORT, i, tag, MPI_COMM_WORLD);
            rowsAssigned += numRowsToSend;
        }

        while (rowsProcessed < worldHeight) {
            int workerRank;
            MPI_Recv(buffer, grainSize * worldWidth, MPI_UNSIGNED_SHORT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            workerRank = status.MPI_SOURCE;
            int numRowsReceived;
            MPI_Get_count(&status, MPI_UNSIGNED_SHORT, &numRowsReceived);
            numRowsReceived /= worldWidth;

            memcpy(&worldB[rowsProcessed * worldWidth], buffer, numRowsReceived * worldWidth * sizeof(unsigned short));
            rowsProcessed += numRowsReceived;

            if (rowsAssigned < worldHeight) {
                int startRow = rowsAssigned;
                int endRow = MIN(startRow + grainSize - 1, worldHeight - 1);
                int numRowsToSend = endRow - startRow + 1;

                memcpy(buffer, &worldA[startRow * worldWidth], numRowsToSend * worldWidth * sizeof(unsigned short));
                MPI_Send(buffer, numRowsToSend * worldWidth, MPI_UNSIGNED_SHORT, workerRank, tag, MPI_COMM_WORLD);
                rowsAssigned += numRowsToSend;
            }
            else {
                int endSignal = END_OF_PROCESSING;
                MPI_Send(&endSignal, 1, MPI_INT, workerRank, tag, MPI_COMM_WORLD);
            }
        }

        // Intercambiar mundos y redibujar
        unsigned short* temp = worldA;
        worldA = worldB;
        worldB = temp;

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        drawWorld(worldB, worldA, renderer, 0, worldHeight - 1, worldWidth, worldHeight);
        SDL_RenderPresent(renderer);

        if (automode == 0) {
            printf("Presiona cualquier tecla para continuar...");
            getchar();
        }
    }

    free(buffer);
    printf("Ejecución dinámica completada.\n");
}

void distribucionFicus(int iterations, int worldWidth, int worldHeight, unsigned short* worldA, unsigned short* worldB, int workers, SDL_Window* window, SDL_Renderer* renderer, int automode) {
    printf("Comenzando la ejecución estática del JUEGO DE LA VIDA\n");

    for (int iter = 0; iter < iterations; iter++) {
        // Enviar datos a los trabajadores
        for (int i = 1; i <= workers; i++) {
            int startRow, endRow, numRowsToSend;
            calculate_worker_rows(worldHeight, workers, i, &startRow, &endRow, &numRowsToSend);

            MPI_Send(&worldA[startRow * worldWidth], numRowsToSend * worldWidth, MPI_UNSIGNED_SHORT, i, 0, MPI_COMM_WORLD);
        }

        // Recibir filas procesadas de los trabajadores
        for (int i = 1; i <= workers; i++) {
            int startRow, endRow, numRowsToReceive;
            calculate_worker_rows(worldHeight, workers, i, &startRow, &endRow, &numRowsToReceive);

            MPI_Recv(&worldB[startRow * worldWidth], numRowsToReceive * worldWidth, MPI_UNSIGNED_SHORT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        // Intercambiar mundos y redibujar
        unsigned short* temp = worldA;
        worldA = worldB;
        worldB = temp;

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        drawWorld(worldB, worldA, renderer, 0, worldHeight - 1, worldWidth, worldHeight);
        SDL_RenderPresent(renderer);

        if (automode == 0) {
            printf("Presiona cualquier tecla para continuar...");
            getchar();
        }
    }

    printf("Ejecución estática completada.\n");
}

// Main master function
void mastereando(int width, int height, int sWidth, int sHeight, int iterations,
    int automode, char* output, int mode,
    SDL_Window* windoW, SDL_Renderer* windowRenderer, int grainSize)
{
    unsigned short* worldA = NULL, * worldB = NULL;
    SDL_Window* window = windoW;
    SDL_Renderer* renderer = windowRenderer;
    int worldWidth = width;
    int worldHeight = height;
    int size;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int workers = size - 1;

    // Allocate memory for the worlds
    worldA = (unsigned short*)malloc(width * height * sizeof(unsigned short));
    worldB = (unsigned short*)malloc(width * height * sizeof(unsigned short));

    if (!worldA || !worldB)
    {
        fprintf(stderr, "Error allocating memory for worlds\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // Initialize and display the initial world
    clearWorld(worldA, width, height);
    clearWorld(worldB, width, height);
    initRandomWorld(worldA, width, height);
    // printWorld(worldA, width, height);

    if (!renderer)
    {
        fprintf(stderr, "Error creating SDL renderer: %s\n", SDL_GetError());
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    drawWorld(worldB, worldA, renderer, 0, worldHeight - 1, worldWidth, worldHeight);
    SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(window);

    printf("World created (iteration 0)\n");
    printf("EL MODO ES %d\n", mode);
    printf("EL AUTOMODE ES %d\n", automode);
    /*
    automode:   step 0
                auto 1
    modo:       static 1
                dynamic 0
    */
    if (mode == 0)
    {
        distribucionDistribuida(iterations, worldWidth, worldHeight, worldA, worldB, workers, window, renderer, automode, grainSize);
    }
    else
    {
        distribucionFicus(iterations, worldWidth, worldHeight, worldA, worldB, workers, window, renderer, automode);
    }

    free(worldA);
    free(worldB);
    SDL_DestroyRenderer(renderer);
}

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
    int tag = 1; // Tag para las comunicaciones
    unsigned short* buffer = (unsigned short*)malloc(grainSize * worldWidth * sizeof(unsigned short));

    if (!buffer) {
        fprintf(stderr, "Error allocating memory for buffer\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    for (int iter = 0; iter < iterations; iter++) {
        int rowsAssigned = 0;  // Contador de filas asignadas
        int rowsProcessed = 0; // Contador de filas procesadas

        // Asignar trabajo inicial a todos los trabajadores
        for (int i = 1; i <= workers; i++) {
            int startRow, endRow;
            calculate_rows_with_grain(worldHeight, workers, i, &startRow, &endRow, grainSize);
            int numRowsToSend = endRow - startRow + 1;

            memcpy(buffer, &worldA[startRow * worldWidth], numRowsToSend * worldWidth * sizeof(unsigned short));

            printf("Sending buffer to process %d with %d elements (rows %d to %d)\n", i, numRowsToSend * worldWidth, startRow, endRow);
            MPI_Send(buffer, numRowsToSend * worldWidth, MPI_UNSIGNED_SHORT, i, tag, MPI_COMM_WORLD);

            rowsAssigned += numRowsToSend;
        }

       
        while (rowsProcessed < worldHeight) { //Mientras queden filas por procesar
          /*ASIGNAR LAS FILAS QUE QUEDAN
               Tener en cuenta que si las filas que quedan son menor que el grano hay que enviar solo las que quedan.
               */

            MPI_Recv(...); //recibimos el resultado de un worker

            rowsProcessed += numRowsToSend;

            if (rowsAssigned < worldHeight) {
                //mandamos 
            }
            else {
                numRowsToSend = END_OF_PROCESSING;
                MPI_Send(&numRowsToSend, 1, MPI_UNSIGNED_SHORT, , , MPI_COMM_WORLD);
            }
        }

        // Intercambiar mundos
        unsigned short* temp = worldA;
        worldA = worldB;
        worldB = temp;

        // Redibujar el mundo
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        drawWorld(worldB, worldA, renderer, 0, worldHeight - 1, worldWidth, worldHeight);
        SDL_RenderPresent(renderer);

        // Pausa en modo manual
        if (automode == 0) {
            printf("Presiona cualquier tecla para continuar...");
            getchar();
        }
    }

   

    free(buffer);
    printf("Ejecución dinámica completada.\n");
}

void distribucionFicus(int iterations, int worldWidth, int worldHeight, unsigned short* worldA, unsigned short* worldB, int workers, SDL_Window* window, SDL_Renderer* renderer, int automode)
{
    printf("Comenzando la ejecucion estatica del JUEGO DE LA VIDA (musica dramatica)\n");
    for (int iter = 0; iter < iterations; iter++)
    {
        // Send data to workers
        for (int i = 1; i <= workers; i++)
        {
            int startRow, endRow, numRowsToSend;
            calculate_worker_rows(worldHeight, workers, i, &startRow, &endRow, &numRowsToSend);

            unsigned short* buffer = (unsigned short*)malloc(numRowsToSend * worldWidth * sizeof(unsigned short));
            if (!buffer)
            {
                fprintf(stderr, "Error allocating memory for buffer\n");
                MPI_Abort(MPI_COMM_WORLD, 1);
            }

            memcpy(buffer, &worldA[startRow * worldWidth], numRowsToSend * worldWidth * sizeof(unsigned short));

            printf("Sending buffer to process %d with %d elements (rows %d to %d)\n",
                i, numRowsToSend * worldWidth, startRow, endRow);
            MPI_Send(buffer, numRowsToSend * worldWidth, MPI_UNSIGNED_SHORT, i, 0, MPI_COMM_WORLD);
            free(buffer);
        }

        // Receive processed rows from workers
        for (int i = 1; i <= workers; i++)
        {
            int startRow, endRow, numRowsToReceive;
            calculate_worker_rows(worldHeight, workers, i, &startRow, &endRow, &numRowsToReceive);

            unsigned short* buffer = (unsigned short*)malloc(numRowsToReceive * worldWidth * sizeof(unsigned short));
            if (!buffer)
            {
                fprintf(stderr, "Error allocating memory for buffer\n");
                MPI_Abort(MPI_COMM_WORLD, 1);
            }

            MPI_Recv(buffer, numRowsToReceive * worldWidth, MPI_UNSIGNED_SHORT, i, 0,
                MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            printf("Master received processed data from worker %d\n", i);
            memcpy(&worldB[startRow * worldWidth], buffer,
                numRowsToReceive * worldWidth * sizeof(unsigned short));
            free(buffer);
        }

        // Swap worlds
        unsigned short* temp = worldA;
        worldA = worldB;
        worldB = temp;

        // Render updated state
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        drawWorld(worldB, worldA, renderer, 0, worldHeight - 1, worldWidth, worldHeight);
        SDL_RenderPresent(renderer);
        SDL_UpdateWindowSurface(window);

        // Handle events and pause if necessary
        SDL_Event event;
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
        {
            break;
        }
        if (automode == 0)
        {
            printf("Press any key to continue...");
            getchar();
        }
    }
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
#include <iostream>
#include <fstream>
#include <vector>
#include "EnterosInf.h"  // propios o los de las estructuras de datos de clase
#include "Matriz.h"

using namespace std;

struct tCuerda {
    int longitud;
    int coste;
};

struct Solucion {
    EntInf formas;
    EntInf minimoNumCuerdas;
    EntInf minimoCoste;
};

Solucion resolver(vector<tCuerda> const& cuerdas, int L) {
    int N = cuerdas.size();
    Matriz<EntInf> formas(N + 1, L + 1, 0);
    Matriz<EntInf> minCuerdas(N + 1, L + 1, Infinito);
    Matriz<EntInf> minCoste(N + 1, L + 1, Infinito);

    // Caso base: longitud 0 se puede formar con 0 cuerdas, coste 0 y 1 forma
    for (int i = 0; i <= N; ++i) {
        formas[i][0] = 1;
        minCuerdas[i][0] = 0;
        minCoste[i][0] = 0;
    }

    // Rellenar las tablas dinámicas
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= L; ++j) {
            // Caso 1: No usar la cuerda actual
            formas[i][j] = formas[i - 1][j];
            minCuerdas[i][j] = minCuerdas[i - 1][j];
            minCoste[i][j] = minCoste[i - 1][j];

            // Caso 2: Usar la cuerda actual si cabe
            if (j >= cuerdas[i - 1].longitud) {
                // Calcular combinaciones válidas para formas
                formas[i][j] = formas[i][j] + formas[i - 1][j - cuerdas[i - 1].longitud];

                // Actualizar mínimo número de cuerdas
                EntInf nuevoNumCuerdas = minCuerdas[i - 1][j - cuerdas[i - 1].longitud] + 1;
                if (nuevoNumCuerdas < minCuerdas[i][j]) {
                    minCuerdas[i][j] = nuevoNumCuerdas;
                }

                // Actualizar mínimo coste
                EntInf nuevoCoste = minCoste[i - 1][j - cuerdas[i - 1].longitud] + cuerdas[i - 1].coste;
                if (nuevoCoste < minCoste[i][j]) {
                    minCoste[i][j] = nuevoCoste;
                }
            }
        }
    }

    Solucion sol;
    sol.formas = formas[N][L];
    sol.minimoNumCuerdas = minCuerdas[N][L];
    sol.minimoCoste = minCoste[N][L];

    return sol;
}

bool resuelveCaso() {
    int N, L;
    cin >> N;

    if (!cin) return false;  // fin de la entrada

    cin >> L;
    vector<tCuerda> cuerdas(N);

    for (int i = 0; i < N; ++i) {
        cin >> cuerdas[i].longitud >> cuerdas[i].coste;
    }

    Solucion sol = resolver(cuerdas, L);

    if (sol.formas == 0) {
        cout << "NO\n";
    }
    else {
        cout << "SI " << sol.formas << " " << sol.minimoNumCuerdas << " " << sol.minimoCoste << "\n";
    }

    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}

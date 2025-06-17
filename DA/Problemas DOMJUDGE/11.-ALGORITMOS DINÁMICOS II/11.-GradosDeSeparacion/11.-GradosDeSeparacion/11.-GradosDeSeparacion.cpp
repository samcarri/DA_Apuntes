#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <limits>
#include <string>
using namespace std;

// ================================================================
// Función para resolver el caso con optimizaciones
// ================================================================
int resolver(vector<vector<int>>& relacion, int N) {
    // Lógica de propagación de distancias
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                // Verificar si es posible una mejora en la relación

                if (relacion[i][k] != 10001 && relacion[k][j] != 10001) {
                    relacion[i][j] = min(relacion[i][j], relacion[i][k] + relacion[k][j]);
                }

            }
        }
    }

    // Buscar el mayor grado de relación
    int res = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (relacion[i][j] == 10001) return -1; // Si alguna persona es inaccesible, retornar -1
            res = max(res, relacion[i][j]); // Encontrar la relación más lejana
        }
    }

    return res; // Retornar el mayor grado de relación
}

bool resuelveCaso() {
    int N, M;
    string persona1, persona2;
    cin >> N >> M;

    if (!std::cin)  // fin de la entrada
        return false;

    // Inicializar la matriz de relaciones
    vector<vector<int>> relacion(N, vector<int>(N, 10001));
    for (int i = 0; i < N; i++) {
        relacion[i][i] = 0;  // La relación de una persona consigo misma es 0
    }

    // Usamos un vector para asociar nombres con índices
    map<string, int> personas;
    int contador = 0;

    // Rellenar las relaciones
    for (int i = 0; i < M; i++) {
        cin >> persona1 >> persona2;
        if (!personas.count(persona1)) {
            personas[persona1] = contador++;
        }
        if (!personas.count(persona2)) {
            personas[persona2] = contador++;
        }

        // Actualizar las relaciones (relación bidireccional)
        relacion[personas[persona1]][personas[persona2]] = 1;
        relacion[personas[persona2]][personas[persona1]] = 1;
    }

    // Resolver el caso
    int res = resolver(relacion, N);

    if (res == -1) {
        cout << "DESCONECTADA\n";
    }
    else {
        cout << res << "\n";
    }

    return true;
}

int main() {
    // Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // Para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}

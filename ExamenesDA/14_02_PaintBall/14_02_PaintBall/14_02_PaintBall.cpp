#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include "Grafo.h"

using namespace std;

bool esBipartito(Grafo const& grafo, int n) {
    vector<int> color(n, -1); // -1: no coloreado, 0: rojo, 1: azul
    queue<int> q;

    for (int i = 0; i < n; ++i) {
        if (color[i] == -1) { // Si el nodo no está coloreado
            color[i] = 0; // Colorear el nodo inicial con rojo
            q.push(i);

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v : grafo.ady(u)) {
                    if (color[v] == -1) { // Si el nodo vecino no está coloreado
                        color[v] = 1 - color[u]; // Colorear con el color opuesto
                        q.push(v);
                    }
                    else if (color[v] == color[u]) {
                        return false; // Si el vecino tiene el mismo color, no es bipartito
                    }
                }
            }
        }
    }
    return true;
}

bool resuelveCaso() {
    int A, R;
    cin >> A >> R;
    if (!cin) return false;

    Grafo grafo(A);
    for (int i = 0; i < R; ++i) {
        int u, v;
        cin >> u >> v;
        grafo.ponArista(u - 1, v - 1); // Convertir a índice 0
    }

    if (esBipartito(grafo, A)) {
        cout << "SI" << endl;
    }
    else {
        cout << "NO" << endl;
    }

    return true;
}
//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}

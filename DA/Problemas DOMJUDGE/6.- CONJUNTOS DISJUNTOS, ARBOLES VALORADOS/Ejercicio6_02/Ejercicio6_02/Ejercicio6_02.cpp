
/*@ <answer>
 *
 * Nombre y Apellidos:Samuel Carrillo Menchero
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include <map>

using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "PriorityQueue.h"
/*@ <answer>

Basicamente consiste en analizar nodo por nodo su grado de entrada y de salida.
Si el grado de entrada es de N-1 y el de salida es 0 entonces estamos hablando de un nodo "sumidero".

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
struct tCamion{
    int og;
    int dst;
    int anchura;
};

// visita los nodos alcanzables desde v respetando el umbral
void dfs(GrafoValorado<int> const& G, int v,int destino, int umbral, vector<bool> &visit, bool & visitado) {
    visit[v] = true;
 
    for (auto a : G.ady(v)) {
        if (a.valor() >= umbral) {
            int w = a.otro(v);
            if (!visit[w]) {
                if (w == destino) {
                    visitado = true;
                    return;
                }
                dfs(G, w, destino, umbral, visit, visitado);
            }
        }
    }
}

bool resuelveCaso() {
    int V, E, V1, V2, A, K;
    bool visitado;
    cin >> V >> E;
    // resolver el caso posiblemente llamando a otras funciones
    if (!std::cin)
        return false;
    // escribir la solución
    GrafoValorado<int> grafo(V);
    for (int i = 0; i < E; i++) {
        cin >> V1 >> V2 >> A;
        grafo.ponArista({ V1 - 1, V2 - 1, A });
    }
    //ARM_Kruskal<int> kruskal(grafo);
    cin >> K;
    for (int i = 0; i < K; i++) {
        tCamion camion;
        visitado = false;
        vector<bool> visit(V, false);
        cin >> camion.og >> camion.dst >> camion.anchura;
        dfs(grafo, camion.og-1, camion.dst-1, camion.anchura, visit, visitado);
        if (visitado) cout << "SI" << "\n";
        else cout << "NO\n";
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


/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"
#include "ConjuntosDisjuntos.h"
#include "Grafo.h"
/*@ <answer>

Cogeremos el primer valor del arbol de recubrimiento minimo para posteriormente
 @ </answer> */


class CaminosDFS {
private:
    std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
    std::vector<int> ant;    // ant[v] = último vértice antes de llegar a v
    std::vector<int> costes;
    std::vector<bool> visitado;
    int s;                   // vértice origen
    int minimo_coste;

    // Realiza DFS para marcar los caminos desde el vértice origen.
    void dfs(Grafo const& G, int v) {
        visit[v] = true; // Marca el nodo como visitado.
        visitado[v] = true;
        if (costes[v] < minimo_coste) minimo_coste = costes[v];

        for (int w : G.ady(v)) { // Itera sobre los nodos adyacentes.
            if (!visit[w]) {    // Si el nodo no está visitado, lo procesa.
                ant[w] = v;     // Registra el nodo previo.
            
                dfs(G, w);      // Llama recursivamente para explorar.
            }
        }
    }

public:
    // Constructor: inicializa y realiza DFS desde el vértice `s`.
    CaminosDFS(Grafo const& G, int s, vector<bool> &visitado, vector<int> costes)
        : visit(G.V(), false), ant(G.V()),visitado(visitado),costes(costes), s(s), minimo_coste(1000000) {
        dfs(G, s);
    }

    // Indica si hay un camino desde el origen `s` al vértice `v`.
    bool hayCamino(int v) const {
        return visit[v];
    }

    vector<bool> visiting() {
        return visitado;
    }
    int minimo() {
        return minimo_coste;
    }
    using Camino = std::deque<int>; // Alias para representar caminos.

    // Devuelve el camino desde el origen `s` al vértice `v` (debe existir).
    Camino camino(int v) const {
        if (!hayCamino(v))
            throw std::domain_error("No existe camino");

        Camino cam; // Para almacenar el camino.
        // Retrocede desde el destino hasta el origen.
        for (int x = v; x != s; x = ant[x])
            cam.push_front(x);

        cam.push_front(s); // Añade el origen al camino.
        return cam;
    }
};


int resolver(vector<int> const& costes, Grafo grafo) {
    vector<bool> visitados(costes.size(), false);
    int solucion = 0;
    for (int i = 0; i < costes.size(); i++) {
        if (!visitados[i]) {
            CaminosDFS sol(grafo, i, visitados, costes);
          
            solucion += sol.minimo();
            visitados = sol.visiting();

        }
    }

    return solucion;
}

bool resuelveCaso() {

    int N, M;
    cin >> N >> M;

    if (!std::cin)  // fin de la entrada
        return false;
    vector<int> costes(N);
    for (int i = 0; i < N; i++) {
        cin >> costes[i];
    }
    Grafo relaciones(N);
    int aux1, aux2;
    for (int i = 0; i < M; i++) {
        cin >> aux1 >> aux2;
        relaciones.ponArista(aux1 - 1, aux2 - 1);
    }
    cout << resolver(costes, relaciones) << endl;
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

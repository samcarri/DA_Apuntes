
/*@ <answer>
 *
 * Nombre y Apellidos:Samuel Carrillo Menchero
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <limits>
#include <stack>
using namespace std;

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"
#include "Grafo.h"

/*@ <answer>



 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
class CaminoMasCorto {
public:
    CaminoMasCorto(Grafo const& g, int s) : visit(g.V(), false),
        ant(g.V(), -1), dist(g.V(), -1), s(s) {
        bfs(g);
    }
    // ¿hay camino del origen a v?
    bool hayCamino(int v) const {
        return visit[v];
    }
    // número de aristas entre s y v
    int distancia(int v) const {
        return dist[v];
    }
    // devuelve el camino más corto desde el origen a v (si existe)
    deque<int> camino(int v) const {
        if (!hayCamino(v)) throw std::domain_error("No existe camino");
        deque<int> cam;
        for (int x = v; x != s; x = ant[x])
            cam.push_front(x);
        cam.push_front(s);
        return cam;
    }
private:
    std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
    std::vector<int> ant; // ant[v] = último vértice antes de llegar a v
    std::vector<int> dist; // dist[v] = aristas en el camino s-v más corto
    int s;
    void bfs(Grafo const& g) {
        std::queue<int> q;
        dist[s] = 0; visit[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : g.ady(v)) {
                if (!visit[w]) {
                    ant[w] = v; dist[w] = dist[v] + 1; visit[w] = true;
                    q.push(w);
                }
            }
        }
    }
};


template <typename Valor>
class Dijkstra {
public:
    Dijkstra(DigrafoValorado<Valor> const& g, int orig, int tam)
        : origen(orig),
        dist(g.V(), INF),
        ulti(g.V()),
        pq(g.V()),
        _tam(tam),
        vueltecitas(g.V(), -1) { // Inicializa con -1 para marcar sin predecesor

        dist[origen] = 0;
        pq.push(origen, 0); // Empieza desde el origen

        // Procesa la cola de prioridad mientras tenga elementos
        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop();
            for (auto a : g.ady(v)) // Recorre las aristas adyacentes
                relajar(a); // Relaja cada arista adyacente
        }
    }

    // Indica si existe un camino desde el origen al vértice `v`
    bool hayCamino(int v) const {
        return dist[v] != INF;
    }

    // Devuelve la distancia mínima desde el origen al vértice `v`
    Valor distancia(int v) const {
        return dist[v];
    }

    // Devuelve el camino mínimo desde el origen hasta el vértice `v`
    deque<AristaDirigida<Valor>> camino(int v) const {
        if (!hayCamino(v))
            throw std::domain_error("No existe camino al destino especificado");

        deque<AristaDirigida<Valor>> cam;
        for (auto a = ulti[v]; a.desde() != origen; a = ulti[a.desde()])
            cam.push_front(a);

        cam.push_front(ulti[v]); // Agrega el origen al camino
        return cam;
    }

    // Reconstruye el camino mínimo en un formato de pila (inverso)
    std::stack<int> reconstruirCaminoInverso(int destino) {
        if (!hayCamino(destino))
            throw std::domain_error("No existe camino al destino especificado");

        std::stack<int> sol;
        int nodo = destino;

        while (nodo != origen) {
            sol.push(nodo);
            nodo = vueltecitas[nodo];
        }
        sol.push(origen); // Añade el nodo de origen al camino
        return sol;
    }

private:
    const Valor INF = std::numeric_limits<Valor>::max(); // Valor infinito para comparación
    int origen; // Nodo origen
    std::vector<Valor> dist; // dist[v] = distancia mínima desde origen a v
    std::vector<AristaDirigida<Valor>> ulti; // ulti[v] = última arista en el camino más corto a v
    IndexPQ<Valor> pq; // Cola de prioridad para el algoritmo de Dijkstra
    int _tam; // Tamaño del grafo
    std::vector<int> vueltecitas; // vueltecitas[v] = predecesor de v en el camino más corto

    // Relaja una arista si encuentra un camino más corto hacia `w`
    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde(), w = a.hasta();

        // Compara y actualiza la distancia mínima a `w`
        if (dist[w] > dist[v] + a.valor()) {
            vueltecitas[w] = v; // Guarda el predecesor de `w`
            dist[w] = dist[v] + a.valor();
            ulti[w] = a; // Actualiza la última arista en el camino a `w`

            // Actualiza o inserta `w` en la cola de prioridad
            pq.update(w, dist[w]);
        }
    }
};



bool resuelveCaso() {
    int N,C,K, aux1, aux2, coste;
    cin >> N;
    if (!std::cin) return false;
    cin >> C;
    DigrafoValorado<int> mapaValorado(N);
    Grafo mapaSimple(N);
    for (int i = 0; i < C; i++) {
        cin >> aux1 >> aux2 >> coste;
        mapaValorado.ponArista({ aux1-1, aux2-1, coste });
        mapaValorado.ponArista({ aux2-1, aux1-1, coste });
        mapaSimple.ponArista(aux1 - 1, aux2 - 1);
    }
    cin >> K;
    for (int i = 0; i < K; i++) {
        cin >> aux1 >> aux2;
        Dijkstra<int> coste(mapaValorado, aux1 - 1, N); 
        CaminoMasCorto cam(mapaSimple, aux1 - 1);
        if (cam.hayCamino(aux2 - 1)) {
            cout << coste.distancia(aux2 - 1) << " ";
            if (coste.reconstruirCaminoInverso(aux2-1).size()-1!=cam.distancia(aux2-1)) cout << "NO";

            else cout << "SI";
        }
        else cout << "SIN CAMINO";
        cout << "\n";
    }
    cout << "---\n";
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

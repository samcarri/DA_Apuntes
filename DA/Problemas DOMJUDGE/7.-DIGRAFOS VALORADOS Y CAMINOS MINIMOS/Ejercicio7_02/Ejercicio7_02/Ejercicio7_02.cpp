
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
using namespace std;

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"

/*@ <answer>

Vamos a utilizar el algoritmo de Dijkstra para encontrar el camino minimo hacia el nodo en cuestion, cada vez que pasemos por el nodo en cuestion
para hacer la comprobación haremos un contador++ señalando que es una posible ruta.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
template <typename Valor>
class Dijkstra {
public:
    Dijkstra(DigrafoValorado<Valor> const& g, int orig, int size) : origen(orig),
        dist(g.V(), INF), ulti(g.V()), pq(g.V()), destino(size), countPaths(g.V(), 0) {

        dist[origen] = 0;
        countPaths[origen] = 1;  // Solo una forma de empezar desde el origen
        pq.push(origen, 0);

        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    int caminos() const { return countPaths[destino]; }

private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    int destino;
    std::vector<Valor> dist;
    std::vector<AristaDirigida<Valor>> ulti;
    IndexPQ<Valor> pq;
    std::vector<int> countPaths;  // Cantidad de caminos mínimos hacia cada nodo

    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde(), w = a.hasta();
        Valor nuevoCoste = dist[v] + a.valor();

        if (nuevoCoste < dist[w]) {
            dist[w] = nuevoCoste;
            ulti[w] = a;
            countPaths[w] = countPaths[v];  // Nuevo camino mínimo hacia w
            pq.update(w, dist[w]);
        }
        else if (nuevoCoste == dist[w]) {
            countPaths[w] += countPaths[v];  // Otro camino mínimo hacia w
        }
    }
};



bool resuelveCaso() {
    int N, C, aux1, aux2, coste;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;
    DigrafoValorado<int> calles(N);
    cin >> C;
    for (int i = 0; i < C; i++) {
        cin >> aux1 >> aux2 >> coste;
        calles.ponArista({ aux1 - 1, aux2 - 1, coste });
        calles.ponArista({ aux2 - 1, aux1 - 1, coste });
    }
    Dijkstra<int> solucion(calles, 0, N - 1);

    cout << solucion.caminos() << "\n";
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


/*@ <answer>
 *
 * Nombre y Apellidos: Samuel Carrillo Menchero y Yago Sanabria Gavin
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

#include "ConjuntosDisjuntos.h"
#include "DigrafoValorado.h"
#include "IndexPQ.h"

/*@ <answer>
SOLUCION
--------
Almacenamos el disgrafo de manera invertida, es decir, invertimos las aristas dirigidas, con ello podemos crear un grafo en el que sabemos
las distancias del origen al resto de los ratones. Tras ello unicamente queda aplicar el algoritmo de Dijkstra y contar los nodos (posicion
 de los ratones) cuyo camino minimo es menor o igual al tiempo establecido.

 COSTE
 -----
 Para resolver este problema usaremos el algoritmo de Dijkstra por lo cual el coste es de O(A log V) y con un espacio adicional en O(V). Siendo
 A el numero de aristas (caminos) y V el numero de vertices (celdas).

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


template <typename Valor>
class Dijkstra {
public:
    Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
        dist(g.V(), INF), ulti(g.V()), pq(g.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }
    bool hayCamino(int v) const { return dist[v] != INF; }
    Valor distancia(int v) const { return dist[v]; }
    deque<Valor> camino(int v) const {
        deque<Valor> cam;
        // recuperamos el camino retrocediendo
        AristaDirigida<Valor> a;
        for (a = ulti[v]; a.desde() != origen; a = ulti[a.desde()])
            cam.push_front(a);
        cam.push_front(a);
        return cam;
    }
private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    std::vector<Valor> dist;
    std::vector<AristaDirigida<Valor>> ulti;
    IndexPQ<Valor> pq;
    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor(); ulti[w] = a;
            pq.update(w, dist[w]);
        }
    }
};

bool resuelveCaso() {
    int N, S, T, P, aux1, aux2, coste, ratones=0;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;
    cin >> S >> T >> P;
    DigrafoValorado<int> laberinto(N);

    for (int i = 0; i < P; i++) {
        cin >> aux1 >> aux2 >> coste;
        laberinto.ponArista({ aux2 - 1, aux1 - 1, coste });
    }
    Dijkstra<int> a(laberinto, S - 1);

    for (int i = 0; i < N; i++) {
        if (a.hayCamino(i) && i != S - 1) {

            if (a.distancia(i) <= T) {
                ratones++;
            }
        }
    }
    cout << ratones << "\n";
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

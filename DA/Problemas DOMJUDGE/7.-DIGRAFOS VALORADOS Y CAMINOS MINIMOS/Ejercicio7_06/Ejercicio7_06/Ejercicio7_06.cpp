
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

Basicamente consiste en analizar nodo por nodo su grado de entrada y de salida.
Si el grado de entrada es de N-1 y el de salida es 0 entonces estamos hablando de un nodo "sumidero".

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
template <typename Valor>
class Dijkstra {
public:
    Dijkstra(DigrafoValorado<Valor> const& g, vector<bool>& burros) : dist(g.V(), INF), pq(g.V()) {
        for (int i = 0; i < g.V(); ++i) {
            if (burros[i]) {
                dist[i] = 0;  // Los nodos con Borriquín tienen distancia 0
                pq.push(i, 0);
            }
        }
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    Valor distancia(int v) const { return dist[v]; }

    int contarPueblosConDistanciaMenorQue(Valor D) const {
        int count = 0;
        for (Valor d : dist) {
            if (d <= D) count++;
        }
        return count;
    }

private:
    const Valor INF = std::numeric_limits<Valor>::max();
    std::vector<Valor> dist;
    IndexPQ<Valor> pq;

    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
        }
    }
};

bool resuelveCaso() {
    int D, P, C, aux1, aux2, coste, B;
    cin >> D >> P >> C;
    if (!std::cin)  // fin de la entrada
        return false;

    DigrafoValorado<int> pueblos(P);
    for (int i = 0; i < C; i++) {
        cin >> aux1 >> aux2 >> coste;
        pueblos.ponArista({ aux1 - 1, aux2 - 1, coste });
        pueblos.ponArista({ aux2 - 1, aux1 - 1, coste });
    }

    cin >> B;
    vector<bool> burros(P, false);
    for (int i = 0; i < B; i++) {
        cin >> aux1;
        burros[aux1 - 1] = true;  // Ajustar índice a 0
    }

    Dijkstra<int> burroKing(pueblos, burros);
    int resul = burroKing.contarPueblosConDistanciaMenorQue(D);
    cout << resul << "\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}

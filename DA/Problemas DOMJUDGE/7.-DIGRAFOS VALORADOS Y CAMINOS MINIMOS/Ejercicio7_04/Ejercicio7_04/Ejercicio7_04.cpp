
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



 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
template <typename Valor>
class Dijkstra {
public:
    Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
        dist(g.V(), INF), pq(g.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    Valor distancia(int v) const { return dist[v]; }
    bool hayCamino(int v) const { return dist[v] != INF; }

private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
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
    int N, C, O, P, aux1, aux2, coste;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;

    cin >> C;
    DigrafoValorado<int> casitas(N), casitasInverso(N);
    for (int i = 0; i < C; i++) {
        cin >> aux1 >> aux2 >> coste;
        casitas.ponArista({ aux1 - 1, aux2 - 1, coste });
        casitasInverso.ponArista({ aux2 - 1, aux1 - 1, coste });
    }

    cin >> O >> P;
    Dijkstra<int> subida(casitas, O - 1);
    Dijkstra<int> bajada(casitasInverso, O - 1);

    int suma = 0;
    bool discrepancia = false;

    for (int i = 0; i < P; i++) {
        cin >> aux1;
        if (subida.hayCamino(aux1 - 1) && bajada.hayCamino(aux1 - 1))
            suma += subida.distancia(aux1 - 1) + bajada.distancia(aux1 - 1);
        else
            discrepancia = true;
    }

    if (discrepancia) cout << "Imposible";
    else cout << suma;
    cout << "\n";

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

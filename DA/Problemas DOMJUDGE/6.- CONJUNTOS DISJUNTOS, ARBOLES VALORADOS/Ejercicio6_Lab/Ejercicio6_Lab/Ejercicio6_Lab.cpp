
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
#include "ConjuntosDisjuntos.h"
/*@ <answer>

Basicamente consiste en analizar nodo por nodo su grado de entrada y de salida.
Si el grado de entrada es de N-1 y el de salida es 0 entonces estamos hablando de un nodo "sumidero".

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
template <typename Valor>
class ARM_Kruskal {
private:
    std::vector<Arista<Valor>> _ARM;
    Valor coste;
    int max;
public:
    Valor costeARM() const {
        return coste;
    }
    std::vector<Arista<Valor>> const& ARM() const {
        return _ARM;
    }
    int returnMax() {
        return max;
    }
    ARM_Kruskal(GrafoValorado<Valor> const& g) : coste(0), max(0) {
        PriorityQueue<Arista<Valor>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                _ARM.push_back(a); coste += a.valor(); max = a.valor();
                if (_ARM.size() == g.V() - 1) break;
            }
        }
    }
};

bool resuelveCaso() {

    int N, M, aux1, aux2, coste;
    cin >> N;
 
    if (!std::cin)  // fin de la entrada
        return false;
    cin >> M;
    GrafoValorado<int> selva(N);
    for (int i = 0; i < M; i++) {
        cin >> aux1 >> aux2 >> coste;
        selva.ponArista({ aux1-1, aux2-1, coste });
    }
    // resolver el caso posiblemente llamando a otras funciones
    ARM_Kruskal<int> balanceo(selva);
    // escribir la solución
    if (balanceo.ARM().size() == N - 1)    cout << balanceo.returnMax() << "\n";
    else cout << "Imposible" << "\n";
    
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

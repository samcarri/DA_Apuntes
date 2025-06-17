/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXX) de los autores de la solucion.
 *
 *@ </authors> */
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "GrafoValorado.h" // propios o los de las estructuras de datos de clase
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"
/*@ <answer>
 Escribe aqui un comentario general sobre la solucion, explicando como
 se resuelve el problema y cual es el coste de la solucion, en funcion
 del tamanio del problema.
 @ </answer> */
 // ================================================================
 // Escribe el codigo completo de tu solucion aqui debajo
 // ================================================================
 //@ <answer>
template <typename Valor>
class ARM {
public:
    ARM(GrafoValorado<Valor> const& g, int origen, int destino) : maxArista(-1), cjtos(g.V()) {
        bool unidos = false;
        PriorityQueue<Arista<Valor>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        while (!pq.empty() && !unidos) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                _ARM.push_back(a);
                if (cjtos.unidos(origen, destino)) {
                    unidos = true;
                    maxArista = a.valor();
                }
                if (_ARM.size() == g.V() - 1) break;
            }
        }
    }
    Valor maxarista() const {
        return maxArista;
    }
private:
    std::vector<Arista<Valor>> _ARM;

    ConjuntosDisjuntos cjtos;
    Valor maxArista;
};
bool resuelveCaso() {
    // leer los datos de la entrada
    int N, M;
    cin >> N >> M;
    if (!std::cin) // fin de la entrada
        return false;
    GrafoValorado<int> grafo(N);
    int u, v, valor;
    for (int i = 0; i < M; i++) {
        cin >> u >> v >> valor;
        grafo.ponArista({ u - 1,v - 1,valor });
    }

    int origen, destino;
    cin >> origen >> destino;
    // resolver el caso posiblemente llamando a otras funciones
    if (origen != destino) {

        ARM<int> mina(grafo, origen - 1, destino - 1);

        auto max = mina.maxarista();
        max == -1 ? cout << "IMPOSIBLE" : cout << max;
    }
    else
        cout << 0;
    cout << "\n";
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

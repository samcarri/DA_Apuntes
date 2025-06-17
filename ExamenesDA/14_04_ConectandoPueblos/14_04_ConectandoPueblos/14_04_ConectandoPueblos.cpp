
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"
/*@ <answer>

El resultado pasa por aplicar el algoritmo de Kruskal al conjunto de pueblos con el objetivo de obtener un arbol de recubrimiento minimo
que nos permitira "comunicar" todos los pueblos. Sabemos por lo tanto que el resultado del problema sera la ultima arista añadida al
arbol, debido a que por definicion, esta siempre sera la de mayor tamaño.
Coste del algoritmo: O(ALogA).
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
template <typename Valor>
class ARM_Kruskal {
private:
    // Vector que almacena las aristas que forman el Árbol Recubridor Mínimo (ARM)
    std::vector<Arista<Valor>> _ARM;
    // Variable para almacenar el coste total del ARM
    Valor coste;
    int sol;
public:
    // Método para obtener el coste total del ARM
    Valor costeARM() const {
        return coste;
    }

    // Método para obtener las aristas del ARM
    std::vector<Arista<Valor>> const& ARM() const {
        return _ARM;
    }
    int solucion() {
        return sol;
    }
    // Implementación del algoritmo de Kruskal
    ARM_Kruskal(GrafoValorado<Valor> const& g) : coste(0),sol(0) {
        // Crear una cola de prioridad con las aristas del grafo
        PriorityQueue<Arista<Valor>> pq(g.aristas());
        // Inicializar la estructura de conjuntos disjuntos
        ConjuntosDisjuntos cjtos(g.V());

        // Procesar las aristas en orden de menor peso
        while (!pq.empty()) {
            // Extraer la arista de menor peso
            Arista<Valor> a = pq.top();
            pq.pop();

            // Obtener los vértices de la arista
            int v = a.uno(), w = a.otro(v);

            // Si los vértices no están en el mismo conjunto, unirlos
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);          // Unir los conjuntos de los vértices
                _ARM.push_back(a);         // Agregar la arista al ARM
                coste += a.valor();        // Sumar el peso de la arista al coste total
                sol = a.valor();
                // Si el ARM ya tiene V-1 aristas, terminamos
                if (_ARM.size() == g.V() - 1)
                   
                    break;
            }
        }
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, M;
    cin >> N >> M;
    if (!std::cin)  // fin de la entrada
        return false;
    GrafoValorado<int> pueblos(N);
    int aux1, aux2, valor;
    for (int i = 0; i < M; i++) {
        cin >> aux1 >> aux2>>valor;
        pueblos.ponArista({ aux1 - 1, aux2 - 1,valor });
    }
    ARM_Kruskal<int> sol(pueblos);
    // resolver el caso posiblemente llamando a otras funciones
    auto solu = sol.solucion();
    if (sol.ARM().size() == N-1)
        cout << solu << "\n";
    else cout << "Imposible\n";
    // escribir la solución

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
    int casos;
    cin >> casos;
    for(int i=0; i<casos; i++)(resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}

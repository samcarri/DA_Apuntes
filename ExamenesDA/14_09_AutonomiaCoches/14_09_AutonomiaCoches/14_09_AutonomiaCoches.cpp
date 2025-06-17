
/*@ <answer>
 *
 * Nombre y Apellidos: Samuel Carrillo Menchero
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"
/*@ <answer>

El resultado pasa por realizar un Arbol de recucbrimiento minimo del grafo que representan las zonas a las que podemos acceder mediante coche y
dar como resultado la ultima arista seleccionada para resolver el problema,ya que por definicion, esta sera la mayor de todo el conjunto de aristas
    La complejidad de de problema en tiempo sera de O(V+A) ya que estamos aplicando el algoritmo de Kruskal.
    La complejidad en espacio adicional esta en O(V) ya que el algoritmo almacena las aristas del arbol de recubrimiento que seleccionamos, y habrá V-1 aristas
    en total para formar el arbol.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
template <typename Valor>
class ARM_Kruskal {
private:
    std::vector<Arista<Valor>> _ARM; // Almacena las aristas del Árbol de Recubrimiento Mínimo (ARM)
    Valor coste;                     // Almacena el coste total del ARM
    int resultado;
public:
    // Devuelve el coste total del Árbol de Recubrimiento Mínimo
    Valor costeARM() const {
        return coste;
    }

    // Devuelve las aristas del Árbol de Recubrimiento Mínimo
    std::vector<Arista<Valor>> const& ARM() const {
        return _ARM;
    }
    int solucion() {
        return resultado;
    }
    // Constructor que implementa el algoritmo de Kruskal
    ARM_Kruskal(GrafoValorado<Valor> const& g) : coste(0), resultado(0) {
        // Inicializamos la cola de prioridad con todas las aristas del grafo
        PriorityQueue<Arista<Valor>> pq(g.aristas());

        // Inicializamos los conjuntos disjuntos para gestionar las componentes conexas
        ConjuntosDisjuntos cjtos(g.V());

        // Mientras haya aristas en la cola de prioridad
        while (!pq.empty()) {
            // Obtenemos la arista con menor peso
            Arista<Valor> a = pq.top();
            pq.pop();

            int v = a.uno();     // Un extremo de la arista
            int w = a.otro(v);   // Otro extremo de la arista

            // Si los vértices de la arista no están en el mismo componente conexo
            if (!cjtos.unidos(v, w)) {
                // Unimos los componentes conexos
                cjtos.unir(v, w);

                // Añadimos la arista al ARM
                _ARM.push_back(a);

                // Actualizamos el coste total
                coste += a.valor();
                resultado = a.valor();
                // Si ya tenemos suficientes aristas para formar un ARM, terminamos
                if (_ARM.size() == g.V() - 1) break;
            }
        }
    }
};

bool resuelveCaso() {

    int N, M, aux1, aux2, coste; //aux1 y aux2 para almacenar los nodos del grafo y coste para el coste de la arista que los une
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;
    cin >> M;
    GrafoValorado<int> visitaciones(N);
    for (int i = 0; i < M; i++) {
        cin >> aux1 >> aux2 >> coste;
        visitaciones.ponArista({ aux1 - 1, aux2 - 1, coste });
    }
    ARM_Kruskal<int> solucionar(visitaciones);
    if (solucionar.ARM().size() != N - 1) cout << "Imposible\n";
    else cout << solucionar.solucion() << "\n";
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

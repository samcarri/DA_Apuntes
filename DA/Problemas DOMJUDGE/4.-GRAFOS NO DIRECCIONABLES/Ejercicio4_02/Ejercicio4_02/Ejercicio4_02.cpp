
/*@ <answer>
 *
 * Nombre y Apellidos:Samuel Carrillo Menchero
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>
Calculamos la maxima componente conexa.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class MaximaCompConexa {
public:
    MaximaCompConexa(Grafo const& g) : visit(g.V(), false), maxim(0) {
        for (int v = 0; v < g.V(); ++v) {
            if (!visit[v]) { // se recorre una nueva componente conexa
                int tam = dfs(g, v);
                maxim = max(maxim, tam);
            }
        }
    }
    // tamaño máximo de una componente conexa
    int maximo() const {
        return maxim;
    }
private:
    vector<bool> visit; // visit[v] = se ha visitado el vértice v?
    int maxim; // tamaño de la componente mayor
    int dfs(Grafo const& g, int v) {
        visit[v] = true;
        int tam = 1;
        for (int w : g.ady(v)) {
            if (!visit[w])
                tam += dfs(g, w);
        }
        return tam;
    }
};

int resolver(const Grafo& grafo) {
    return MaximaCompConexa(grafo).maximo();
}

void resuelveCaso() {
    int N, M, aux1, aux2;
    // leer los datos de la entrada
    cin >> N >> M;
    Grafo grafo(N);
    for (int i = 0; i < M; i++) {
        cin >> aux1 >> aux2;
        grafo.ponArista(aux1-1, aux2-1);
    }
    // resolver el caso posiblemente llamando a otras funciones
    // escribir la solución
    cout << resolver(grafo) << endl;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}

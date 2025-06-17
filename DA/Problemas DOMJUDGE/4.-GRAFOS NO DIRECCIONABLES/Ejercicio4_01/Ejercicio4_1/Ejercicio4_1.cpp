
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class CaminosDFS {
private:
    std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
    std::vector<int> ant;    // ant[v] = último vértice antes de llegar a v
    int s;      
    int num_visitados;
    bool hayCiclo;

    // Función DFS para explorar los caminos desde un vértice
    void dfs(Grafo const& G, int v) {
        visit[v] = true;
        num_visitados++;
        for (int w : G.ady(v)) { // Recorrer los adyacentes al vértice v
            if (!visit[w]) {    // Si no ha sido visitado
                ant[w] = v;     // Registrar el predecesor
                dfs(G, w);      // Continuar explorando
            }
            else if(ant[v]!=w) {
                hayCiclo = true;
            }
        }
    }

public:
    // Constructor: inicializa la estructura y realiza el recorrido DFS
    CaminosDFS(Grafo const& g, int s)
        : visit(g.V(), false), ant(g.V()), s(s), num_visitados(0),hayCiclo(false) {
        dfs(g, s);
    }

    // Verifica si hay un camino del origen a v
    bool hayCamino(int v) const {
        return visit[v];
    }

    bool ciclo() {
        return hayCiclo;
    }

    int numVisitados() {
        return num_visitados;
    }
    // Define el tipo de datos para un camino
    using Camino = std::deque<int>;

    // Devuelve un camino desde el origen a v (debe existir)
    Camino camino(int v) const {
        if (!hayCamino(v)) {
            throw std::domain_error("No existe camino");
        }

        Camino cam;
        // Recuperamos el camino retrocediendo desde el destino al origen
        for (int x = v; x != s; x = ant[x]) {
            cam.push_front(x); // Agregar vértices en orden inverso
        }
        cam.push_front(s); // Agregar el origen
        return cam;
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int V, A,aux1, aux2;
    cin >> V;
    if (!std::cin)  // fin de la entrada
        return false;
    cin >> A;
    Grafo grafo(V);
    for (int i = 0; i < A; i++) {
        cin >> aux1 >> aux2;
        grafo.ponArista(aux1 , aux2 );
    }
    CaminosDFS sol(grafo,0);
    if (sol.ciclo() || sol.numVisitados() != V) cout << "NO\n";
    else cout << "SI\n";
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

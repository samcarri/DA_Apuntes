
/*@ <answer>
 *
 * Nombre y Apellidos:Samuel Carrillo Menchero
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

La resolución basicamente consiste en hacer una ordenación topológica, si existe un ciclo será imposible de realizar

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
class OrdenTopologico {
public:
    // g es DAG
    OrdenTopologico(Digrafo const& g) : visit(g.V(), false), ant(g.V()), apilado(g.V(), false) {
        existeCiclo = false;
        for (int v = 0; v < g.V(); ++v)
            if (!visit[v])
                dfs(g, v);
    }
    // devuelve la ordenación topológica
    std::deque<int> const& orden() const {
        return _orden;
    }
     bool hayCiclo() const { return existeCiclo; }
private:
    std::vector<bool> visit;
    std::deque<int> _orden; // ordenación topológica
    bool existeCiclo;
    std::vector<int> ant;
    std::vector<bool> apilado;
    void dfs(Digrafo const& g, int v) {
        visit[v] = true;
        apilado[v] = true;
        for (int w : g.ady(v)) {
            if (existeCiclo) return; //si encontramos un ciclo no seguimos la busqueda.
            if (!visit[w]) {
                ant[w] = v; dfs(g, w);
            }
            else if (apilado[w]) {
                existeCiclo = true;

            }
        }
        apilado[v] = false;
        _orden.push_front(v);
    }
   
};

deque<int> resolver(const Digrafo& grafo) {
    OrdenTopologico orden(grafo);
    if (orden.hayCiclo()) {
        deque<int> aux(0);
        return aux;
    }
    return orden.orden();
    
}
bool resuelveCaso() {
    int N, M, aux1, aux2;
    // leer los datos de la entrada
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;
    cin >> M;
    Digrafo grafo(N);
    // resolver el caso posiblemente llamando a otras funciones
    for (int i = 0; i < M; i++) {
        cin >> aux1 >> aux2;
        grafo.ponArista(aux1 - 1, aux2 - 1);
    }
    // escribir la solución
    auto a = resolver(grafo);
    if (a.size()==0) cout << "Imposible";
    else {
        for (int i = 0; i < a.size(); i++) {
            cout << a[i] + 1 << " ";
        }
    }
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

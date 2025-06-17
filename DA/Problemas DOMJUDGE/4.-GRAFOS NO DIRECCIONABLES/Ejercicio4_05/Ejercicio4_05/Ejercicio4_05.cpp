
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

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>
Pondremos las conexiones de los amigos en un grafo para posteriormente realizar un recorrido en profundidad
comprobando a que personas les llega la noticia
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


class CaminosDFS {
private:
    vector<bool> visit; // visit[v] = ¿hay camino de s a v?
    int s; // vértice origen
    int contador;

    void dfs(const Grafo& G, int v) {
        visit[v] = true;
        contador++;
        for (int w : G.ady(v)) {
            if (!visit[w]) {
                dfs(G, w);
            }
        }
    }

public:
    CaminosDFS(const Grafo& g, int s) : visit(g.V(), false), s(s), contador(0) {
        dfs(g, s);
    }

    int devolverConexos() const {
        return contador;
    }
};

bool resuelveCaso() {
    int N, M;
    cin >> N;
    if (!cin) return false;

    cin >> M;
    Grafo usuarios(N);

    for (int i = 0; i < M; i++) {
        int aux;
        cin >> aux;
        vector<int> grupo(aux);
        for (int j = 0; j < aux; j++) {
            cin >> grupo[j];
        }
        for (int j = 0; j < aux; j++) {
            for (int k = j + 1; k < aux; k++) {
                usuarios.ponArista(grupo[j] - 1, grupo[k] - 1);
            }
        }
    }

    for (int i = 0; i < N; i++) {
        CaminosDFS a(usuarios, i);
        cout << a.devolverConexos() << " ";
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

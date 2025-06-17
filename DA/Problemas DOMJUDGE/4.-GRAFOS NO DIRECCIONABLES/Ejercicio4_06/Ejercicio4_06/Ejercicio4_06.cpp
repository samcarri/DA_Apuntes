
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
El resultado pasara por hacer un recorrido en anchura del grafo, una vez realizado podremos ver la distancia del nodo origen al resto, conociendo esto podremos calcular cuales nodos
cumplen con el TTL y cuales no.
El coste de esta operacion sera de O(N*(V+A)) siendo:
- N numero de consultas
- V Numero de vertices del grafo
- A Numero de aristas del grafo
Esto es debido que al realizar una busqueda en anchura en un grafo visitamos todos sus vertices y aristas.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
class CaminoMasCorto {
public:
    // Constructor: inicializa la estructura y realiza el recorrido BFS
    CaminoMasCorto(Grafo const& g, int s, int TTL)
        : visit(g.V(), false), ant(g.V()), dist(g.V()), s(s), alcanzados(g.V(), false), alcanzables(0), TTL(TTL) {
        bfs(g);
    }

    // ¿Hay camino del origen a v?
    bool hayCamino(int v) const {
        return visit[v];
    }

    // Número de aristas entre s y v
    int distancia(int v) const {
        return dist[v];
    }

    int nodos_alcanzables() {
        return alcanzables;
    }

    // Devuelve el camino más corto desde el origen a v (si existe)
    using Camino = std::deque<int>;
    Camino camino(int v) const {
        if (!hayCamino(v)) {
            throw std::domain_error("No existe camino");
        }

        Camino cam;
        // Recuperar el camino retrocediendo desde el destino al origen
        for (int x = v; x != s; x = ant[x]) {
            cam.push_front(x);
        }
        cam.push_front(s); // Agregar el origen
        return cam;
    }

private:
    std::vector<bool> visit;  // visit[v] = ¿hay camino de s a v?
    std::vector<int> ant;     // ant[v] = último vértice antes de llegar a v
    std::vector<int> dist;    // dist[v] = aristas en el camino s-v más corto
    std::vector<bool> alcanzados;
    int alcanzables; //Numero de nodos alcanzables teniendo en cuenta el TTL
    int s;                    // vértice origen
    int TTL; //TIME TO LIFE
    // Función BFS para calcular los caminos más cortos desde el origen
    void bfs(Grafo const& g) {
        std::queue<int> q;
        dist[s] = 0;
        visit[s] = true;
        q.push(s);

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int w : g.ady(v)) { // Recorrer los adyacentes al vértice v
                if (!visit[w]) {     // Si no ha sido visitado
                    ant[w] = v;      // Registrar el predecesor
                    dist[w] = dist[v] + 1; // Calcular la distancia mínima
                    if (dist[w] <= TTL && !alcanzados[w]) {
                        alcanzados[w] = true;
                        alcanzables++;
                    }
                    visit[w] = true;
                    q.push(w);       // Agregar el vértice a la cola
                }
            }
        }
    }
};

bool resuelveCaso() {

    int N, C,K, aux1, aux2;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;
    cin >> C;
    Grafo grafo(N);
    for (int i = 0; i < C; i++) {
        cin >> aux1 >> aux2;
        grafo.ponArista(aux1 - 1, aux2 - 1);
    }
    cin >> K;
    for (int i = 0; i < K; i++) {
        cin >> aux1 >> aux2; //aux2 es TTL
        CaminoMasCorto comprobar(grafo, aux1-1, aux2);
        cout << N-comprobar.nodos_alcanzables()-1 << "\n";
    }
    cout << "---\n";
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

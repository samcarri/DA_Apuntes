
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
#include <stack>
using namespace std;

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"
/*@ <answer>

Basicamente consiste en analizar nodo por nodo su grado de entrada y de salida.
Si el grado de entrada es de N-1 y el de salida es 0 entonces estamos hablando de un nodo "sumidero".
IDEA
----
Convertir caminos en un vector que devuelva el nodo inmediatamente anterior desde el que se ha llegado, posteriormente hacer un trakeo para devolver el camino
seguido
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

template <typename Valor>
class Dijkstra {

public:
    Dijkstra(DigrafoValorado<Valor> const& g, int orig, int tam) : origen(orig),
        dist(g.V(), INF), ulti(g.V()), pq(g.V()),_tam(tam), vueltecitas(g.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }
    bool hayCamino(int v) const { return dist[v] != INF; } //O(1)
    Valor distancia(int v) const { return dist[v]; }//O(1)
    deque<Valor> camino(int v) const {
        deque<Valor> cam;
        // recuperamos el camino retrocediendo
        AristaDirigida<Valor> a;
        for (a = ulti[v]; a.desde() != origen; a = ulti[a.desde()])
            cam.push_front(a);
        cam.push_front(a);
        return cam;
    }
    stack<int> reconstruirCaminoInverso(int destino) {
        stack<int> sol;
        int nodo = destino;
        while (nodo != origen) {
            sol.push(nodo);
            nodo = vueltecitas[nodo];
        }
        sol.push(origen); // Añadimos el nodo de origen al final del camino
        return sol;
    }
private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    std::vector<Valor> dist;
    std::vector<AristaDirigida<Valor>> ulti;
    IndexPQ<Valor> pq;
    int _tam;
    vector<int> vueltecitas;

    void relajar(AristaDirigida<Valor> a) { //O(log V) Se realiza una vez por Arista como máximo.
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            vueltecitas[w] = v;
            dist[w] = dist[v] + a.valor(); ulti[w] = a;
        
            pq.update(w, dist[w]);//O(log V)
        }

    }
};

bool resuelveCaso() {
    int N, C, aux1, aux2, coste, K;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;
    cin >> C;
    DigrafoValorado<int> C2enTiraFlechas(N);
    for (int i = 0; i < C; i++) {
        cin >> aux1 >> aux2 >> coste; 
        C2enTiraFlechas.ponArista({ aux1 - 1, aux2 - 1, coste }); C2enTiraFlechas.ponArista({ aux2 - 1, aux1 - 1, coste });
    }
    cin >> K;
    vector<pair<int, int>> viajes(K);
    for (int i = 0; i < K; i++) {
        cin >> aux1 >> aux2;
        Dijkstra<int> sol(C2enTiraFlechas, aux1 - 1, aux2-1);
        if (sol.hayCamino(aux2 - 1)) {
            cout << sol.distancia(aux2 - 1) << ": ";
            stack<int> solu = sol.reconstruirCaminoInverso(aux2 - 1);
            while (!solu.empty()) {
                cout << solu.top() + 1;
                solu.pop();
                if (!solu.empty()) cout << " -> ";
            }
        }
        else cout << "NO LLEGA";
        cout << "\n";
    }
    cout << "---\n";
    // resolver el caso posiblemente llamando a otras funciones

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

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}

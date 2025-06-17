
/*@ <answer>
 *
 * Nombre y Apellidos: Samuel Carrillo Menchero
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include<queue>
#include<limits>
using namespace std;

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"
/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
template <typename Valor>
class Dijkstra {
public:
    Dijkstra(DigrafoValorado<Valor> const& g, int orig, vector<int> costes) : origen(orig),
        dist(g.V(), INF), ulti(g.V()), pq(g.V()), sol(0) {
        _costes = costes;
        dist[origen] = _costes[origen];
      
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }
    bool hayCamino(int v) const { return dist[v] != INF; }
    Valor distancia(int v) const { return dist[v]; }
    deque<Valor> camino(int v) const {
        deque<Valor> cam;
        // recuperamos el camino retrocediendo
        AristaDirigida<Valor> a;
        for (a = ulti[v]; a.desde() != origen; a = ulti[a.desde()])
            cam.push_front(a);
        cam.push_front(a);
        return cam;
    }
    int resultado() { return sol; }
private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    std::vector<Valor> dist;
    std::vector<AristaDirigida<Valor>> ulti;
    IndexPQ<Valor> pq;
    vector<int> _costes;
    int sol;
    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()+ _costes[w]) {
            dist[w] = dist[v] + a.valor()+_costes[w]; ulti[w] = a;
           
            pq.update(w, dist[w]);
        }
    }
};
bool resuelveCaso() {

    // leer los datos de la entrada
    int N, M, aux, aux1, coste;
    cin >> N;
    if (N==0)
        return false;
    DigrafoValorado<int> laRed(N);
    vector<int> tiempos(N);
  
    for (int i = 0; i < N; i++) {
        cin >> tiempos[i];
    }
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> aux >> aux1 >> coste;
        laRed.ponArista({ aux-1, aux1-1, coste });
    }
    Dijkstra<int> sercheando(laRed, 0, tiempos);
    if (!sercheando.hayCamino(N - 1)) cout << "IMPOSIBLE";
    else cout << sercheando.distancia(N-1);
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

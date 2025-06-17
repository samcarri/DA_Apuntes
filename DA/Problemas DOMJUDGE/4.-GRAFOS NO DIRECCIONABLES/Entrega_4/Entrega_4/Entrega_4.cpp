/*@ <answer>
 *
 * Nombre y Apellidos: Samuel Carrillo y Yago Sanabria
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase


using Camino = std::deque<int>;

class CaminoMasCorto {
public:
    CaminoMasCorto(Grafo const& g, int s) : visit(g.V(), false),
        ant(g.V()), dist(g.V()), s(s) {
        bfs(g);
    }

    // ¿hay camino del origen a v?
    bool hayCamino(int v) const {
        return visit[v];
    }

    int distancia(int v) const {
        return dist[v];
    }
    // devuelve el camino más corto desde el origen a v (si existe)
    Camino camino(int v) const {
        if (!hayCamino(v)) throw std::domain_error("No existe camino");
        Camino cam;
        for (int x = v; x != s; x = ant[x])
            cam.push_front(x);
        cam.push_front(s);
        return cam;
    }

private:

    std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
    std::vector<int> ant; // ant[v] = último vértice antes de llegar a v
    std::vector<int> dist; // dist[v] = aristas en el camino s-v más corto
    int s;

    void bfs(Grafo const& g) {
        std::queue<int> q;
        dist[s] = 0; visit[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : g.ady(v)) {
                if (!visit[w]) {
                    ant[w] = v; dist[w] = dist[v] + 1; visit[w] = true;
                    q.push(w);
                }
            }
        }
    }
};

int camino_corto(int c1, int c2) {
    if (c1 < c2) return c1;
    else return c2;
}

bool resuelveCaso() {
    //VARIABLES
    //---------
    int N;//numero de intersecciones
    int C;//tramos de calles
    int Alex; //casa de Alex
    int Lucas; //casa de Lucas
    int trabajo; //panaderia
    int aux1;
    int aux2;
    int sumaAux, sumaTotal, puntoMedio;
    // leer los datos de la entrada


    cin >> N >> C >> Alex >> Lucas >> trabajo;

    if (!std::cin)  // fin de la entrada
        return false;

    Grafo intersecciones(N);

    for (int i = 0; i < C; i++) {
        cin >> aux1 >> aux2;
        intersecciones.ponArista(aux1 - 1, aux2 - 1);
    }


   CaminoMasCorto alexViaja(intersecciones, Alex-1);
   CaminoMasCorto lucasViaja(intersecciones, Lucas-1);
   CaminoMasCorto panaderia(intersecciones, trabajo - 1);
   puntoMedio = 0;
   sumaTotal = 1000000;
   for (int i = 0; i < N; i++) {
       aux1 = alexViaja.distancia(i);
       aux2 = lucasViaja.distancia(i);
       if (aux1 + aux2 + panaderia.distancia(i) < sumaTotal) {
           sumaTotal = aux1 + aux2 + panaderia.distancia(i);
           puntoMedio = i;
       }
}
 

   cout << sumaTotal << endl;

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

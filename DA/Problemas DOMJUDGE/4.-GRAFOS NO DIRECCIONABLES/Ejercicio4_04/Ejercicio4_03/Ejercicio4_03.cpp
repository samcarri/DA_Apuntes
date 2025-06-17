#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <deque>  // Para usar std::deque
#include <queue>
#include <stdexcept> // Para std::domain_error
using namespace std;

#include "Grafo.h"  // Asegúrate de que este archivo esté correctamente implementado

typedef deque<int> Camino;  // Definimos el tipo Camino como un deque de enteros

class CaminoMasCorto {
public:
    CaminoMasCorto(Grafo const& g, int s)
        : visit(g.V(), false), ant(g.V(), -1), dist(g.V(), -1), s(s) {
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

    // Devuelve el camino más corto desde el origen a v (si existe)
    Camino camino(int v) const {
        if (!hayCamino(v)) throw std::domain_error("No existe camino");
        Camino cam;
        for (int x = v; x != s; x = ant[x])
            cam.push_front(x);
        cam.push_front(s);
        return cam;
    }

private:
    vector<bool> visit; // visit[v] = ¿hay camino de s a v?
    vector<int> ant;    // ant[v] = último vértice antes de llegar a v
    vector<int> dist;   // dist[v] = aristas en el camino s-v más corto
    int s;              // Nodo origen

    void bfs(Grafo const& g) {
        queue<int> q;
        dist[s] = 0;
        visit[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : g.ady(v)) {
                if (!visit[w]) {
                    ant[w] = v;
                    dist[w] = dist[v] + 1;
                    visit[w] = true;
                    q.push(w);
                }
            }
        }
    }
};

bool resuelveCaso() {
    int P, N, nActores;
    int contador = 0;
    map<string, int> actores;
    map<string, vector<string>> Pelicula_Actores;
    string titulo, nombre;

    cin >> P;

    if (!std::cin)  // fin de la entrada
        return false;

    // Leer la información de películas y actores
    for (int i = 0; i < P; i++) {
        cin >> titulo >> nActores;
        for (int j = 0; j < nActores; j++) {
            cin >> nombre;
            if (actores.find(nombre) == actores.end()) {
                actores[nombre] = contador++; // Asignar un ID único a cada actor, 0-based
            }
            Pelicula_Actores[titulo].push_back(nombre); // Añadir los actores a la película
        }
    }

    Grafo Bacon(contador);  // Inicializar el grafo con el número de actores

    // Conectar los actores que aparecen en la misma película
    for (const auto& pelicula : Pelicula_Actores) {
        const vector<string>& actoresEnPelicula = pelicula.second;
        for (size_t i = 0; i < actoresEnPelicula.size(); ++i) {
            for (size_t j = i + 1; j < actoresEnPelicula.size(); ++j) {
                // Obtenemos los IDs únicos de los actores y conectamos en el grafo
                int idActor1 = actores[actoresEnPelicula[i]];
                int idActor2 = actores[actoresEnPelicula[j]];
                Bacon.ponArista(idActor1, idActor2);  // Conectar los actores en el grafo
            }
        }
    }

    cin >> N;

    // Verificar que "KevinBacon" está en el mapa
    if (actores.find("KevinBacon") == actores.end()) {
        cerr << "Error: KevinBacon no está en la lista de actores." << endl;
        return false;
    }

    int origen = actores["KevinBacon"]; // 0-based
    CaminoMasCorto anchura(Bacon, origen);

    for (int i = 0; i < N; i++) {
        cin >> nombre;
        cout << nombre << " ";
        // Verificar que el actor existe
        if (actores.find(nombre) == actores.end()) {
            cout << "INF";
        }
        else {
            int id = actores[nombre];
            if (!anchura.hayCamino(id)) cout << "INF";
            else cout << anchura.distancia(id);
        }
        cout << endl;
    }
    cout << "---" << endl;
    return true;
}

int main() {
    // Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // Para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}

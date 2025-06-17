
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "IndexPQ.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


int resolver(vector<IndexPQ<int>>& pilas) {
    int num_pilas_disponibles = pilas.size();
    int ejemplar_minimo_local = 100000000;
    int ejemplar_minimo_glonal = 100000000;
    int id_pop = 0;
    while (num_pilas_disponibles != 0) {
        for (int i = 0; i < pilas.size(); i++) {
            if (pilas[i].size() != 0) {
                if(pilas[i].>ejemplar_minimo_local)
            }
        }
    }

}
bool resuelveCaso() {

    int N, K;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;
    vector<IndexPQ<int>> comics(N);
    for (int i = 0; i < N; i++) {
        cin >> K;
        IndexPQ<int> pila(K);
        for (int j = 0; j < K; j++) {
            int aux;
            cin >> aux;
            pila.push(aux);

        }
        comics[i] = pila;
}
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

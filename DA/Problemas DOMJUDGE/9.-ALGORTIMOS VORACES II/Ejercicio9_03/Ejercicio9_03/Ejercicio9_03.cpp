
/*@ <answer>
 *
 * Nombre y Apellidos: Samuel Carrillo Menchero
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;



/*
   Resuelve el problema de emparejar pilas para maximizar la cantidad de coches en funcionamiento.
   Ordena los voltajes y combina el más bajo con el más alto en cada iteración para cumplir el umbral V.
   Coste: O(N log N) debido al ordenamiento.
*/
int resolver(deque<int>& pilasDeque, int V) {
    sort(pilasDeque.begin(), pilasDeque.end()); // Ordena las pilas de menor a mayor
    int sol = 0;

    // Mientras haya al menos dos pilas para emparejar
    while (pilasDeque.size() > 1) {
        int voltaje_comb = pilasDeque.front() + pilasDeque.back(); // Combina el menor y el mayor voltaje
        if (voltaje_comb >= V) {
            sol++; // Se forma un coche con las dos pilas
            pilasDeque.pop_front(); // Elimina la pila de menor voltaje
            pilasDeque.pop_back();  // Elimina la pila de mayor voltaje
        }
        else {
            pilasDeque.pop_front(); // Si no cumplen el voltaje, elimina solo la pila menor
        }
    }

    return sol;
}
void resuelveCaso() {

    // leer los datos de la entrada
    int N, V;
    cin >> N >> V;
    deque<int> pilasDeque(N);
    for (int i = 0; i < N; i++) {
    
        cin >> pilasDeque[i];
    }
    cout << resolver(pilasDeque, V) << "\n";
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

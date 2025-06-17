
/*@ <answer>
 *
 * Nombre y Apellidos:Samuel Carrillo Menchero
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include <map>
using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

Basicamente consiste en analizar nodo por nodo su grado de entrada y de salida.
Si el grado de entrada es de N-1 y el de salida es 0 entonces estamos hablando de un nodo "sumidero".

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {

    int V, A, aux1, aux2;
    int resultado = -1;
    cin >> V >> A;
    if (!std::cin)  // fin de la entrada
        return false;
    Digrafo grafo(V);
    map<int, pair<int, int>> entrada_salida; //en el pair se almacena el grado de entrada y de salida
    for (int i = 0; i < V; i++)entrada_salida[i]={0,0}; //entrada-salida
    for (int i = 0; i < A; i++) {
        cin >> aux1 >> aux2;
        entrada_salida[aux1].second++;
        entrada_salida[aux2].first++;
        grafo.ponArista(aux1, aux2);
    }
  
    for (int i = 0; i < V; i++) {
        if (entrada_salida[i].first == V - 1 && entrada_salida[i].second == 0) resultado = i;
       
    }

    // escribir la solución
    if (resultado == -1) cout << "NO\n";
    else cout << "SI " << resultado << "\n";
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


/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
int minimoEsfuerzo(PriorityQueue<int> & cola) {
    int esfuerzo = 0;
    int res = 0;
    while (cola.size() != 1) {
        res += cola.top();
        cola.pop();
        res += cola.top();
        cola.pop();
        cola.push(res);
      
       
      
     esfuerzo += res;
         
        res = 0;
    }
    res = esfuerzo;
    return res;
}
void leerCola(PriorityQueue<int> cola) {
    while (!cola.empty()) {
        cout << cola.top() << " | ";
        cola.pop();
    }
    cout << endl;
}
bool resuelveCaso() {

    // leer los datos de la entrada
    int N,elem;
    PriorityQueue<int> cola;
    cin >> N;
    if (N==0)
        return false;

    // resolver el caso posiblemente llamando a otras funciones
    for (int i = 0; i < N; i++) {
        cin >> elem;
        cola.push(elem);
    }
    // escribir la solución
    
   // leerCola(cola);
    cout << minimoEsfuerzo(cola) << "\n";
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

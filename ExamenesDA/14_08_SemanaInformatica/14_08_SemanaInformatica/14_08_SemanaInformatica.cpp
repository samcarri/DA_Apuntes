
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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
struct actividad {
    int comienzo;
    int final;
};
bool operator<( actividad const & a, actividad const & b) {
    if (a.comienzo == b.comienzo) return a.final < b.final;
    else return a.comienzo < b.comienzo;
}

int resolver(PriorityQueue<actividad>& actividades) {
    int res = 0;
    actividad actividad_actual;
    actividad actividad_aux;
    bool seguir = false;
    actividad_actual = actividades.top();
    actividades.pop(); //O(log(N))
    while (actividades.size() > 0) {
        seguir = true;
    
        while (actividades.size() > 0 && seguir) {
            actividad_aux = actividades.top();
            actividades.pop();
      
            if (actividad_aux.comienzo < actividad_actual.final) {
                res++;
            }
            else {
                seguir = false;
                actividad_actual = actividad_aux;
            }
       }
    }

    return res;
}
bool resuelveCaso() {

    int N;
    cin >> N;
    if (N==0)  // fin de la entrada
        return false;
    PriorityQueue<actividad> actividades;
    int aux1, aux2;
    for (int i = 0; i < N; i++) {
        cin >> aux1 >> aux2;
        actividades.push({ aux1, aux2 });
    }
    // resolver el caso posiblemente llamando a otras funciones
    cout << resolver(actividades) << endl;
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

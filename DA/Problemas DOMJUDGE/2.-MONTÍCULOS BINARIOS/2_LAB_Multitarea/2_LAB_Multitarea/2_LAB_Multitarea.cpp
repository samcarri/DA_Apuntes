
/*@ <answer>
 *
 * Nombre y Apellidos: Samuel Carrillo Menchero
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

struct tTarea {
    int inicio;
    int final;
    int periodo;
};
bool operator<(tTarea const& a, tTarea const& b) {
    return b.inicio > a.inicio ||
        (a.inicio == b.inicio && b.final > a.final);
}
/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
bool resolver(PriorityQueue<tTarea> &tareas, int minuto) {
    int comienzo = -1;
    int final = -1;
    tTarea aux;
    while (!tareas.empty() && tareas.top().inicio < minuto) {
        tTarea tarea = tareas.top();
        if (tarea.inicio >= comienzo && tarea.inicio < final) {
         /*
            cout << "tarea con inicio en: " << tarea.inicio << " y final en :" << tarea.final <<  " coincide con tarea " << endl;
            cout << "tarea con inicio en: " << comienzo<< " y final en :" << final<<  " coincide con tarea " << endl;
            */
            return true;
        }
        if (tarea.periodo != 0) {
            aux.final = tarea.final + tarea.periodo;
            aux.inicio = tarea.inicio + tarea.periodo;
            aux.periodo = tarea.periodo;
            tareas.push(aux);
        }
        comienzo = tarea.inicio;
     final = tarea.final;
        tareas.pop();
    }
    return false;
}
bool resuelveCaso() {

    int N, M, T;
    cin >> N;

    if (!std::cin)  // fin de la entrada
        return false;

    cin >> M;
    cin >> T;
    PriorityQueue<tTarea> tareas;
    tTarea aux;
    // resolver el caso posiblemente llamando a otras funciones
    for (int i = 0; i < N; i++) {
        cin >> aux.inicio >> aux.final;
        aux.periodo = 0;
        tareas.push(aux);
    }
    for (int i = 0; i < M; i++) {
        cin >> aux.inicio >> aux.final >> aux.periodo;
        tareas.push(aux);
    }
    // escribir la solución
    if (resolver(tareas,T)) cout << "SI\n";
    else cout << "NO\n";

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

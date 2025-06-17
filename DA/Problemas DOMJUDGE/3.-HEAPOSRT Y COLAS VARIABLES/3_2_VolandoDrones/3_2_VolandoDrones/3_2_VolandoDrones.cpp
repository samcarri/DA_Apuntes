
/*@ <answer>
 *
 * Nombre y Apellidos: Samuel Carrillo Menchero
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "IndexPQ.h"  // propios o los de las estructuras de datos de clase
#include "PriorityQueue.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

struct pila {
    int carga;
};
 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
bool operator<(pila const& a, pila const& b) {
    return b.carga < a.carga;
}

void resolver(PriorityQueue<pila>& NueveV, PriorityQueue<pila>& UnV, int N) {
    int resultado = 0;
    int pilaNueve, pilaUno;
    int numDrones = 0;
    while (!NueveV.empty() && !UnV.empty()) {

        pilaNueve = NueveV.top().carga; NueveV.pop();
        pilaUno = UnV.top().carga; UnV.pop();

        if (pilaUno < pilaNueve) { // La de 1.5V es menor que la de 9V
            resultado += pilaUno;
            pilaNueve -= pilaUno;
            NueveV.push({ pilaNueve });
        }
        else { // La de 1.5V es mayor o igual a la de 9V
            resultado += pilaNueve;
            pilaUno -= pilaNueve;
            if (pilaUno != 0) UnV.push({ pilaUno });
        }
        numDrones++;
        if (numDrones == N) {
            cout << resultado << " ";
            resultado = 0; numDrones = 0;
        }
    }
    if (resultado != 0) cout << resultado << "\n";
    else cout << "\n";
}


bool resuelveCaso() {
    int N, A, B;
    cin >> N;
    // leer los datos de la entrada
    
    if (!std::cin)  // fin de la entrada
        return false;

    cin >> A >> B;
    PriorityQueue <pila> NueveV;
    PriorityQueue<pila> UnV;
    pila pila;
    for (int i = 0; i < A; i++) {
        cin >> pila.carga;
        NueveV.push(pila);
    }
    for (int i = 0; i < B; i++) {
        cin >> pila.carga;
       UnV.push(pila);
    }
    /*
    while(!NueveV.empty()) {
        cout << NueveV.top().carga<<" "; NueveV.pop();
    }
    */
    // resolver el caso posiblemente llamando a otras funciones
    resolver(NueveV, UnV, N);
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


/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase
#include "EnterosInf.h"
/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
EntInf resolver(int caras, int numeros) {
    Matriz<EntInf> solucion(caras + 1, numeros + 1, 0); 
    for (int i = 0; i <= caras; i++) {
        solucion[i][0] = 1; //hay una forma de obtener 0 caras
    }
 
    for (int i = 1; i <= caras; i++) {
        for (int j = 1; j <= numeros; j++) {
            solucion[i][j] =solucion[i][j]+ solucion[i - 1][j];
            if (j - i >= 0) solucion[i][j] =solucion[i][j]+ solucion[i][j - i];
         
        }
     
    }

    return solucion[caras][numeros];
}
bool resuelveCaso() {

    int caras, numeros;
    cin >> caras >> numeros;
    cout << resolver(caras, numeros)<<endl;
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
    int casos;
    cin >> casos;
    for(int i=0; i<casos;i++) (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}

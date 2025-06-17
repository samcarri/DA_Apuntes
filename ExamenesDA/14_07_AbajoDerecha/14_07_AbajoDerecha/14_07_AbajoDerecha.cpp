
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
int resolver(Matriz<int> const & matriz) {
    int filas = matriz.numfils();
    int cols = matriz.numcols();
    Matriz<int> saltitos(filas, cols, 0);
    saltitos[0][0] = 1; //una forma de llegar punto de comienzo
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            int salto = matriz[i][j];
            if (saltitos[i][j] > 0) {
                if (i +salto< filas) saltitos[i + salto][j] += saltitos[i][j];
                if (j + salto < cols) saltitos[i][j + salto] += saltitos[i][j];
            }
        }
    }
    return saltitos[filas-1][cols-1];
}

bool resuelveCaso() {

    int filas, columnas;
    cin >> filas >> columnas;

    if (!std::cin)  // fin de la entrada
        return false;
    Matriz<int> matriz(filas, columnas);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cin >> matriz[i][j];
        }
    }
    cout << resolver(matriz) << endl;
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

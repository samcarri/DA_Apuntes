
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

#include "Matriz.h"  // propios o los de las estructuras de datos de clase
#include "EnterosInf.h"
/*@ <answer>

Basicamente consiste en analizar nodo por nodo su grado de entrada y de salida.
Si el grado de entrada es de N-1 y el de salida es 0 entonces estamos hablando de un nodo "sumidero".

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int resolver(Matriz<char> const& mapa, int N, int M) {
    Matriz<int> auxiliar(N, M,0);
    auxiliar[0][0] = 1; // Solo hay una forma de ir al origen 
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i == 0 && j == 0) {
                continue; // No hacemos nada
            }
            if (mapa[i][j] == 'X') {
                auxiliar[i][j] = 0;
            }
            else {
                if (i > 0) {
                    auxiliar[i][j] += auxiliar[i - 1][j]; // Agrega el valor de arriba si no estamos en la primera fila
                }
                if (j > 0) {
                    auxiliar[i][j] += auxiliar[i][j - 1]; // Agrega el valor de la izquierda si no estamos en la primera columna
                }
            }
        }
    }
    /*
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << auxiliar[i][j] << " ";
        }
        cout << endl;
    }
    */
    return auxiliar[N - 1][M - 1];
}

bool resuelveCaso() {

    int N, M;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;
    cin >> M;
    Matriz<char> matriz(N, M);
    // resolver el caso posiblemente llamando a otras funciones
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> matriz[i][j];
          //  cout << matriz[i][j] << " ";
        }
       // cout << endl;
    }
    // escribir la solución
    cout << resolver(matriz, N, M) << "\n";
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

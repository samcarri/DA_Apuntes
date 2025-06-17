
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
pair<int, int> resolver(const Matriz<int>& matriz, int N) {
    // Resultado: {máximo valor, columna correspondiente}
    pair<int, int> res = { 0, 0 };

    // Matriz auxiliar para almacenar resultados intermedios
    Matriz<int> aux(N, N, 0);

    // Inicializar la primera fila de la matriz auxiliar
    for (int i = 0; i < N; i++) {
        aux[0][i] = matriz[0][i];
    }

    // Rellenar la matriz auxiliar acumulando los máximos
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < N; j++) {
            aux[i][j] = matriz[i][j];

            // Acumular el máximo valor desde la fila anterior
            if (j > 0) {
                aux[i][j] += max(aux[i - 1][j], aux[i - 1][j - 1]);
            }
            else {
                aux[i][j] += aux[i - 1][j];
            }

            if (j < N - 1) {
                aux[i][j] = max(aux[i][j], matriz[i][j] + aux[i - 1][j + 1]);
            }

            // Si estamos en la última fila, actualizamos el máximo global
            if (i == N - 1 && aux[i][j] > res.first) {
                res.first = aux[i][j];
                res.second = j;
            }
        }
    }
    
    return res;
}

bool resuelveCaso() {
    int N;
    cin >> N;

    if (!std::cin)  // fin de la entrada
        return false;
    Matriz<int> matriz(N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> matriz[i][j];
        }
    }
    pair<int,int> res=resolver(matriz, N);
    cout << res.first << " " << res.second+1 << "\n";


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

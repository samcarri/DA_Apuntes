
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
#include "EnterosInf.h"
/*@ <answer>
Debemos aplicar un algoritmo dinamico en el que por cada posicion almacenaremos el minimo camino posible para llegar a un punto:
Por ejemplo si i=0 sabemos que nos encontramos en el poblado 0 y por lo tanto si nuestra j=1 querra decir que queremos llegar al poblado 1 desde el 0.
Por cada posicion (i, j) para saber la posicion minima debemos contemplar:
    -Lo que cuesta ir desde (i,j): viaje directo.
    -Lo que costaria ir si fueramos eligiendo otra ruta, por ejemplo:
        Quermos ir al pueblo 2 desde el 0 posicion (0,2):
        -Posibilidad 1: viaje directo desde (0,2)
        -Posibilidad 2: ir a al pueblo 1 (0, 1) y despues ir al (1,2).
Formula: matriz[i,j]= min(matriz[i,j], (matriz[i][k]+matriz[k][i]))
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
void resolver(Matriz<int> &matriz, int N) {
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                matriz[i][j] = min(matriz[i][j], matriz[i][k] + matriz[k][j]);
            }
        }
    }
}
bool resuelveCaso() {

    int N;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;
    Matriz<int> amazonas(N, N, 1000010);
    // resolver el caso posiblemente llamando a otras funciones
        for (int i = 0; i < N - 1; i++) {
            for (int j = i + 1; j < N; j++) {
                cin >> amazonas[i][j];
            }
        }
        resolver(amazonas, N);
        for (int i = 0; i < N - 1; i++) {
            for (int j = i + 1; j < N; j++) {
                cout << amazonas[i][j]<<" ";
            }
            cout << "\n";
        }
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

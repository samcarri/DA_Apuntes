
/*@ <answer>
 *
 * Nombre y Apellidos:Samuel Carrillo Menchero
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <vector>
using namespace std;



/*@ <answer>

Basicamente consiste en analizar nodo por nodo su grado de entrada y de salida.
Si el grado de entrada es de N-1 y el de salida es 0 entonces estamos hablando de un nodo "sumidero".

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
int resolver(vector<int> const agujeros, int L) {
    int res = 1;
    int i = 1;
    int comienzo_tapar = agujeros[0];
    while (i != agujeros.size()) {
        if (agujeros[i] - comienzo_tapar > L) {
            res++;
            comienzo_tapar = agujeros[i];
        }
            i++;
    }
    return res;
}
bool resuelveCaso() {
    int N, L;
    cin >> N;

    if (!std::cin)  // fin de la entrada
        return false;
    cin >> L;
    vector<int> agujeros(N);
    for (int i = 0; i < N; i++) cin >> agujeros[i];
    cout << resolver(agujeros, L) << "\n";
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

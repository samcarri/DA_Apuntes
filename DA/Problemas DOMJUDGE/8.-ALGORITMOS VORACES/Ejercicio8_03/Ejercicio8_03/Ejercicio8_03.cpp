
/*@ <answer>
 *
 * Nombre y Apellidos:Samuel Carrillo Menchero
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;



/*@ <answer>
Resolución: ordenamos jugadores y camisetas de menor a mayor y vamos asignando las que podamos en orden, el resultado será el número de 
jugadores que queden sin camiseta.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
int resolver(vector<int>& ninios, vector<int>& camisetas) {
    sort(ninios.begin(), ninios.end());
    sort(camisetas.begin(), camisetas.end());
    int contador_ninios = 0, contador_camisetas = 0;
    int camisetas_asignadas = 0;
    while (contador_ninios < ninios.size() && contador_camisetas < camisetas.size()) {
        if (camisetas[contador_camisetas] == ninios[contador_ninios] || camisetas[contador_camisetas]  == ninios[contador_ninios]+1) {
           // cout << camisetas[contador_camisetas] << " " << ninios[contador_ninios];
            camisetas_asignadas++;
            contador_ninios++;
            contador_camisetas++;
           
        }
        else if (camisetas[contador_camisetas] > ninios[contador_ninios] + 1) contador_ninios++;
        else  contador_camisetas++;
    }
    return ninios.size() - camisetas_asignadas;
}
bool resuelveCaso() {
    int N, M;
    cin >> N;

    if (!std::cin)  // fin de la entrada
        return false;
    cin >> M;
    vector<int> ninios(N);
    vector<int> camisetas(M);
    for (int i = 0; i < N; i++) cin >> ninios[i];
    for (int i = 0; i < M; i++) cin >> camisetas[i];
    cout << resolver(ninios, camisetas) << "\n";

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


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
#include <algorithm>
using namespace std;



/*@ <answer>

Basicamente consiste en analizar nodo por nodo su grado de entrada y de salida.
Si el grado de entrada es de N-1 y el de salida es 0 entonces estamos hablando de un nodo "sumidero".

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
int resolver(vector<int> &invadidas, vector<int>& defensa) {
    int contador_ciudades = 0;
    int contador_defensas = 0;
   // int defensores = 0;
    int res = 0;
    std::sort(invadidas.begin(), invadidas.end());
    std::sort(defensa.begin(), defensa.end());
   // for (int i = 0; i < defensa.size(); i++) cout << defensa[i] << " ";
    while (contador_ciudades != invadidas.size() && contador_defensas != invadidas.size()) {
       
        if (defensa[contador_defensas] >= invadidas[contador_ciudades]) {
           // cout << defensores << "->" << invadidas[contador_ciudades] << "\n";
            res++;
            contador_ciudades++;
      
        }
        contador_defensas++;
    }
    return res;
}
bool resuelveCaso() {
    int N;
    cin >> N;

    if (!std::cin)  // fin de la entrada
        return false;
    
    vector<int> invadidas(N);
    vector<int> defensa(N);
    for (int i = 0; i < N; i++) cin >> invadidas[i];
    for (int i = 0; i < N; i++) cin >> defensa[i];
    cout << resolver(invadidas, defensa)<<"\n";
    // resolver el caso posiblemente llamando a otras funciones

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

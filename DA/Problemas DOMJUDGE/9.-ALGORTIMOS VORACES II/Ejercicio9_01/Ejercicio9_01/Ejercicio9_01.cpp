
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
struct tEdificio {
    int comienzo;
    int final;
};

bool operator <(tEdificio const& a, tEdificio const& b) {
    return a.final < b.final;
}
int resolver(vector<tEdificio> &edificios) {
    int res = 1;
    sort(edificios.begin(), edificios.end());
   // for (int i = 0; i < edificios.size(); i++) cout << edificios[i].comienzo << " " << edificios[i].final<<endl;
   // cout << "---" << endl;
    tEdificio ant=edificios[0];
    for (int i = 1; i < edificios.size(); i++) {
        if (edificios[i].comienzo >= ant.final) {
            res++;
            ant = edificios[i];
        }
    }
    return res;
}
bool resuelveCaso() {

    int N;
    cin >> N;
    if (N==0)  // fin de la entrada
        return false;
    tEdificio aux;
    vector<tEdificio> edificios(N);
    for (int i = 0; i < N; i++) {
        cin >> aux.comienzo >> aux.final;
        edificios[i] = aux;
    }
    // resolver el caso posiblemente llamando a otras funciones
    cout << resolver(edificios) << "\n";
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

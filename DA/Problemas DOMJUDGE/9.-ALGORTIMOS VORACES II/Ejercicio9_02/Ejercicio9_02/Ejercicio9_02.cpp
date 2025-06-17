
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
struct tPeriodos {
    int comienzo;
    int final;
};

bool operator <(const tPeriodos& a, const tPeriodos& b) {
    return (a.comienzo < b.comienzo) || (a.comienzo == b.comienzo && a.final > b.final);
}

int resolver(vector<tPeriodos>& trabajos, int C, int F) {
    sort(trabajos.begin(), trabajos.end());  // Ordenamos por comienzo y, en caso de empate, por final descendente.

    int sol = 0;
    int finalActual = C;
    int i = 0;
    bool haySolucion = false;

    while (i < trabajos.size() && finalActual < F) {
        int mejorAlcance = finalActual;

        // Buscar el intervalo que empieza antes o en `finalActual` y se extiende más allá
        while (i < trabajos.size() && trabajos[i].comienzo <= finalActual) {
            mejorAlcance = max(mejorAlcance, trabajos[i].final);
            i++;
        }

        if (mejorAlcance == finalActual) return -1;  // No hay intervalo que extienda `finalActual`, no se puede cubrir.

        finalActual = mejorAlcance;
        sol++;

        if (finalActual >= F) haySolucion = true;
    }

    return haySolucion ? sol : -1;
}



bool resuelveCaso() {

    int C, F, N;
    cin >> C >> F >> N;
    if (C==0 && F==0 && N==0)  // fin de la entrada
        return false;
    vector<tPeriodos> trabajos(N);
    for (int i = 0; i < N; i++) {
        cin >> trabajos[i].comienzo >> trabajos[i].final;
    }
    int sol = resolver(trabajos, C, F);
    if (sol == -1) cout << "Imposible";
    else cout << sol;
    cout << "\n";
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

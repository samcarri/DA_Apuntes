
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
#include "EnteroInf.h"
/*@ <answer>

Es un caso clasico del problema de cambio de monedas

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
vector<int> devolver_cambio(vector<int> const& M, int C) {
    int n = M.size();
    vector<EntInf> monedas(C + 1, Infinito);
    monedas[0] = 0;
    // calcular la matriz sobre el propio vector
    for (int i = 1; i <= n; ++i) {
        for (int j = M[i - 1]; j <= C; ++j) {
            monedas[j] = min(monedas[j], monedas[j - M[i - 1]] + 1);
        }
    }
    vector<int> sol;
    if (monedas[C] != Infinito) {
        int i = n, j = C;
        while (j > 0) { // no se ha pagado todo
            if (M[i - 1] <= j && monedas[j] == monedas[j - M[i - 1]] + 1) {
                // tomamos una moneda de tipo i
                sol.push_back(M[i - 1]);
                j = j - M[i - 1];
            }
            else // no tomamos más monedas de tipo i
                --i;
        }
    }
    return sol;
}
bool resuelveCaso() {

    int P, N;
    cin >> P >> N;
    if (!std::cin)  // fin de la entrada
        return false;
    vector<int> sectores(N);
    for(int i=0; i<N; i++) cin>>sectores[i];
    auto a = devolver_cambio(sectores, P);
    if (a.size() != 0) {
        cout << a.size() << ": ";
        for (int i = 0; i < a.size(); i++) {
            cout << a[i];
            if (i != a.size() - 1) cout << " ";

        }
    }
    else cout << "Imposible";
    cout << "\n";
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

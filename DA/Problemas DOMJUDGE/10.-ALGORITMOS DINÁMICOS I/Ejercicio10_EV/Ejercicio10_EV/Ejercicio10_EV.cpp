
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
/*@ <answer>

Basicamente consiste en analizar nodo por nodo su grado de entrada y de salida.
Si el grado de entrada es de N-1 y el de salida es 0 entonces estamos hablando de un nodo "sumidero".

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
struct Objeto { int peso; double valor; };
double mochila_rec(vector<Objeto> const& obj, int i, int j,
    Matriz<double>& mochila) {
    if (mochila[i][j] != -1) // subproblema ya resuelto
        return mochila[i][j];
    if (i == 0 || j == 0) mochila[i][j] = 0;
    else if (obj[i - 1].peso > j)
        mochila[i][j] = mochila_rec(obj, i - 1, j, mochila);
    else
        mochila[i][j] = max(mochila_rec(obj, i - 1, j, mochila),
            mochila_rec(obj, i - 1, j - obj[i - 1].peso, mochila)
            + obj[i - 1].valor);
    return mochila[i][j];
}
double mochila(vector<Objeto> const& objetos, int M, vector<bool>& sol) {
    int n = objetos.size();
    Matriz<double> mochila(n + 1, M + 1, -1);
    double valor = mochila_rec(objetos, n, M, mochila);
    // cálculo de los objetos
    int i = n, j = M;
    sol = vector<bool>(n, false);
    while (i > 0 && j > 0) {
        if (mochila[i][j] != mochila[i - 1][j]) {
            sol[i - 1] = true; j = j - objetos[i - 1].peso;
        }
        --i;
    }
    return valor;
}
bool resuelveCaso() {
    int P, N; //P-> pelas, N-> Num conciertos
    cin >> P >> N;
    if (!std::cin)  // fin de la entrada
        return false;
    vector<Objeto> conciertos(N);
    for (int i = 0; i < N; i++) {
        cin >> conciertos[i].valor >> conciertos[i].peso;
    }
    vector<bool> soluciones(N, false);
    cout << mochila(conciertos, P, soluciones) << "\n";
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

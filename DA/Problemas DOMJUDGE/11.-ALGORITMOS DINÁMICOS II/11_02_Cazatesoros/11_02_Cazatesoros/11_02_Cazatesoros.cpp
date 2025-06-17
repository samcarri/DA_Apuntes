
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
#include "Matriz.h"

/*@ <answer>

Basicamente consiste en analizar nodo por nodo su grado de entrada y de salida.
Si el grado de entrada es de N-1 y el de salida es 0 entonces estamos hablando de un nodo "sumidero".

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
struct Objeto {
    int peso;
    double valor;
};
double mochila_rec(vector<Objeto> const& obj, int i, int j, Matriz<double>& mochila) {
    if (mochila[i][j] != -1) // subproblema ya resuelto
        return mochila[i][j];

    if (i == 0 || j == 0)
        mochila[i][j] = 0;
    else if (obj[i - 1].peso > j)
        mochila[i][j] = mochila_rec(obj, i - 1, j, mochila);
    else
        mochila[i][j] = max(mochila_rec(obj, i - 1, j, mochila),
            mochila_rec(obj, i - 1, j - obj[i - 1].peso, mochila)
            + obj[i - 1].valor);

    return mochila[i][j];
}
double mochila(vector<Objeto> const& objetos, int M, vector<bool>& sol, int &contador) {
    int n = objetos.size();
    Matriz<double> mochila(n + 1, M + 1, -1);
    double valor = mochila_rec(objetos, n, M, mochila);
    
    // cálculo de los objetos
    int i = n, j = M;
    sol = vector<bool>(n, false);

    while (i > 0 && j > 0) {
        if (mochila[i][j] != mochila[i - 1][j]) {
            sol[i - 1] = true;
            contador++;
            j = j - objetos[i - 1].peso;
        }
        --i;
    }

    return valor;
}


bool resuelveCaso() {
    int T; //tiempo que se puede sumergir el maquinon
    int N; //numero de cofres en el agua
    int profundidad; 
    int contador = 0;
    double oro;
    cin >> T;

    if (!std::cin)  // fin de la entrada
        return false;
    cin >> N;
    vector<Objeto> cofres(N);
    for (int i = 0; i < N; i++) {
        cin >> profundidad >> oro;
        cofres[i] = { profundidad*2+profundidad, oro };
    }
    vector<bool> soluciones(N, false);
    cout << mochila(cofres, T, soluciones, contador) << "\n";
    cout << contador << "\n";
    for (int i = 0; i < soluciones.size(); i++) {
        if (soluciones[i]) cout << cofres[i].peso/3 << " " << cofres[i].valor << endl;
    }
    cout << "---" << endl;
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

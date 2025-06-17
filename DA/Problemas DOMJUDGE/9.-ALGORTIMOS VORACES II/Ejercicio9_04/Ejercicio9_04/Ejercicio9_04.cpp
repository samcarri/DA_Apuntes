
/*@ <answer>
 *
 * Nombre y Apellidos:Samuel Carrillo Menchero
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <deque>

using namespace std;


/*@ <answer>
La solución es muy parecida al problema anterior, ordenaremos a las personas de menor a mayor peso para posteriormente elegir a la persona con menos
y mas peso para subir juntas, en caso de que la suma de sus pesos no sea viable, subirá unicamente la persona más pesada.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
int resolver(deque<int>& personas, int P) {
    sort(personas.begin(), personas.end());
    int combi=0;
    int sol = 0;
    while (personas.size() != 0) {
        if (personas.size() != 1) {
            combi += personas.back() + personas.front();
            if (combi <= P) {
                //metemos a ambas personas
                personas.pop_front();
                personas.pop_back();
            }
            else {
                personas.pop_back(); //solo metemos a la mas pesada
            }
            combi = 0;
            sol++;
        }
        else {
            sol++;
            personas.pop_front();
        }
    }
    return sol;
}
bool resuelveCaso() {
    int P, N;
    cin >> P;
    if (!std::cin)  // fin de la entrada
        return false;
    cin >> N;
    deque<int> convencionDeFoskitos(N);
    for (int i = 0; i < N; i++) cin >> convencionDeFoskitos[i];

    cout << resolver(convencionDeFoskitos, P)<<"\n";
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

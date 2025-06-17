
/*@ <answer>
 *
 * Nombre y Apellidos: Samuel Carrillo Menchero
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "bintree.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
template <typename T>
int esAVL(const BinTree<T>& arbol, int nivel, int& max_izq, int& max_der) {
    if (arbol.empty()) {
        return nivel;
    }

    // Comprueba si los hijos existen antes de acceder a la raíz
    if (!arbol.left().empty() && arbol.left().root() > arbol.root()) return -1;
    if (!arbol.right().empty() && arbol.right().root() < arbol.root()) return -1;

    // Llamadas recursivas incrementando el nivel
    int izq = esAVL(arbol.left(), nivel + 1, max_izq, max_der);
    int der = esAVL(arbol.right(), nivel + 1, max_izq, max_der);

    // Si alguna de las llamadas recursivas devuelve -1, no es AVL
    if (izq == -1 || der == -1) return -1;

    // Actualización de las alturas máximas
    if (izq > max_izq) max_izq = izq;
    if (der > max_der) max_der = der;

    // Verificación del balance de alturas
    if (abs(izq - der) > 1) return -1;

    return max(izq, der);  // Devuelve la altura máxima
}

bool resuelveCaso() {
    char tipo;
    cin >> tipo;
    int max_izq = 0;
    int max_der = 0;
    if (!std::cin)  // fin de la entrada
        return false;

    if (tipo == 'N') {
        BinTree<int> arbolEnteros=read_tree<int>(cin);
        if (esAVL(arbolEnteros, 0, max_izq, max_der) == -1) {
            std::cout << "NO" << "\n";
            return false;
        }
        else std::cout << "SI" << "\n";
    }
    else {
        BinTree<char> arbolChars=read_tree<char>(cin);
  
        if (esAVL(arbolChars, 0, max_izq, max_der) == -1) {
            std::cout << "NO" << "\n";
            return false;
        }
        else std::cout << "SI" << "\n";
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

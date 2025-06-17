
/*@ <answer>
 *
 * Nombre y Apellidos:Samuel Carrillo Menchero
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct tUsuario {
    int ID;
    int tiempo;
    int inicial;
};

bool operator<(tUsuario const& a, tUsuario const& b) {
    return b.tiempo > a.tiempo ||
        (a.tiempo == b.tiempo && b.ID> a.ID);
}
void monitoriza(PriorityQueue<tUsuario>& ids,int K, int N) {
    int veces = 0;
  for(int i=0; i<K; i++) {
        auto usuario = ids.top();
        ids.pop();
        std::cout << usuario.ID << "\n";
        usuario.tiempo += usuario.inicial;
        ids.push(usuario);

  }
    std::cout << "---" << "\n";
}
bool resuelveCaso() {

    // leer los datos de la entrada
    int K, N;
    tUsuario usuarios;
    PriorityQueue<tUsuario> ids;
    cin >> N;
    if (N==0)  return false;
    for (int i = 0; i < N; i++) {
        cin >> usuarios.ID >> usuarios.tiempo;
        usuarios.inicial = usuarios.tiempo;
        ids.push(usuarios);
      }
    cin >> K;
    // resolver el caso posiblemente llamando a otras funciones
    monitoriza(ids, K,N);
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

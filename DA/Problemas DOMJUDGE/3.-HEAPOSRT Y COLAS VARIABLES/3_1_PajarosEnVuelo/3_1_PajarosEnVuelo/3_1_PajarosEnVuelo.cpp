
/*@ <answer>
 *
 * Nombre y Apellidos: Samuel Carrillo Menchero
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>
   Resolución: 
   El resultado pasa por hacer dos colas de prioridad, una siempre una unidad mayor que la otra, es decir:
   IndexPQ<int, int> menores; 
   IndexPQ<int, int> mayores;
   menores almacenará a los pajaros de menor edad incluyendo al "lider", por lo tanto su longitud será de (N/2)+1.
   
   Para el siguiente ejemplo:
   30 3
   10 20 35 25 5 40
   Las colas deberian quedar de la siguiente forma:
 minimos: 5 10 20 25
  maximos: 40 30 30

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {

    // leer los datos de la entrada
    int E, N; //EDAD Y NUMERO DE PAJAROS
    cin >> E >> N;
    if (E==0 && N==0)
        return false;
    PriorityQueue<int> pajaros_mayores;
    PriorityQueue<int, std::greater<int>> pajaros_peques;
    pajaros_peques.push(E);
    /* PRUEBA
    pajaros_peques.push(1,1);
    pajaros_peques.push(2, 2);
    pajaros_peques.push(3, 3);
    pajaros_mayores.push(1, 1);
    pajaros_mayores.push(2, 2);
    pajaros_mayores.push(3, 3);
    while (!pajaros_peques.empty()) {
        cout << pajaros_peques.top().elem << " ";
        pajaros_peques.pop();
    }
    cout << "\n";
    */
    int edad, aux;

 
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 2; j++) {
            cin >> edad;
            /*Metemos los elementos*/
            if (edad > pajaros_peques.top()) pajaros_mayores.push(edad);
            else pajaros_peques.push(edad);
            /*Vemos si las listas han quedado descuadras*/
            //2 3 4 5 6 7
            if (pajaros_mayores.size() > pajaros_peques.size()) {
                edad = pajaros_mayores.top();
                pajaros_peques.push(edad);
                pajaros_mayores.pop();
            }
            else if (pajaros_peques.size() >= pajaros_mayores.size() + 1) {
              
                pajaros_mayores.push(pajaros_peques.top());
                pajaros_peques.pop();
            
            }

        }
        cout << pajaros_peques.top()<<" ";
   }
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

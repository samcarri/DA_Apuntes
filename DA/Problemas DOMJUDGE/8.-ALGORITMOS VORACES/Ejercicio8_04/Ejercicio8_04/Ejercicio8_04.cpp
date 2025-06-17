
/*@ <answer>
 *
 * Nombre y Apellidos:Samuel Carrillo Menchero
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <string>
#include <vector>
using namespace std;


/*@ <answer>

El resultado pasa por ordenar la peliculas en torno a su hora de comienzo, en caso de que que este sea igual a otra lo ordenaremos por su hora de finalizacion
visto esto elegiremos las peliculas que no se interseccionen

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
struct tHora {
    int comienzo;
    int fin;
};

bool operator <(const tHora& a, const tHora& b) {
    if (a.fin != b.fin) {
        return a.fin < b.fin;  // Ordenar por hora de fin
    }
    else {
        return a.comienzo < b.comienzo;  // En caso de empate, ordenar por hora de comienzo
    }
}
int transformarHora(const std::string& hora) {
    // Extraemos las partes de hora y minutos sin modificar el formato original
    std::string horas = hora.substr(0, 2);   // Toma los dos primeros caracteres (horas)
    std::string minutos = hora.substr(3, 2); // Toma los dos últimos caracteres (minutos)

    // Concatenamos las horas y minutos y convertimos el resultado a entero
    int hora_int = std::stoi(horas + minutos);

    return hora_int;
}
int devolverHoraFinal(int hora, int duracion) {
    // Extraer horas y minutos de la hora inicial
    int horas = hora / 100;
    int minutos = hora % 100;

    // Sumar la duración
    horas += duracion / 60;         // Agregar las horas de la duración
    minutos += duracion % 60;       // Agregar los minutos de la duración

    // Ajustar en caso de que los minutos superen 60
    if (minutos >= 60) {
        horas += minutos / 60;
        minutos %= 60;
    }

    // Convertir el resultado a formato de hora entero (HHMM)
    return horas * 100 + minutos;
}
int resolver(vector<tHora> horas) {
        int res= 1;
        int comienzo_actual = horas[0].comienzo;
        int final_actual = horas[0].fin;
        for (int i = 1; i < horas.size(); i++) {
            if (final_actual < horas[i].comienzo) {
                res++;
                final_actual = horas[i].fin;

            }
        }
    return res;
}

bool resuelveCaso() {
    int N, hora, duracion;
    string hora_string;
    cin >> N;
    if (N==0)  // fin de la entrada
        return false;
    vector<tHora> peliculas(N);
    for (int i = 0; i < N; i++) {
        cin >> hora_string >> duracion;
        int hora_comienzo = transformarHora(hora_string);
        //cout << hora_comienzo << "-"<<devolverHoraFinal(hora_comienzo, duracion)<<"\n";
        peliculas[i] = { hora_comienzo, devolverHoraFinal(hora_comienzo, duracion) };
    }
 
    cout <<resolver(peliculas)<< "\n";
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

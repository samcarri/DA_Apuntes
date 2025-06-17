/**
 * Nombre y usuario de cada miembro de la pareja
 * Samuel Carrillo Menchero
 * Yago Sanabria Gavin
 *
 * Explica tu código:
 * Básicamente consiste en actualizar en la cola de prioridad el tiempo de visión de cada uno de los
 * espectadores y posteriormente en un vector a parte (que va a ser el resultado) ir añadiendo el tiempo en el que se ha
 * encontrado en prime time cada programa, para ello nos guardamos el minuto anterior al actual y el actual y calculamos el intervalo
 * para sumarselo al vector de indice correspondiente.
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "IndexPQ.h"
#include "PriorityQueue.h"

using namespace std;

struct Canal {
    int indice;
    int minutos;
};

bool operator<(Canal const& a, Canal const& b) {
    return b.minutos < a.minutos ||
        (a.minutos == b.minutos && b.indice > a.indice);
}

void resolver(IndexPQ<int, std::greater<int>>& canales_audiencia, int D, int N) {
    vector<int> minutos_totales_audiencia(canales_audiencia.size(), 0); // Almacena el tiempo que cada canal fue el más visto
    int ultimo_canal = canales_audiencia.top().elem; // Canal más visto al inicio
    int tiempo = 0; // Acumula tiempo de duración que el último canal fue el más visto
    int minuto_anterior = 0; // Para llevar la cuenta del minuto anterior
    int minuto;
    int indice;
    int audiencia;

    // Iteramos sobre las actualizaciones
    for (int i = 0; i < N; i++) {
        cin >> minuto; // Leer minuto de actualización
        // Si hay tiempo acumulado desde el último minuto registrado
        if (minuto > minuto_anterior) {
            minutos_totales_audiencia[ultimo_canal] += minuto - minuto_anterior;
        }
        minuto_anterior = minuto; // Actualizar el minuto anterior

        cin >> indice; // Leer el primer canal a actualizar

        // Procesar las actualizaciones
        while (indice != -1) {
            cin >> audiencia; // Leer audiencia del canal
            canales_audiencia.update(indice - 1, audiencia); // Actualizar el canal
            cin >> indice; // Leer el siguiente canal
        }

        // Obtener el nuevo canal más visto
        int nuevo_canal = canales_audiencia.top().elem;

        // Si el canal más visto ha cambiado, actualizamos
        if (nuevo_canal != ultimo_canal) {
            // Acumular el tiempo que el último canal fue el más visto
            ultimo_canal = nuevo_canal; // Cambiamos el último canal más visto
        }
    }

    // Al final, necesitamos sumar el tiempo que el último canal fue el más visto hasta el final de la franja
    minutos_totales_audiencia[ultimo_canal] += D - minuto_anterior;

    // Imprimir los resultados
    vector<Canal> resultados;
    for (int i = 0; i < canales_audiencia.size(); ++i) {
        if (minutos_totales_audiencia[i] > 0) {
            resultados.push_back({ i, minutos_totales_audiencia[i] });
        }
    }

    // Ordenar resultados
    sort(resultados.begin(), resultados.end()); 

    // Imprimir resultados
    for (int i = 0; i<resultados.size(); i++) {
        cout << resultados[i].indice + 1 << " " << resultados[i].minutos << endl; // Sumar 1 al índice para mostrar el canal
    }
    cout << "---" << endl; // Separador entre casos
}

bool resuelveCaso() {
    int D, C, N; // Duración del prime time, número de canales y número de actualizaciones
    cin >> D >> C >> N;
    if (!cin) return false;

    IndexPQ<int, std::greater<int>> canales_audiencia(C); // Usamos greater<int> para tener el canal con mayor audiencia en top
    long int audiencia;
    for (int i = 0; i < C; i++) {
        cin >> audiencia;
        canales_audiencia.push(i, audiencia); // Inicializamos la cola con las audiencias iniciales
    }

    resolver(canales_audiencia, D, N); // Llamamos a la función resolver
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}

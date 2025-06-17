#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

#include "Digrafo.h" // propios o los de las estructuras de datos de clase

class Necronomiqueando {
public:
    Necronomiqueando(Digrafo const& g, int l) : visit(g.V(), false), ant(g.V()),
        apilado(g.V(), false), hayciclo(false), llegado(false) {
        for (int v = 0; v < g.V(); ++v)
            if (!visit[v])
                dfs(g, v,l);
    }
    bool hayCiclo() const { return hayciclo; }
    bool Sano() const { return llegado; }
    deque<int> const& ciclo() const { return _ciclo; }
private:
    std::vector<bool> visit; // visit[v] = ¿se ha alcanzado a v en el dfs?
    std::vector<int> ant; // ant[v] = vértice anterior en el camino a v
    std::vector<bool> apilado; // apilado[v] = ¿está el vértice v en la pila?
    deque<int> _ciclo; // ciclo dirigido (vacío si no existe)
    bool hayciclo;
    bool llegado;
   
    void dfs(Digrafo const& g, int v, int l) {
        apilado[v] = true;
        visit[v] = true;
        for (int w : g.ady(v)) {
            if (!visit[w]) { // encontrado un nuevo vértice, seguimos
                if (w == l)
                    llegado = true;
                ant[w] = v;
                dfs(g, w, l);
            }
            else if (apilado[w]) { // hemos detectado un ciclo
                hayciclo = true;
                for (int x = v; x != w; x = ant[x])
                    _ciclo.push_front(x);
                _ciclo.push_front(w);
                _ciclo.push_front(v);
            }
        }
        apilado[v] = false;
    }

};

bool resuelveCaso() {
    int l; //num intrucciones programa oscuro
    char instruc;
    int n;
    cin >> l;


    // leer los datos de la entrada

    if (!std::cin)  return false;
    Digrafo d(l + 1);
    for (int i = 0; i < l; i++) {

        cin >> instruc;
        if (instruc == 'A') {//instruciones aritmeticas.
            d.ponArista(i, i + 1);
        }
        else if (instruc == 'J') {//salto normal
            cin >> n;
            d.ponArista(i, n - 1);
        }
        else if (instruc == 'C') { //salto condicional
            cin >> n;
            d.ponArista(i, i + 1);
            d.ponArista(i, n - 1);
        }
      
    }

    // escribir la solución
    Necronomiqueando necronomicon(d,l);

    // resolver el caso posiblemente llamando a otras funciones
    
    if (!necronomicon.Sano()) {
        cout << "NUNCA"; 
    }
    else if (necronomicon.Sano() && necronomicon.hayCiclo()) {
        cout << "A VECES";
    }
    else {
        cout << "SIEMPRE";
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

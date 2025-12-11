#include <iostream>
#include "Grafo.h"
#include "tabulate/table.hpp" 
#include <list>
#include <map>

#include "Floyd.h"

using namespace tabulate;
using namespace std;



void DFS(Grafo<int> &g, int v, map<int, bool> &visitado, list<int> &camino) {
    visitado[v] = true;
    list<Grafo<int>::Arco> adyacentes;
    g.devolverAdyacentes(v, adyacentes);

    for (const auto &arco : adyacentes) {
        int adyacente = arco.devolverAdyacente();
        if (!visitado[adyacente]) {
            camino.push_back(adyacente);
            DFS(g, adyacente, visitado, camino);
        }
    }
    
}

void bosqueDFS(Grafo<int> g,list<int> &camino){
    list<int> vertices;
    g.devolverVertices(vertices);
    map<int, bool> visitado;
    for (const auto &v : vertices) {
        visitado[v] = false;
    }

    for (const auto &v : vertices) {
        if (!visitado[v]) {
            camino.push_back(v);
            DFS(g, v, visitado,camino);
        }
    }
}

void BFS(Grafo<int> &g, int inicio, map<int, bool> &visitado, list<int> &camino) {
    list<int> cola;
    visitado[inicio] = true;
    cola.push_back(inicio);

    while (!cola.empty()) {
        int v = cola.front();
        cola.pop_front();
        camino.push_back(v);

        list<Grafo<int>::Arco> adyacentes;
        g.devolverAdyacentes(v, adyacentes);

        for (const auto &arco : adyacentes) {
            int adyacente = arco.devolverAdyacente();
            if (!visitado[adyacente]) {
                visitado[adyacente] = true;
                cola.push_back(adyacente);
            }
        }
    }
}

void bosqueBFS(Grafo<int> g, list<int> &camino){
    list<int> vertices;
    g.devolverVertices(vertices);
    map<int, bool> visitado;
    for (const auto &v : vertices)
        visitado[v] = false;

    for (const auto &v : vertices) 
        if (!visitado[v]) {
            //camino.push_back(v);
            BFS(g, v, visitado, camino);
        }
}

void imprimirListaAdyacentes(const list<Grafo<int>::Arco>& listaAdyacentes) {
    cout << "Lista de Adyacentes:\n";
    for (const auto& arco : listaAdyacentes) {
        cout << "Vértice: " << arco.devolverAdyacente() 
             << ", Costo: " << arco.devolverCosto() << "\n";
    }
}



int main() {
    

    Grafo<int> G = Grafo<int>(false);
    G.agregarVertice(1);
    G.agregarVertice(2);    
    G.agregarVertice(3);
    G.agregarVertice(4);
    G.agregarVertice(5);
    G.agregarVertice(6);
    
    G.agregarArco(1, 2, 3);
    G.agregarArco(1, 3, 5);
    G.agregarArco(1, 4, 1);

    G.agregarArco(2, 5, 9);

    G.agregarArco(3, 5, 7);
    G.agregarArco(3, 4, 7);
    G.agregarArco(3, 6, 1);

    G.agregarArco(4, 6, 4);
     
    Floyd floyd(G);
    
    int i =0;
    for (const Table& tabla : floyd.getListaDeTablas()) {
        std::cout << tabla << "\n\n";
        i++;
        if(i!=0 && i%2==0){
            std::cout << "----------------------------------\n";
        }
    }


    std::cout << "FIN"<< std::endl;
    
    return 0;
}
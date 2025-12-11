#include <iostream>
#include "Grafo.h"
#include "tabulate/table.hpp" 
#include <list>
#include <map>

#include "Floyd.h"
#include "Dijkstra.h"

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
    

    Grafo<int> G = Grafo<int>(true);
    G.agregarVertice(1);
    G.agregarVertice(2);    
    G.agregarVertice(3);
    G.agregarVertice(4);
    G.agregarVertice(5);
    
    G.agregarArco(1, 2, 10);
    G.agregarArco(1, 4, 30);
    G.agregarArco(1, 5, 100);

    G.agregarArco(2, 3, 50);

    G.agregarArco(3, 5, 10);

    G.agregarArco(4, 3, 20);
    G.agregarArco(4, 5, 60);
     
    Dijkstra dijkstra(G,1);

    
    cout<< dijkstra.getaTablaDijkstra() << std::endl;
    

    std::cout << "FIN"<< std::endl;
    
    return 0;
}
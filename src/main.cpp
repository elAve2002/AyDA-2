#include <iostream>
#include "Grafo.h"
#include "tabulate/table.hpp" 
#include <list>
#include <map>

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
    

    list<int> camino;
    Grafo<int> G = Grafo<int>(false);
    G.agregarVertice(1);
    G.agregarVertice(2);    
    G.agregarVertice(3);
    G.agregarVertice(4);
    G.agregarVertice(5);
    G.agregarVertice(6);
    G.agregarVertice(7);
    G.agregarVertice(8);
    G.agregarVertice(9);
    G.agregarVertice(10);
    G.agregarVertice(11);

    G.agregarArco(1, 2, 0);
    G.agregarArco(1, 3, 0);
    G.agregarArco(1, 9, 0);

    G.agregarArco(2, 6, 0);
    G.agregarArco(2, 3, 0);

    G.agregarArco(3, 4, 0);

    G.agregarArco(4, 6, 0);

    G.agregarArco(5, 7, 0);

    G.agregarArco(6, 5, 0);
    G.agregarArco(6, 7, 0);
    G.agregarArco(6, 8, 0);

    G.agregarArco(9, 10, 0);
    G.agregarArco(9, 11, 0);

    bosqueBFS(G,camino);

    cout << "Recorrido BFS del grafo:\n";
    for (const auto &v : camino) {
        cout << v << " ";
    }
    cout << std::endl;  


    /*
    // Crear tabla
    Table table;
    
    table.add_row({"Nodo", "Grado", "Visitado", "Color"});
    table.add_row({"A", "2", "Sí", "Rojo"});
    table.add_row({"B", "3", "No", "Azul"});
    table.add_row({"C", "1", "Sí", "Verde"});
    


    // Formatear
    table.format()
        .font_style({FontStyle::bold})
        .border_top("═")
        .border_bottom("═");
    
    std::cout << "Información del Grafo:\n";
    std::cout << table << std::endl;*/
    
    return 0;
}
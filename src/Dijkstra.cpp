#include "Dijkstra.h"




string Dijkstra::formatValue(int value) const {
    if (value == INT_MAX) {
        return "INF";
    } else {
        return std::to_string(value);
    }
}

string Dijkstra::listaAString(list<int> l) const {
    string resultado = "{ ";
    for (const auto &vertice : l) {
        resultado += std::to_string(vertice) + ", ";
    }
    resultado += "}";
    return resultado;
}


/*
Table Dijkstra::creaTabla(vector<vector<int>> mat, list<int> s, int v) const {
    Table tabAux;

    using RowType = std::vector<std::variant<std::string, const char*, std::string_view, Table>>;
    
    RowType primeraFila;
    
    primeraFila.push_back("S");
    primeraFila.push_back("V");
    
    list<int> vertices;
    grafo.devolverVertices(vertices);
    
    for(const auto &vertice : vertices){
        primeraFila.push_back("D(" + std::to_string(vertice) + ")");
    }
    
    tabAux.add_row(primeraFila);

    for(const auto &fila : mat){
        RowType filaStr;
        filaStr.push_back(listaAString(s));
        filaStr.push_back(std::to_string(v));
        
        for(const auto &valor : fila){
            if(valor == INT_MAX){
                filaStr.push_back("INF");
            } else if(valor < 0){
                filaStr.push_back(std::to_string(valor) + "*");
            }else {
                filaStr.push_back(std::to_string(valor));
            }
        }
        tabAux.add_row(filaStr);
    }

    // Configurar anchos: primera columna 10, resto 6
    for (size_t row = 0; row < tabAux.size(); ++row) {
        for (size_t col = 0; col < tabAux[row].size(); ++col) {
            if (col == 0) {
                // Primera columna: ancho 10
                tabAux[row][col].format()
                    .width(ANCHO_PRIMERA_COLUMNA)                    
                    .font_align(FontAlign::center)
                    .padding_left(0)             
                    .padding_right(0)
                    .multi_byte_characters(true);
            } else {
                // Resto de columnas: ancho 6
                tabAux[row][col].format()
                    .width(ANCHO_OTRAS_CELDAS)                    
                    .font_align(FontAlign::center)
                    .padding_left(0)             
                    .padding_right(0)
                    .multi_byte_characters(true);
            }
        }
    }
    
    tabAux.format()
        .border_top("═")
        .border_bottom("═")
        .border_left("║")
        .border_right("║")
        .corner("╬");
     
    return tabAux;
}
*/

Dijkstra::Dijkstra(Grafo<int> &g, int vertice) : grafo(g) {

    //grafo.devolverVertices(listaS);
    this->verticeInicio = vertice;


    using RowType = std::vector<std::variant<std::string, const char*, std::string_view, Table>>;
    
    RowType primeraFila;
    primeraFila.push_back("S");
    primeraFila.push_back("V");
    
    list<int> vertices;
    grafo.devolverVertices(vertices);
    
    for(const auto &vertice : vertices){
        primeraFila.push_back("D(" + std::to_string(vertice) + ")");
    }

    this->tablaDijkstra.add_row(primeraFila); 

    // inicio del algoritmo

    list<int> S;
    S.push_back(verticeInicio);  // S conjunto de vértices ya calculados, inicialmente S={f}

    map<int, int> D;  // Mapa de distancias desde el vértice inicial
    for (const auto &v : vertices) {
        if (v == verticeInicio) {
            D[v] = 0;
        } else if (grafo.existeArco(verticeInicio, v)) {
            D[v] = grafo.costoArco(verticeInicio, v);
        } else {
            D[v] = INT_MAX; 
        }
    }
    
    map<int,int> P; // P(i) es el vertice anterior a i en el camino desde f
    list<int> v;
    g.devolverVertices(v);

    int n = g.devolverLongitud();
    for (int i=1; i<n; i++){
        int w = getVerticeDMin(v,S,D);
        S.push_back(w);

        for(const auto &vertice: disponiblesYAdy(v,S,w)){
            int costo = grafo.costoArco(w, vertice);
            if (D[vertice] > D[w] + costo) {
                D[vertice] = D[w] + costo;
                P[vertice] = w;
            }

        }



    }


}


list<int> Dijkstra::disponibles(list<int>v, list<int> s) const{ // los vertices disponibles son V-S
    list<int> resultado;

    for(const auto &temp: v){
        auto it = find(s.begin(), s.end(), temp);
        if (it != s.end()){
            resultado.push_back(temp);
        }
    }

    return resultado;
}

list<int> Dijkstra::disponiblesYAdy(list<int> v, list<int> s, int vertice) const {
    list<int> resultado;
    list<int> disponiblesList = disponibles(v, s);
    list<int> adyacentes;

    grafo.devolverAdyacentesVertices(vertice, adyacentes);

    // Intersección: solo los que están en ambos
    for (const auto &elem : adyacentes) {
        auto it = std::find(disponiblesList.begin(), disponiblesList.end(), elem);
        if (it != disponiblesList.end()) { // si está en disponibles
            resultado.push_back(elem);
        }
    }

    return resultado;
}

int Dijkstra::getVerticeDMin(list<int> v,list<int> s, map<int, int> d) const {
    int min = INT_MAX;
    
    for (const auto &temp : disponibles(v,s)) {
        auto it = d.find(temp); 
        if (it != d.end()) {
            if (it->second <= min)
                min = it->second;
        }
    }

    return min;
}

Dijkstra::~Dijkstra() {
    // Destructor
}


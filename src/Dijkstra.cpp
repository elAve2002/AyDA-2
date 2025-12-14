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

    this->listaS.push_back(verticeInicio);  // S conjunto de vértices ya calculados, inicialmente S={f}

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


    RowType filaTempa;

    filaTempa.push_back(listaAString(listaS));
    filaTempa.push_back("-");
    for (const auto &v : vertices) {
        if(verticeInicio == v){
            filaTempa.push_back("0*");
        } else if(grafo.existeArco(verticeInicio, v)){
            filaTempa.push_back(formatValue(D[v]));
        } else {
            filaTempa.push_back("INF");
        }
    }

    tablaDijkstra.add_row(filaTempa);

    int n = vertices.size();

    for(int i = 0; i < n - 1; ++i){  // Repetir n-1 veces

        // Encontrar el vértice fuera de S con la distancia mínima
        int minDist = INT_MAX;
        int verticeMin = -1;
        for (const auto &v : vertices) {
            if (std::find(listaS.begin(), listaS.end(), v) == listaS.end()) { // Si v no está en S
                if (D[v] < minDist) {
                    minDist = D[v];
                    verticeMin = v;
                }
            }
        }

        listaS.push_back(verticeMin);


        RowType filaTemp;

        filaTemp.push_back(listaAString(listaS));
        filaTemp.push_back(std::to_string(verticeMin));

        list<int> adyacentesAMin;
        grafo.devolverAdyacentesVertices(verticeMin, adyacentesAMin);

        for(const auto &v: adyacentesAMin){
            if (std::find(listaS.begin(), listaS.end(), v) == listaS.end()) { // Si v no está en S
                int nuevaDist = (D[verticeMin] == INT_MAX) ? INT_MAX : D[verticeMin] + grafo.costoArco(verticeMin, v);
                if (nuevaDist < D[v]) {
                    D[v] = nuevaDist;
                }
            }
        }

    }



    



}

Dijkstra::~Dijkstra() {
    // Destructor
}


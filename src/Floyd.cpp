#include "Floyd.h"

string Floyd::formatValue(int value) const {
    if (value == INT_MAX) {
        return "INF";
    } else {
        return std::to_string(value);
    }
}

Table Floyd::crearTabla(vector<vector<int>> M, char tipo) const {
    Table tabla;


    list<int> vertices;
    this->grafo.devolverVertices(vertices);

    vector<int> vertices_vec(vertices.begin(), vertices.end());
    
    // Encabezado
    vector<variant<string, const char*, string_view, Table>> encabezadoA;
    encabezadoA.push_back(tipo + to_string(this->nroTabla));
    for (const auto &v : vertices_vec) {
        encabezadoA.push_back(to_string(v));
    }
    tabla.add_row(encabezadoA);

    // Filas de datos
    size_t i = 0;
    for (const auto &fila : M) {
        vector<variant<string, const char*, string_view, Table>> filaStr;
        filaStr.push_back(to_string(vertices_vec[i]));
        
        for (const auto &valor : fila) {
            if (valor == INT_MAX) {
                filaStr.push_back("INF");  // Usar "INF" en lugar de "∞" para mejor alineación
            } else {
                filaStr.push_back(to_string(valor));
            }
        }
        tabla.add_row(filaStr);
        i++;
    }

    // APLICAR ANCHO FIJO DE 6 A TODAS LAS CELDAS
    // IMPORTANTE: Aplicar primero el ancho, luego el formato general
    
    // 1. Aplicar ancho fijo de 6 a cada celda
    for (size_t row = 0; row < tabla.size(); ++row) {
        for (size_t col = 0; col < tabla[row].size(); ++col) {
            tabla[row][col].format()
                .width(6)                    // Ancho fijo de 6 caracteres
                .font_align(FontAlign::center)
                .padding_left(0)             // Sin padding para mejor alineación
                .padding_right(0)
                .multi_byte_characters(true); // Para caracteres especiales
        }
    }
    
    // 2. Aplicar formato de bordes (después del width)
    tabla.format()
        .border_top("═")
        .border_bottom("═")
        .border_left("║")
        .border_right("║")
        .corner("╬");

    return tabla;
}

Floyd::Floyd(Grafo<int> &g) : grafo(g) {
    this->nroTabla = 0;

    list<int> vertices;
    g.devolverVertices(vertices);
    
    // Obtener tamaño de vértices
    int n = vertices.size();
    
    // Inicializar matrizA con el tamaño correcto
    matrizA = vector<vector<int>>(n, vector<int>(n, INT_MAX));
    
    // Inicializar matrizP con el tamaño correcto
    matrizP = vector<vector<int>>(n, vector<int>(n, 0));
    
    // Mapear vértices a índices
    map<int, int> indiceVertice;
    int idx = 0;
    for (int v : vertices) {
        indiceVertice[v] = idx++;
    }

    // Llenar matrizA
    for (const auto &f : vertices) {
        int i = indiceVertice[f];
        for (const auto &c : vertices) {
            int j = indiceVertice[c];
            
            if (f == c) {
                matrizA[i][j] = 0;
            } else if (g.existeArco(f, c)) {
                matrizA[i][j] = g.costoArco(f, c);
            }
        }
    }

    this->listaDeTablas.push_back(crearTabla(this->matrizA,'A'));
    this->listaDeTablas.push_back(crearTabla(this->matrizP,'P'));

    this->nroTabla++;

    floyd();


}

Floyd::~Floyd(){

}


std::list<Table> Floyd::getListaDeTablas() const {
    return this->listaDeTablas;
}

void Floyd::floyd(){  //complejidad O(n^3)

    size_t n = matrizA.size();

    for (size_t k = 0; k < n; ++k) {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (matrizA[i][k] != INT_MAX && matrizA[k][j] != INT_MAX) {
                    int nuevoCosto = matrizA[i][k] + matrizA[k][j];
                    if (nuevoCosto < matrizA[i][j]) {
                        matrizA[i][j] = nuevoCosto;
                        matrizP[i][j] = k + 1; // +1 para ajustar al índice del vértice

                    }
                }
            }
        }

                        listaDeTablas.push_back(crearTabla(this->matrizA,'A'));
                        listaDeTablas.push_back(crearTabla(this->matrizP,'P'));
                        this->nroTabla++;
    }
}


void Floyd::caminoMinimo(int origen, int destino, list<int> &camino) const {

    unsigned int k = matrizP[origen - 1][destino - 1];

    if(k>0){
        caminoMinimo(origen, k, camino);
        camino.push_back(k);
        caminoMinimo(k, destino, camino);
    }
    
}

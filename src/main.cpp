// main.cpp
#include <iostream>
#include "Grafo.h"
#include "tabulate/table.hpp"  // Si está en include/

using namespace tabulate;

int main() {
    
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
    std::cout << table << std::endl;
    
    return 0;
}
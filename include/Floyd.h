#ifndef FLOYD_H 
#define FLOYD_H

#include <iostream>
#include "Grafo.h"
#include <list>
#include <climits>
#include "tabulate/table.hpp" 
#include <string>
// floyd se basa en programacion dinamica, asiq se vuelca el grafo en una tabla y se trabaja con la tabla
using namespace tabulate;
using namespace std;

class Floyd{
    
    private:
        Grafo<int> &grafo;
        std::list<Table> listaDeTablas;
        int nroTabla;

        vector<vector<int>> matrizA;
        vector<vector<int>> matrizP;

        string formatValue(int value)const;
        Table crearTabla(vector<vector<int>> M, char tipo) const;

        void floyd();


    public:
        list<Table> getListaDeTablas() const;
        void caminoMinimo(int origen, int destino, list<int> &camino) const;

        Floyd(Grafo<int> &g);
        ~Floyd();
};


#endif
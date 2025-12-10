#include <iostream>
#include "Grafo.h"
#include <list>
#include <climits>
#include "tabulate/table.hpp" 
#include <string>

using namespace tabulate;

template <typename C>
class Floyd{
    
    private:
        Grafo<C> &grafo;
        std::list<Table> listaDeTablas;

    public:

        Floyd(Grafo<C> &g);
        ~Floyd();
};
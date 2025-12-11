#include <string>
#include <list>
#include <vector>
#include "Grafo.h"
#include <climits>
#include "tabulate/table.hpp" 


using namespace tabulate;
using namespace std;


class Dijkstra{
private:
    Grafo<int> grafo;
    list<int> listaS;
    Table tablaDijkstra;
    int verticeInicio;

    const int ANCHO_PRIMERA_COLUMNA = 16;
    const int ANCHO_OTRAS_CELDAS = 6;


public:
    Dijkstra(Grafo<int> &g, int vertice);
    ~Dijkstra();

    string formatValue(int value) const;
    string listaAString(list<int> l)const;

    Table getaTablaDijkstra() const {return tablaDijkstra;}




};

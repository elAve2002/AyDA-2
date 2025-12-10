#include "Floyd.h"

template <typename C>
Floyd<C>::Floyd(Grafo<C> &g){
    this->grafo = g;
    this->nroTabla = 0;
}

template <typename C>
Floyd<C>::~Floyd(){

}

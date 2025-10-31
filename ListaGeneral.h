#ifndef LISTAGENERAL_H
#define LISTAGENERAL_H

#include "Nodo.h"
#include "SensorBase.h"

// interfaz
class ListaGeneral
{
private:
    Nodo<SensorBase *> *cabeza;

public:
    ListaGeneral() : cabeza(nullptr) {};
    ~ListaGeneral();
    void insertar(SensorBase *valor);
    bool estaVacia();
    void procesarTodos();
    void imprimirTodos() const;
    SensorBase* buscarPorNombre(const char* nombre);
};
#endif
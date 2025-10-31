#ifndef NODO_H
#define NODO_H

template <typename T>
class Nodo
{
public:
    Nodo<T> *siguiente;
    T valor;

    // constructor
    Nodo(T valor)
    {
        this->valor = valor;
        this->siguiente = nullptr;
    };
};

#endif
#ifndef NODO_H
#define NODO_H

/**
 * @file Nodo.h
 * @brief Nodo simple para listas enlazadas genéricas.
 *
 * Plantilla de nodo utilizada por las estructuras de lista del proyecto.
 * Contiene el valor y un puntero al siguiente nodo.
 *
 * @tparam T Tipo almacenado en el nodo.
 */

template <typename T>
class Nodo
{
public:
    Nodo<T> *siguiente; /**< Puntero al siguiente nodo. */
    T valor;            /**< Valor almacenado en el nodo. */

    /**
     * Constructor.
     * @param valor Valor a almacenar en el nodo.
     */
    Nodo(T valor)
    {
        this->valor = valor;
        this->siguiente = nullptr;
    };
};

#endif
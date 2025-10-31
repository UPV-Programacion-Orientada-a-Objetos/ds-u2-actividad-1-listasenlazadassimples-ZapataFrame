#ifndef LISTAGENERAL_H
#define LISTAGENERAL_H

/**
 * @file ListaGeneral.h
 * @brief Contenedor genérico de sensores (lista enlazada).
 *
 * Implementa una lista enlazada simple que almacena punteros a SensorBase.
 * Proporciona operaciones básicas: inserción, búsqueda y recorrido para
 * procesar o imprimir información de los sensores.
 */

#include "Nodo.h"
#include "SensorBase.h"

class ListaGeneral
{
private:
    Nodo<SensorBase *> *cabeza; /**< Cabeza de la lista. */

public:
    ListaGeneral() : cabeza(nullptr) {};
    ~ListaGeneral();

    /**
     * Inserta un sensor al final de la lista.
     * @param valor Puntero al sensor a insertar.
     */
    void insertar(SensorBase *valor);

    /**
     * Comprueba si la lista está vacía.
     * @return true si no contiene elementos.
     */
    bool estaVacia();

    /**
     * Llama a procesarLectura() para cada sensor almacenado.
     */
    void procesarTodos();

    /**
     * Imprime información de todos los sensores.
     */
    void imprimirTodos() const;

    /**
     * Busca un sensor por nombre.
     * @param nombre Nombre del sensor a buscar.
     * @return Puntero al sensor o nullptr si no existe.
     */
    SensorBase* buscarPorNombre(const char* nombre);
};
#endif
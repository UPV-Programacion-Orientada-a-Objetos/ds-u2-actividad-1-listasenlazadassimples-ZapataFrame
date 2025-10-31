#ifndef LISTASENSOR_H
#define LISTASENSOR_H

#include "Nodo.h"
#include <iostream>

template <typename T>
// interfaz
class ListaSensor
{
private:
    Nodo<T> *cabeza;

public:
    ListaSensor()
    {
        this->cabeza = nullptr;
    };
    ~ListaSensor()
    {
        // si es null no se libera nada
        if (this->cabeza == nullptr)
            return;
        Nodo<T> *temp = this->cabeza;
        while (temp != nullptr)
        {
            Nodo<T> *aux = temp->siguiente;
            delete temp;
            temp = aux;
        }
        this->cabeza = nullptr;
    }
    void insertar(T valor);
    T encontrarMinimo();
    void eliminarValor(T valor);
    double calcularPromedio();
    bool estaVacia();
    int numeroDeElementos();
    void mostrarLista();
};

// implementacion
template <typename T>
void ListaSensor<T>::insertar(T valor)
{
    Nodo<T> *nuevoNodo = new Nodo<T>(valor);
    if (this->cabeza == nullptr)
    {
        this->cabeza = nuevoNodo;
    }
    else
    {
        Nodo<T> *temp = this->cabeza;
        while (temp->siguiente != nullptr)
        {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoNodo;
    }
}

template <typename T>
T ListaSensor<T>::encontrarMinimo()
{

    // si la lista esta vacia
    if (this->cabeza == nullptr)
        return T(); // alomejor throwear una exception

    // si tiene un nodo asignar el valor al minimo
    Nodo<T> *temp = this->cabeza;
    T valorMinimo = temp->valor;

    while (temp->siguiente != nullptr)
    {
        temp = temp->siguiente;
        if (temp->valor < valorMinimo)
        {
            valorMinimo = temp->valor;
        }
    }
    return valorMinimo;
}

template <typename T>
void ListaSensor<T>::eliminarValor(T valor)
{
    // si la lista esta vacia
    if (this->cabeza == nullptr)
        return;
    Nodo<T> *temp = this->cabeza;

    // En caso de que sea el primer valor
    if (temp->valor == valor)
    {
        Nodo<T> *aux = temp;
        this->cabeza = aux->siguiente;
        delete aux;
        return;
    }

    // en caso de que sea algun otro elemento
    while (temp->siguiente != nullptr)
    {
        Nodo<T> *aux = temp->siguiente;
        if (aux->valor == valor)
        {
            temp->siguiente = aux->siguiente;
            delete aux;
            return;
        }
        temp = temp->siguiente;
    }
}

template <typename T>
double ListaSensor<T>::calcularPromedio()
{
    if (this->cabeza == nullptr)
        return 0.0; // alomejor throwear algo

    Nodo<T> *temp = this->cabeza;
    int contador = 0;
    double sumatoria = 0.0;

    while (temp != nullptr)
    {
        sumatoria += (temp->valor);
        contador++;
        temp = temp->siguiente;
    }

    return sumatoria / contador;
}

template <typename T>
bool ListaSensor<T>::estaVacia()
{
    return cabeza == nullptr;
}

template <typename T>
int ListaSensor<T>::numeroDeElementos()
{
    int contador = 0;
    Nodo<T> *temp = this->cabeza;
    while (temp != nullptr)
    {
        contador++;
        temp = temp->siguiente;
    }

    return contador;
}

template <typename T>
void ListaSensor<T>::mostrarLista()
{
    if (this->cabeza == nullptr)
        return;

    Nodo<T> *temp = this->cabeza;
    while (temp != nullptr)
    {
        std::cout << temp->valor << " ->";
        temp = temp->siguiente;
    }
    std::cout << std::endl;
}

#endif
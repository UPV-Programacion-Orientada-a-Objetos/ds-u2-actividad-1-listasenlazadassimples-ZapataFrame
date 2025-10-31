#include "ListaGeneral.h"
#include <iostream>
#include <cstring>
// implementacion

ListaGeneral::~ListaGeneral()
{
    // si es null no se libera nada
    if (this->cabeza == nullptr)
        return;
    Nodo<SensorBase *> *temp = this->cabeza;
    while (temp != nullptr)
    {
        Nodo<SensorBase *> *aux = temp->siguiente;
        delete temp->valor;
        delete temp;
        temp = aux;
    }
    this->cabeza = nullptr;
}

void ListaGeneral::insertar(SensorBase *valor)
{
    Nodo<SensorBase *> *nuevoNodo = new Nodo<SensorBase *>(valor);
    if (this->cabeza == nullptr)
    {
        this->cabeza = nuevoNodo;
    }
    else
    {
        Nodo<SensorBase *> *temp = this->cabeza;
        while (temp->siguiente != nullptr)
        {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoNodo;
    }
}
bool ListaGeneral::estaVacia()
{
    return cabeza == nullptr;
}

void ListaGeneral::procesarTodos()
{
    if (this->cabeza == nullptr)
    {
        std::cout << "No hay sensores para procesar." << std::endl;
        return;
    }

    std::cout << "\n--- Ejecutando Polimorfismo ---" << std::endl;

    Nodo<SensorBase *> *temp = this->cabeza;
    while (temp != nullptr)
    {
        std::cout << "-> Procesando sensor ";
        temp->valor->printNombre();
        std::cout << std::endl;

        temp->valor->procesarLectura();
        temp = temp->siguiente;
        std::cout << std::endl;
    }
}

void ListaGeneral::imprimirTodos() const
{
    if (this->cabeza == nullptr)
    {
        std::cout << "No hay sensores registrados." << std::endl;
        return;
    }

    std::cout << "\n--- Lista de Sensores ---" << std::endl;

    Nodo<SensorBase *> *temp = this->cabeza;
    int contador = 1;

    while (temp != nullptr)
    {
        std::cout << "\n[Sensor " << contador << "]" << std::endl;
        temp->valor->imprimirInfo();
        temp = temp->siguiente;
        contador++;
    }
}

SensorBase* ListaGeneral::buscarPorNombre(const char* nombre)
{
    Nodo<SensorBase *> *temp = this->cabeza;
    
    while (temp != nullptr)
    {
        if (std::strcmp(temp->valor->getNombre(), nombre) == 0)
        {
            return temp->valor;
        }
        temp = temp->siguiente;
    }
    
    return nullptr;
}
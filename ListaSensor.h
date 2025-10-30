#include "Nodo.h"

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
        this->cabeza=nullptr;
    }
    void insertar(T valor);
    T encontrarMinimo();
    void eliminarValor(T valor);
    T calcularPromedio();
    bool estaVacia();
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
T ListaSensor<T>::calcularPromedio()
{
    // si la lista esta vacia
    if (this->cabeza == nullptr)
        return T(); // alomejor throwear una exception

    Nodo<T> *temp = this->cabeza;
    int contador = 1;
    T sumatoria = temp->valor;

    while (temp->siguiente != nullptr)
    {
        Nodo<T> *aux = temp->siguiente;
        sumatoria += aux->valor;
        contador++;
        temp = temp->siguiente;
    }

    T promedio = sumatoria / contador;
    return promedio;
}

template <typename T>
bool ListaSensor<T>::estaVacia() {
    return cabeza == nullptr;
}
#include "SensorPresion.h"
#include <iostream>

// Constructor
SensorPresion::SensorPresion(const char *nom) : SensorBase(nom) {}

// Destructor
SensorPresion::~SensorPresion()
{
    std::cout << "\t[Destructor Sensor " << this->nombre << "] Liberando Lista Interna..." << std::endl;
}

void SensorPresion::procesarLectura()
{
    std::cout << "-> Procesando Sensor " << this->nombre << "..." << std::endl;
    if (!historial.estaVacia())
    {
        double promedio = historial.calcularPromedio();
        int numeroElementos = historial.numeroDeElementos();
        std::cout << "[Sensor Presion] Promedio calculado sobre " << numeroElementos << " lectura (" << promedio << ")." << std::endl;
        std::cout << "[" << nombre << "] (Presion): Promedio de lecturas: "
                  << promedio << "." << std::endl;
    }
    else
    {
        std::cout << "[" << nombre << "] (Presion): Sin lecturas" << std::endl;
    }
}

void SensorPresion::imprimirInfo() const
{
    std::cout << "=== Sensor de Presión ===" << std::endl;
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Tipo: Presión (int)" << std::endl;
}

void SensorPresion::agregarLectura(int valor)
{
    std::cout << "[Log] Insertando Nodo<int> en " << this->nombre << "." << std::endl;
    historial.insertar(valor);
}
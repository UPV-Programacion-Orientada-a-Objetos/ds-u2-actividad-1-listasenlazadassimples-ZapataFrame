#include "SensorPresion.h"
#include <iostream>

// Constructor
SensorPresion::SensorPresion(const char *nom) : SensorBase(nom){}

// Destructor
SensorPresion::~SensorPresion() {}

void SensorPresion::procesarLectura()
{
    if (!historial.estaVacia())
    {
        int promedio = historial.calcularPromedio();
        std::cout << "[" << nombre << "] Promedio de lecturas: "
                  << promedio << "." << std::endl;
    }
    else
    {
        std::cout << "[" << nombre << "] Sin lecturas" << std::endl;
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
    historial.insertar(valor);
    std::cout << "[Log] Lectura " << valor << " registrada en " << nombre << std::endl;
}
#include "SensorTemperatura.h"
#include <iostream>

// Constructor
SensorTemperatura::SensorTemperatura(const char *nom) : SensorBase(nom){}

// Destructor
SensorTemperatura::~SensorTemperatura() {}

void SensorTemperatura::procesarLectura()
{
    if (!historial.estaVacia())
    {
        float minimo = historial.encontrarMinimo();
        historial.eliminarValor(minimo);
        double promedio = historial.calcularPromedio();
        std::cout << "[" << nombre << "] (Temperatura): Lectura más baja ("
                  << minimo << ") eliminada."
                  << "Promedio restante: " << promedio << "." << std::endl;
    }
    else
    {
        std::cout << "[" << nombre << "] Sin lecturas" << std::endl;
    }
}

void SensorTemperatura::imprimirInfo() const
{
    std::cout << "=== Sensor de Temperatura ===" << std::endl;
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Tipo: Temperatura (float)" << std::endl;
}

void SensorTemperatura::agregarLectura(float valor)
{
    historial.insertar(valor);
}
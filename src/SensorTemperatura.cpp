/**
 * @file SensorTemperatura.cpp
 * @brief Implementación del sensor de temperatura.
 *
 * Especializa SensorBase para manejar lecturas de tipo float. Mantiene
 * un historial de lecturas y calcula promedios tras eliminar el valor mínimo
 * en el método procesarLectura().
 */

#include "SensorTemperatura.h"
#include <iostream>

// Constructor
SensorTemperatura::SensorTemperatura(const char *nom) : SensorBase(nom) {}

// Destructor
SensorTemperatura::~SensorTemperatura()
{
    std::cout << "\t[Destructor Sensor " << this->nombre << "] Liberando Lista Interna..." << std::endl;
}

void SensorTemperatura::procesarLectura()
{
    std::cout << "-> Procesando Sensor " << this->nombre << "..." << std::endl;
    if (!historial.estaVacia())
    {
        float minimo = historial.encontrarMinimo();
        historial.eliminarValor(minimo);
        double promedio = historial.calcularPromedio();
        int numeroElementos = historial.numeroDeElementos();
        std::cout << "[Sensor Temp] Promedio calculado sobre " << numeroElementos << " lectura (" << promedio << ")." << std::endl;
        std::cout << "[" << nombre << "] (Temperatura): Lectura más baja ("
                  << minimo << ") eliminada."
                  << "Promedio restante: " << promedio << "." << std::endl;
    }
    else
    {
        std::cout << "[" << nombre << "] (Temperatura): Sin lecturas" << std::endl;
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
    std::cout << "[Log] Insertando Nodo<float> en " << this->nombre << "." << std::endl;
    historial.insertar(valor);
}
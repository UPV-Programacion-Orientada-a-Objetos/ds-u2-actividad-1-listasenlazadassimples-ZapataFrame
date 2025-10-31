#ifndef SENSORPRESION_H
#define SENSORPRESION_H

/**
 * @file SensorPresion.h
 * @brief Implementación de sensor de presión.
 *
 * Extiende SensorBase, almacena un historial de lecturas en ListaSensor<int>
 * y proporciona funciones para procesar y mostrar lecturas.
 */

#include "SensorBase.h"
#include "ListaSensor.h"

class SensorPresion : public SensorBase
{
private:
    ListaSensor<int> historial; /**< Historial de lecturas. */

public:
    /** Constructor. @param nom Nombre del sensor. */
    SensorPresion(const char* nom);
    /** Destructor. */
    ~SensorPresion();

    void procesarLectura() override;
    void imprimirInfo() const override;
    void agregarLectura(int valor);
};

#endif
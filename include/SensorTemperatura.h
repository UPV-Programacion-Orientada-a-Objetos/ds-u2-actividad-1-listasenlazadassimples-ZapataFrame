#ifndef SENSORTEMPERATURA_H
#define SENSORTEMPERATURA_H

/**
 * @file SensorTemperatura.h
 * @brief Implementación de sensor de temperatura.
 *
 * Extiende SensorBase y mantiene un historial de lecturas en una
 * ListaSensor<float>. Provee métodos para procesar lecturas y mostrar
 * información del sensor.
 */

#include "SensorBase.h"
#include "ListaSensor.h"

class SensorTemperatura : public SensorBase
{
private:
    ListaSensor<float> historial; /**< Historial de lecturas. */

public:
    /** Constructor. @param nom Nombre del sensor. */
    SensorTemperatura(const char* nom);
    /** Destructor. */
    ~SensorTemperatura();

    void procesarLectura() override;
    void imprimirInfo() const override;
    void agregarLectura(float valor);
};

#endif
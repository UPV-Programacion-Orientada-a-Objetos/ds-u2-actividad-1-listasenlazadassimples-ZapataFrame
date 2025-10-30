#ifndef SENSORTEMPERATURA_H
#define SENSORTEMPERATURA_H

#include "SensorBase.h"
#include "ListaSensor.h"

class SensorTemperatura : public SensorBase
{
private:
    ListaSensor<float> historial;

public:
    // Constructor
    SensorTemperatura(const char* nom);
    
    // Destructor
    ~SensorTemperatura();
    
    void procesarLectura() override;
    void imprimirInfo() const override;
    void agregarLectura(float valor);
};

#endif
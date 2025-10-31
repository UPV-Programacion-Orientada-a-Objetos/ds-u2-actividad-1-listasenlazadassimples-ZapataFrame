#ifndef SENSORPRESION_H
#define SENSORPRESION_H

#include "SensorBase.h"
#include "ListaSensor.h"

class SensorPresion : public SensorBase
{
private:
    ListaSensor<int> historial;

public:
    // Constructor
    SensorPresion(const char* nom);
    
    // Destructor
    ~SensorPresion();

    void procesarLectura() override;
    void imprimirInfo() const override;
    void agregarLectura(int valor);
};

#endif
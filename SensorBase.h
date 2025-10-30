#ifndef SENSORBASE_H
#define SENSORBASE_H

#include <cstring>

class SensorBase
{
public:
    // Constructor
    SensorBase(const char* nom);
    
    // Destructor
    virtual ~SensorBase();
    
    virtual void procesarLectura() = 0;
    virtual void imprimirInfo() const = 0;

protected:
    char nombre[50];
};

#endif
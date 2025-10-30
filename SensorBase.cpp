#include "SensorBase.h"

// Constructor
SensorBase::SensorBase(const char *nom)
{
    std::strncpy(nombre, nom, 49);
    nombre[49] = '\0';
}

// Destructor
SensorBase::~SensorBase(){}
#include "SensorBase.h"
#include <iostream>

// Constructor
SensorBase::SensorBase(const char *nom)
{
    std::strncpy(nombre, nom, 49);
    nombre[49] = '\0';
}

// Destructor
SensorBase::~SensorBase(){}

void SensorBase::printNombre(){
    std::cout << this->nombre;
}

const char* SensorBase::getNombre() const {
    return nombre;
}
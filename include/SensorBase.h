#ifndef SENSORBASE_H
#define SENSORBASE_H

/**
 * @file SensorBase.h
 * @brief Clase base abstracta para todos los sensores del sistema IoT.
 *
 * Define la interfaz común que deben implementar todos los sensores concretos
 * (temperatura, presión, etc.). Declara los métodos virtuales puros
 * procesarLectura() e imprimirInfo() que garantizan el comportamiento
 * polimórfico del sistema.
 *
 * @author ZapataFrame
 * @date 2025-10-30
 */

#include <cstring>

class SensorBase
{
public:
    /**
     * Constructor de la clase base.
     * @param nom Nombre identificador del sensor.
     */
    SensorBase(const char* nom);
    
    /**
     * Destructor virtual para garantizar destrucción polimórfica.
     */
    virtual ~SensorBase();
    
    /**
     * Procesa las lecturas almacenadas en el sensor (método virtual puro).
     * Cada sensor concreto define su lógica de procesamiento.
     */
    virtual void procesarLectura() = 0;
    
    /**
     * Imprime información descriptiva del sensor (método virtual puro).
     */
    virtual void imprimirInfo() const = 0;
    
    /**
     * Imprime el nombre del sensor en salida estándar.
     */
    void printNombre();
    
    /**
     * Obtiene el nombre del sensor.
     * @return Puntero al nombre del sensor.
     */
    const char* getNombre() const;

protected:
    char nombre[50]; /**< Nombre del sensor (máximo 49 caracteres). */
};

#endif
#ifndef ARDUINOREADER_H
#define ARDUINOREADER_H

/**
 * @brief Clase para lectura de puerto serial (Arduino) sin usar STL
 * @details Implementa comunicación serial usando POSIX (termios.h)
 */
class ArduinoReader {
private:
    int serial_port;        ///< Descriptor del puerto serial
    bool isConnected;       ///< Estado de conexión
    char puerto[50];        ///< Nombre del puerto (ej. /dev/ttyUSB0)
    
    /**
     * @brief Configura los parámetros del puerto serial
     * @return true si la configuración fue exitosa
     */
    bool configurarPuerto();
    
    /**
     * @brief Espera y limpia el buffer tras reset del Arduino
     */
    void esperarArduinoListo();
    
public:
    /**
     * @brief Constructor que intenta abrir y configurar el puerto
     * @param port Ruta del puerto serial (ej. "/dev/ttyUSB0")
     */
    ArduinoReader(const char* port);
    
    /**
     * @brief Destructor que cierra el puerto automáticamente
     */
    ~ArduinoReader();
    
    /**
     * @brief Verifica si la conexión está activa
     * @return true si el puerto está abierto y configurado
     */
    bool estaConectado() const;
    
    /**
     * @brief Lee una línea completa del puerto serial
     * @param buffer Buffer donde se almacenará la línea leída
     * @param maxLen Tamaño máximo del buffer
     * @return true si se leyó una línea completa exitosamente
     */
    bool leerLinea(char* buffer, int maxLen);
    
    /**
     * @brief Cierra el puerto serial manualmente
     */
    void desconectar();
    
    /**
     * @brief Obtiene el nombre del puerto
     * @return Puntero al nombre del puerto
     */
    const char* getPuerto() const;
};

#endif
/**
 * @file ArduinoReader.cpp
 * @brief Implementación de la clase de comunicación serial con Arduino.
 *
 * Usa POSIX termios para configurar y leer del puerto serial. Implementa
 * apertura, configuración a 9600 baud, lectura línea por línea y cierre
 * del puerto. Gestiona timeouts y sincronización con Arduino tras reset.
 */

#include "ArduinoReader.h"
#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <errno.h>

ArduinoReader::ArduinoReader(const char *port)
    : serial_port(-1), isConnected(false)
{
    strncpy(this->puerto, port, sizeof(this->puerto) - 1);
    this->puerto[sizeof(this->puerto) - 1] = '\0';
    
    this->serial_port = open(port, O_RDWR | O_NOCTTY);
    
    if (this->serial_port < 0)
    {
        std::cerr << "[Error Arduino] No se pudo abrir puerto " << port << std::endl;
        std::cerr << "[Error Arduino] Verifica: permisos (sudo chmod 666 " << port << ")" << std::endl;
        return;
    }
    
    if (!this->configurarPuerto())
    {
        std::cerr << "[Error Arduino] Fallo en configuracion del puerto" << std::endl;
        close(this->serial_port);
        this->serial_port = -1;
        return;
    }
    
    this->esperarArduinoListo();
    this->isConnected = true;
}

ArduinoReader::~ArduinoReader()
{
    this->desconectar();
}

bool ArduinoReader::configurarPuerto()
{
    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    
    if (tcgetattr(this->serial_port, &tty) != 0)
    {
        std::cerr << "[Error Arduino] tcgetattr fallo" << std::endl;
        return false;
    }
    
    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);
    
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;
    
    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO;
    tty.c_lflag &= ~ECHOE;
    tty.c_lflag &= ~ECHONL;
    tty.c_lflag &= ~ISIG;
    
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);
    
    tty.c_oflag &= ~OPOST;
    tty.c_oflag &= ~ONLCR;
    
    tty.c_cc[VTIME] = 10;
    tty.c_cc[VMIN] = 0;
    
    if (tcsetattr(this->serial_port, TCSANOW, &tty) != 0)
    {
        std::cerr << "[Error Arduino] tcsetattr fallo" << std::endl;
        return false;
    }
    
    return true;
}

void ArduinoReader::esperarArduinoListo()
{
    usleep(2000000);
    tcflush(this->serial_port, TCIOFLUSH);
}

bool ArduinoReader::leerLinea(char *buffer, int maxLen)
{
    if (!this->isConnected || this->serial_port < 0)
    {
        return false;
    }
    
    int index = 0;
    char c;
    
    while (index < maxLen - 1)
    {
        int n = read(this->serial_port, &c, 1);
        
        if (n < 0)
        {
            return false;
        }
        
        if (n == 0)
        {
            continue;
        }
        
        if (c == '\n')
        {
            buffer[index] = '\0';
            return true;
        }
        
        if (c == '\r')
        {
            continue;
        }
        
        buffer[index++] = c;
    }
    
    buffer[index] = '\0';
    return false;
}

void ArduinoReader::desconectar()
{
    if (this->serial_port >= 0)
    {
        close(this->serial_port);
        this->serial_port = -1;
    }
    this->isConnected = false;
}

bool ArduinoReader::estaConectado() const
{
    return this->isConnected;
}

const char *ArduinoReader::getPuerto() const
{
    return this->puerto;
}
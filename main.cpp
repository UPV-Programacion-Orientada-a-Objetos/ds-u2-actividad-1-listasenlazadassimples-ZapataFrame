#include <iostream>
#include <limits>
#include <cstring>
#include <cstdlib>
#include "ListaGeneral.h"
#include "SensorTemperatura.h"
#include "SensorPresion.h"
#include "ArduinoReader.h"

template <typename T>
T getInput(const char* prompt);

template <>
const char* getInput(const char* prompt);

int get_menu_option();
void print_menu();
void crearSensorTemperatura(ListaGeneral* lista);
void crearSensorPresion(ListaGeneral* lista);
void registrarLectura(ListaGeneral* lista);
void registrarLecturaManual(ListaGeneral* lista);

int main()
{
    std::cout << "\n========================================" << std::endl;
    std::cout << "   Sistema IoT de Monitoreo Polimorfico" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    ListaGeneral* listaSensores = new ListaGeneral();
    
    bool isProgramRunning = true;
    
    while (isProgramRunning)
    {
        int opt = get_menu_option();
        switch (opt)
        {
            case 1:
            {
                std::cout << "\nOpcion 1: Crear Sensor (Tipo Temp - FLOAT)" << std::endl;
                crearSensorTemperatura(listaSensores);
                break;
            }
            case 2:
            {
                std::cout << "\nOpcion 2: Crear Sensor (Tipo Presion - INT)" << std::endl;
                crearSensorPresion(listaSensores);
                break;
            }
            case 3:
            {
                std::cout << "\nOpcion 3: Registrar Lectura" << std::endl;
                registrarLectura(listaSensores);
                break;
            }
            case 4:
            {
                std::cout << "\nOpcion 4: Ejecutar Procesamiento Polimorfico" << std::endl;
                std::cout << "\n--- Ejecutando Polimorfismo ---" << std::endl;
                listaSensores->procesarTodos();
                break;
            }
            case 5:
            {
                std::cout << "\nOpcion 5: Cerrar Sistema (Liberar Memoria)" << std::endl;
                std::cout << "\n--- Liberacion de Memoria en Cascada ---" << std::endl;
                isProgramRunning = false;
                break;
            }
            case 6:
            {
                std::cout << "\nOpcion 6: Registro Manual de Lectura" << std::endl;
                registrarLecturaManual(listaSensores);
                break;
            }
        }
    }
    
    delete listaSensores;
    std::cout << "Sistema cerrado. Memoria limpia." << std::endl;
    
    return 0;
}

void crearSensorTemperatura(ListaGeneral* lista)
{
    const char* nombre = getInput<const char*>("Nombre del sensor: ");
    SensorBase* nuevoSensor = new SensorTemperatura(nombre);
    lista->insertar(nuevoSensor);
    std::cout << "Sensor '" << nombre << "' creado e insertado en la lista de gestion." << std::endl;
}

void crearSensorPresion(ListaGeneral* lista)
{
    const char* nombre = getInput<const char*>("Nombre del sensor: ");
    SensorBase* nuevoSensor = new SensorPresion(nombre);
    lista->insertar(nuevoSensor);
    std::cout << "Sensor '" << nombre << "' creado e insertado en la lista de gestion." << std::endl;
}

void registrarLectura(ListaGeneral* lista)
{
    if (lista->estaVacia())
    {
        std::cout << "[Error] No hay sensores en el sistema." << std::endl;
        std::cout << "[Info] Agregue el Sensor de temperatura 'T-001' y el de Presion 'P-105'." << std::endl;
        return;
    }
    
    const char* puerto = "/dev/ttyUSB0";
    
    ArduinoReader* arduino = new ArduinoReader(puerto);
    
    if (!arduino->estaConectado())
    {
        std::cout << "[Error] No se pudo conectar al Arduino." << std::endl;
        delete arduino;
        return;
    }
    
    char buffer[100];
    int lecturas = 0;
    
    // 2 CADA UNA
    while (lecturas < 4)
    {
        if (arduino->leerLinea(buffer, sizeof(buffer)))
        {
            if (strcmp(buffer, "ARDUINO_READY") == 0)
            {
                continue;
            }
            
            char* coma = strchr(buffer, ',');
            if (coma == nullptr)
            {
                continue;
            }
            
            *coma = '\0';
            const char* id = buffer;
            const char* valorStr = coma + 1;
            
            SensorBase* sensor = lista->buscarPorNombre(id);
            
            if (sensor == nullptr)
            {
                continue;
            }
            
            SensorTemperatura* sensorTemp = dynamic_cast<SensorTemperatura*>(sensor);
            if (sensorTemp != nullptr)
            {
                float valor = atof(valorStr);
                sensorTemp->agregarLectura(valor);
                std::cout << "ID: " << id << ". Valor: " << valor << " (float)" << std::endl;
                lecturas++;
                continue;
            }
            
            SensorPresion* sensorPres = dynamic_cast<SensorPresion*>(sensor);
            if (sensorPres != nullptr)
            {
                int valor = atoi(valorStr);
                sensorPres->agregarLectura(valor);
                std::cout << "ID: " << id << ". Valor: " << valor << " (int)" << std::endl;
                lecturas++;
            }
        }
    }
    
    delete arduino;
}

void registrarLecturaManual(ListaGeneral* lista)
{
    if (lista->estaVacia())
    {
        std::cout << "[Error] No hay sensores en el sistema." << std::endl;
        return;
    }
    
    const char* nombre = getInput<const char*>("ID: ");
    SensorBase* sensor = lista->buscarPorNombre(nombre);
    
    if (sensor == nullptr)
    {
        std::cout << "[Error] Sensor no encontrado." << std::endl;
        return;
    }
    
    SensorTemperatura* sensorTemp = dynamic_cast<SensorTemperatura*>(sensor);
    if (sensorTemp != nullptr)
    {
        float valor = getInput<float>("Valor: ");
        sensorTemp->agregarLectura(valor);
        std::cout << "ID: " << nombre << ". Valor: " << valor << " (float)" << std::endl;
        return;
    }
    
    SensorPresion* sensorPres = dynamic_cast<SensorPresion*>(sensor);
    if (sensorPres != nullptr)
    {
        int valor = getInput<int>("Valor: ");
        sensorPres->agregarLectura(valor);
        std::cout << "ID: " << nombre << ". Valor: " << valor << " (int)" << std::endl;
        return;
    }
}

int get_menu_option()
{
    bool isValidOption = false;
    int opt;
    do
    {
        print_menu();
        opt = getInput<int>("Seleccione una opcion: ");
        if (opt < 1 || opt > 6)
        {
            std::cout << "[Error] Opcion invalida. Intente nuevamente." << std::endl;
            continue;
        }
        isValidOption = true;
    } while (!isValidOption);
    return opt;
}

void print_menu()
{
    std::cout << "\n========================================" << std::endl;
    std::cout << "            MENU PRINCIPAL              " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << " [1] Crear Sensor (Temperatura - FLOAT)" << std::endl;
    std::cout << " [2] Crear Sensor (Presion - INT)" << std::endl;
    std::cout << " [3] Registrar Lectura (Arduino)" << std::endl;
    std::cout << " [4] Ejecutar Procesamiento Polimorfico" << std::endl;
    std::cout << " [5] Cerrar Sistema" << std::endl;
    std::cout << " [6] Registro Manual de Lectura" << std::endl;
    std::cout << "========================================" << std::endl;
}

template <typename T>
T getInput(const char* prompt)
{
    T input;
    std::cout << prompt;
    while (!(std::cin >> input))
    {
        std::cout << "Entrada invalida." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << prompt;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return input;
}

template <>
const char* getInput(const char* prompt)
{
    static char buffer[50];
    std::cout << prompt;
    std::cin.getline(buffer, 50);
    return buffer;
}
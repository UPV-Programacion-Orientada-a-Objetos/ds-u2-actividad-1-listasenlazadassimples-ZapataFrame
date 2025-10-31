#include <iostream>
#include <limits>
#include <cstring>
#include "ListaGeneral.h"
#include "SensorTemperatura.h"
#include "SensorPresion.h"

// Prototipos de funciones
template <typename T>
T getInput(const char* prompt);

template <>
const char* getInput(const char* prompt);

int get_menu_option();
void print_menu();
void crearSensorTemperatura(ListaGeneral* lista);
void crearSensorPresion(ListaGeneral* lista);
void registrarLectura(ListaGeneral* lista);
SensorBase* buscarSensor(ListaGeneral* lista, const char* nombre);

int main()
{
    std::cout << "\n--- Sistema IoT de Monitoreo Polimorfico ---\n" << std::endl;
    
    ListaGeneral* listaSensores = new ListaGeneral();
    
    bool isProgramRunning = true;
    
    while (isProgramRunning)
    {
        int opt = get_menu_option();
        switch (opt)
        {
            case 0:
            {
                std::cout << "\nOpcion 5: Cerrar Sistema (Liberar Memoria)" << std::endl;
                std::cout << "\n--- Liberacion de Memoria en Cascada ---" << std::endl;
                isProgramRunning = false;
                break;
            }
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
                listaSensores->procesarTodos();
                break;
            }
            case 5:
            {
                std::cout << "\nMostrar Informacion de Sensores" << std::endl;
                listaSensores->imprimirTodos();
                break;
            }
        }
    }
    
    // Liberar memoria
    delete listaSensores;
    std::cout << "Sistema cerrado. Memoria limpia." << std::endl;
    
    return 0;
}

void crearSensorTemperatura(ListaGeneral* lista)
{
    const char* nombre = getInput<const char*>("ID del sensor (ej. T-001): ");
    SensorBase* nuevoSensor = new SensorTemperatura(nombre);
    lista->insertar(nuevoSensor);
    std::cout << "Sensor '" << nombre << "' creado e insertado en la lista de gestion." << std::endl;
}

void crearSensorPresion(ListaGeneral* lista)
{
    const char* nombre = getInput<const char*>("ID del sensor (ej. P-105): ");
    SensorBase* nuevoSensor = new SensorPresion(nombre);
    lista->insertar(nuevoSensor);
    std::cout << "Sensor '" << nombre << "' creado e insertado en la lista de gestion." << std::endl;
}

void registrarLectura(ListaGeneral* lista)
{
    if (lista->estaVacia())
    {
        std::cout << "[Error] No hay sensores registrados. Cree un sensor primero." << std::endl;
        return;
    }
    
    const char* nombre = getInput<const char*>("ID del sensor: ");
    
    SensorBase* sensor = lista->buscarPorNombre(nombre);
    
    if (sensor == nullptr)
    {
        std::cout << "[Error] Sensor '" << nombre << "' no encontrado." << std::endl;
        return;
    }
    
    // Intentar hacer downcast a SensorTemperatura
    SensorTemperatura* sensorTemp = dynamic_cast<SensorTemperatura*>(sensor);
    if (sensorTemp != nullptr)
    {
        // Es un sensor de temperatura
        float valor = getInput<float>("Valor (float): ");
        sensorTemp->agregarLectura(valor);
        return;
    }
    
    // Intentar hacer downcast a SensorPresion
    SensorPresion* sensorPres = dynamic_cast<SensorPresion*>(sensor);
    if (sensorPres != nullptr)
    {
        // Es un sensor de presion
        int valor = getInput<int>("Valor (int): ");
        sensorPres->agregarLectura(valor);
        return;
    }
    
    std::cout << "[Error] Tipo de sensor desconocido." << std::endl;
}

int get_menu_option()
{
    bool isValidOption = false;
    int opt;
    do
    {
        print_menu();
        opt = getInput<int>("Ingrese una opcion [0-5]: ");
        if (opt < 0 || opt > 5)
        {
            std::cout << "[Error] Ingrese una opcion valida" << std::endl;
            continue;
        }
        isValidOption = true;
    } while (!isValidOption);
    return opt;
}

void print_menu()
{
    std::cout << "\n========================================" << std::endl;
    std::cout << "         MENU PRINCIPAL                 " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << " 1. Crear Sensor (Tipo Temp - FLOAT)" << std::endl;
    std::cout << " 2. Crear Sensor (Tipo Presion - INT)" << std::endl;
    std::cout << " 3. Registrar Lectura" << std::endl;
    std::cout << " 4. Procesar Todos (Polimorfismo)" << std::endl;
    std::cout << " 5. Mostrar Sensores" << std::endl;
    std::cout << " 0. Salir" << std::endl;
    std::cout << "========================================" << std::endl;
}

template <typename T>
T getInput(const char* prompt)
{
    T input;
    std::cout << prompt;
    while (!(std::cin >> input))
    {
        std::cout << "Ingrese un input valido!" << std::endl;
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
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(ListasEnlazadasSimples VERSION 1.0 LANGUAGES CXX)

# Establecer el estándar de C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Opciones de compilación
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Archivos fuente
set(SOURCES
    main.cpp
    SensorBase.cpp
    SensorTemperatura.cpp
    SensorPresion.cpp
    ListaGeneral.cpp
    ArduinoReader.cpp
)

# Archivos de encabezado
set(HEADERS
    Nodo.h
    ListaSensor.h
    ListaGeneral.h
    SensorBase.h
    SensorTemperatura.h
    SensorPresion.h
    ArduinoReader.h
)

# Crear el ejecutable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Habilitar RTTI para dynamic_cast
target_compile_options(${PROJECT_NAME} PRIVATE -frtti)

# Información de compilación
message(STATUS "Proyecto: ${PROJECT_NAME}")
message(STATUS "Versión: ${PROJECT_VERSION}")
message(STATUS "Compilador C++: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Estándar C++: C++${CMAKE_CXX_STANDARD}")

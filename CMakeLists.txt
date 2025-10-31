cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(ListasEnlazadasSimples VERSION 1.0 LANGUAGES CXX)

# Establecer el estándar de C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Opciones de compilación
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Directorio de encabezados
include_directories(${CMAKE_SOURCE_DIR}/include)

# Archivos fuente
set(SOURCES
    src/main.cpp
    src/SensorBase.cpp
    src/SensorTemperatura.cpp
    src/SensorPresion.cpp
    src/ListaGeneral.cpp
    src/ArduinoReader.cpp
)

# Archivos de encabezado
set(HEADERS
    include/Nodo.h
    include/ListaSensor.h
    include/ListaGeneral.h
    include/SensorBase.h
    include/SensorTemperatura.h
    include/SensorPresion.h
    include/ArduinoReader.h
)

# Configurar la carpeta de salida para los ejecutables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

# Crear el ejecutable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Habilitar RTTI para dynamic_cast
target_compile_options(${PROJECT_NAME} PRIVATE -frtti)

# Información de compilación
message(STATUS "Proyecto: ${PROJECT_NAME}")
message(STATUS "Versión: ${PROJECT_VERSION}")
message(STATUS "Compilador C++: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Estándar C++: C++${CMAKE_CXX_STANDARD}")

cmake_minimum_required(VERSION 3.10)
project(SistemaIoT)

set(CMAKE_CXX_STANDARD 11)

# Archivos fuente principales
add_executable(SistemaIoT 
    main.cpp
    # Solo main.cpp porque los demás son .h con implementación inline
)

# En Windows, enlazar con librerías necesarias para puerto serial
if(WIN32)
    target_link_libraries(SistemaIoT Setupapi)
endif()

# Configuración para mostrar advertencias
if(MSVC)
    target_compile_options(SistemaIoT PRIVATE /W4)
else()
    target_compile_options(SistemaIoT PRIVATE -Wall -Wextra)
endif()
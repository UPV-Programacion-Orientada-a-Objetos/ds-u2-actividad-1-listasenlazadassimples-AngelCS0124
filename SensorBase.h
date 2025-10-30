#ifndef SENSORBASE_H
#define SENSORBASE_H

#include <iostream>

class SensorBase {
    protected:
        char nombre[50];

    public:
        // Constructor
        SensorBase(const char* nombreSensor) {
            int i = 0;
            // Se copia el nombre del sensor asegurando no exceder el tamaño del arreglo
            while (nombreSensor[i] != '\0' && i < 49) {
                // Se copian los caracteres uno por uno
                nombre[i] = nombreSensor[i];
                i++;
            } 
            nombre[i] = '\0';
        }
        // Destructor virtual
        virtual ~SensorBase() {
            // Log de destrucción del sensor base
            std::cout << "Sensor '" << obtenerNombre() << "' destruido" << std::endl;
        }
        // Métodos virtuales puros
        virtual void procesarLectura() = 0;
        virtual void mostrarInfo() const = 0;

        const char* obtenerNombre() const { return nombre; }
};

#endif 
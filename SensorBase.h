#ifndef SENSORBASE_H
#define SENSORBASE_H

#include <iostream>

/**
 * @file SensorBase.h
 * @brief Clase base abstracta para todos los tipos de sensores
 * @author Angel Gabriel Coronado Sánchez
 * @date 2025
 */

/**
 * @class SensorBase
 * @brief Clase abstracta que define la interfaz común para todos los sensores
 * 
 * Esta clase proporciona la base para implementar diferentes tipos de sensores
 * mediante polimorfismo. Define métodos virtuales puros que deben ser
 * implementados por las clases derivadas.
 */
class SensorBase {
    protected:
        char nombre[50]; ///< Nombre identificador del sensor (máximo 49 caracteres)
        
    public:
        /**
         * @brief Constructor de la clase base
         * @param nombreSensor Cadena de caracteres con el nombre del sensor
         * 
         * Copia el nombre del sensor carácter por carácter, asegurando
         * no exceder el tamaño del arreglo (49 caracteres + terminador nulo)
         */
        SensorBase(const char* nombreSensor) {
            int i = 0;
            while (nombreSensor[i] != '\0' && i < 49) {
                nombre[i] = nombreSensor[i];
                i++;
            } 
            nombre[i] = '\0';
        }
        
        /**
         * @brief Destructor virtual de la clase base
         * 
         * Destructor marcado como virtual para permitir la destrucción
         * polimórfica correcta de objetos derivados
         */
        virtual ~SensorBase() {
            std::cout << "Sensor '" << obtenerNombre() << "' destruido" << std::endl;
        }
        
        /**
         * @brief Procesa las lecturas almacenadas del sensor
         * @pure Método virtual puro - debe ser implementado por clases derivadas
         */
        virtual void procesarLectura() = 0;
        
        /**
         * @brief Muestra la información del sensor
         * @pure Método virtual puro - debe ser implementado por clases derivadas
         */
        virtual void mostrarInfo() const = 0;

        /**
         * @brief Obtiene el nombre del sensor
         * @return Puntero constante al nombre del sensor
         */
        const char* obtenerNombre() const { return nombre; }
};

#endif
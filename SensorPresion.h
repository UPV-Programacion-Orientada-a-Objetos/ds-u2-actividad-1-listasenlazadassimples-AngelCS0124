#ifndef SENSORPRESION_H
#define SENSORPRESION_H

#include <iostream>
#include "SensorBase.h"
#include "ListaSensor.h"

/**
 * @file SensorPresion.h
 * @brief Implementación de sensor de presión
 * @author Angel Gabriel Coronado Sánchez
 * @date 2025
 */

/**
 * @class SensorPresion
 * @brief Sensor especializado para medir y procesar lecturas de presión
 * 
 * Esta clase hereda de SensorBase e implementa funcionalidad específica
 * para sensores de presión. Almacena lecturas en formato int y su
 * procesamiento calcula el promedio de todas las lecturas.
 */
class SensorPresion : public SensorBase {
    private:
        ListaSensor<int> historial; ///< Lista enlazada con el historial de lecturas
        
    public:
        /**
         * @brief Constructor del sensor de presión
         * @param nombreSensor Nombre identificador del sensor
         * @post Crea un sensor de presión e imprime mensaje de log
         */
        SensorPresion(const char* nombreSensor) : SensorBase(nombreSensor) {
            std::cout << "Sensor de presión '" << obtenerNombre() << "' creado" << std::endl;
        }

        /**
         * @brief Destructor del sensor de presión
         * @post Destruye el sensor e imprime mensaje de log
         */
        ~SensorPresion() {
            std::cout << "Sensor de presión '" << obtenerNombre() << "' destruido" << std::endl;
        }
        
        /**
         * @brief Registra una nueva lectura de presión
         * @param valor Valor de presión a registrar
         * @post Agrega la lectura al historial e imprime confirmación
         */
        void registrarLectura(int valor) {
            historial.insertar(valor);
            std::cout << "Lectura registrada en sensor '" << obtenerNombre() << "': " << valor << std::endl;
        }

        /**
         * @brief Procesa las lecturas del sensor de presión
         * @post Calcula e imprime el promedio de todas las lecturas
         * 
         * Implementación específica del procesamiento para presión:
         * suma todas las lecturas y calcula el promedio
         */
        void procesarLectura() override {
            std::cout << "\n[Procesando Sensor " << obtenerNombre() << " - Presión]" << std::endl;
            
            if (historial.obtenerTamanio() == 0) {
                std::cout << "No hay lecturas para procesar." << std::endl;
                return;
            }

            int suma = 0;
            Nodo<int>* actual = historial.obtenerCabeza();
            
            while (actual != nullptr) {
                suma += actual->dato;
                actual = actual->sig;
            }
            
            float promedio = static_cast<float>(suma) / historial.obtenerTamanio();
            std::cout << "Promedio de lecturas: " << promedio << std::endl;
        }

        /**
         * @brief Muestra información detallada del sensor
         * @post Imprime tipo, nombre y cantidad de lecturas registradas
         */
        void mostrarInfo() const override {
            std::cout << "\n=== INFORMACION DEL SENSOR ===" << std::endl;
            std::cout << "Tipo: Presión" << std::endl;
            std::cout << "Nombre: " << obtenerNombre() << std::endl;
            std::cout << "Cantidad de lecturas: " << historial.obtenerTamanio() << std::endl;
            std::cout << "===============================" << std::endl;
        }
};

#endif
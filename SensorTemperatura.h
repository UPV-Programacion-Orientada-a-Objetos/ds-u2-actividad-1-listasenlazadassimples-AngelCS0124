#ifndef SENSORTEMPERATURA_H
#define SENSORTEMPERATURA_H

#include <iostream>
#include "SensorBase.h"
#include "ListaSensor.h"

/**
 * @file SensorTemperatura.h
 * @brief Implementación de sensor de temperatura
 * @author Angel Gabriel Coronado Sánchez
 * @date 2025
 */

/**
 * @class SensorTemperatura
 * @brief Sensor especializado para medir y procesar lecturas de temperatura
 * 
 * Esta clase hereda de SensorBase e implementa funcionalidad específica
 * para sensores de temperatura. Almacena lecturas en formato float y
 * su procesamiento consiste en encontrar y eliminar la lectura más baja.
 */
class SensorTemperatura : public SensorBase {
    private:
        ListaSensor<float> historial; ///< Lista enlazada con el historial de lecturas
        
    public:
        /**
         * @brief Constructor del sensor de temperatura
         * @param nombreSensor Nombre identificador del sensor
         * @post Crea un sensor de temperatura e imprime mensaje de log
         */
        SensorTemperatura(const char* nombreSensor) : SensorBase(nombreSensor) {
            std::cout << "Sensor de temperatura '" << obtenerNombre() << "' creado" << std::endl;
        }
        
        /**
         * @brief Destructor del sensor de temperatura
         * @post Destruye el sensor e imprime mensaje de log
         */
        ~SensorTemperatura() {
            std::cout << "Sensor de temperatura '" << obtenerNombre() << "' destruido" << std::endl;
        }
        
        /**
         * @brief Registra una nueva lectura de temperatura
         * @param valor Valor de temperatura a registrar
         * @post Agrega la lectura al historial e imprime confirmación
         */
        void registrarLectura(float valor) {
            historial.insertar(valor);
            std::cout << "Lectura registrada en sensor '" << obtenerNombre() << "': " << valor << std::endl;
        }

        /**
         * @brief Procesa las lecturas del sensor de temperatura
         * @post Encuentra y elimina la lectura más baja del historial
         * 
         * Implementación específica del procesamiento para temperatura:
         * recorre el historial buscando el valor mínimo y lo elimina
         */
        void procesarLectura() override {
            std::cout << "\n[Procesando Sensor " << obtenerNombre() << " - Temperatura]" << std::endl;
            
            if (historial.obtenerTamanio() == 0) {
                std::cout << "No hay lecturas para procesar." << std::endl;
                return;
            }
            
            float lecturaMasBaja = 9999.9f;
            Nodo<float>* actual = historial.obtenerCabeza(); 
            
            while (actual != nullptr) {
                if (actual->dato < lecturaMasBaja) {
                    lecturaMasBaja = actual->dato;
                }
                actual = actual->sig;
            }
            
            std::cout << "Lectura más baja encontrada: " << lecturaMasBaja << std::endl;
            std::cout << "Eliminando lectura más baja..." << std::endl;
            historial.eliminarValor(lecturaMasBaja);
        }

        /**
         * @brief Muestra información detallada del sensor
         * @post Imprime tipo, nombre y cantidad de lecturas registradas
         */
        void mostrarInfo() const override {
            std::cout << "\n=== INFORMACION DEL SENSOR ===" << std::endl;
            std::cout << "Tipo: Temperatura" << std::endl;
            std::cout << "Nombre: " << obtenerNombre() << std::endl;
            std::cout << "Cantidad de lecturas: " << historial.obtenerTamanio() << std::endl;
            std::cout << "===============================" << std::endl;
        }
};

#endif
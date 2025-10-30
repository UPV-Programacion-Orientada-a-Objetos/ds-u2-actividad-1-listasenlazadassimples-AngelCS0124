#ifndef SENSORPRESION_H
#define SENSORPRESION_H

#include <iostream>
#include "SensorBase.h"
#include "ListaSensor.h"

class SensorPresion : public SensorBase {
    private:
        ListaSensor<int> historial;
    public:
        SensorPresion(const char* nombreSensor) : SensorBase(nombreSensor) {
            // Log de creación del sensor
            std::cout << "Sensor de presión '" << obtenerNombre() << "' creado" << std::endl;
        }

        ~SensorPresion() {
            // Log de destrucción del sensor
            std::cout << "Sensor de presión '" << obtenerNombre() << "' destruido" << std::endl;
        }
        // Se agrega una nueva lectura al historial
        void registrarLectura(int valor) {
            historial.insertar(valor);
            std::cout << "Lectura registrada en sensor '" << obtenerNombre() << "': " << valor << std::endl;
        }

        void procesarLectura() override {
            std::cout << "\n[Procesando Sensor " << obtenerNombre() << " - Presión]" << std::endl;
            // Si no hay lecturas, no se puede procesar nada
            if (historial.obtenerTamanio() == 0) {
                std::cout << "No hay lecturas para procesar." << std::endl;
                return;
            }

            int suma = 0;
            Nodo<int>* actual = historial.obtenerCabeza();
            // Se suman todas las lecturas del historial
            while (actual != nullptr) {
                suma += actual->dato;
                actual = actual->sig;
            }
            // Se calcula el promedio
            float promedio = static_cast<float>(suma) / historial.obtenerTamanio();
            std::cout << "Promedio de lecturas: " << promedio << std::endl;
        }

        void mostrarInfo() const override {
            // Se muestra tipo, nombre y cantidad de lecturas de sensor
            std::cout << "\n=== INFORMACION DEL SENSOR ===" << std::endl;
            std::cout << "Tipo: Presión" << std::endl;
            std::cout << "Nombre: " << obtenerNombre() << std::endl;
            std::cout << "Cantidad de lecturas: " << historial.obtenerTamanio() << std::endl;
            std::cout << "===============================" << std::endl;
        }
};

#endif 
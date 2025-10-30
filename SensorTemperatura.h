#ifndef SENSORTEMPERATURA_H
#define SENSORTEMPERATURA_H

#include <iostream>
#include "SensorBase.h"
#include "ListaSensor.h"

class SensorTemperatura : public SensorBase {
private:
    ListaSensor<float> historial;
    
public:
    SensorTemperatura(const char* nombreSensor) : SensorBase(nombreSensor) {
        std::cout << "Sensor de temperatura '" << obtenerNombre() << "' creado" << std::endl;
    }
    
    ~SensorTemperatura() {
        std::cout << "Sensor de temperatura '" << obtenerNombre() << "' destruido" << std::endl;
    }

    void registrarLectura(float valor) {
        historial.insertar(valor);
        std::cout << "Lectura registrada en sensor '" << obtenerNombre() << "': " << valor << "°C" << std::endl;
    }

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
        
        std::cout << "Lectura más baja encontrada: " << lecturaMasBaja << "°C" << std::endl;
        std::cout << "Eliminando lectura más baja..." << std::endl;

        historial.eliminarValor(lecturaMasBaja);

        std::cout << "Procesamiento completado (eliminación pendiente)" << std::endl;
    }

    void mostrarInfo() const override {
        std::cout << "\n=== INFORMACION DEL SENSOR ===" << std::endl;
        std::cout << "Tipo: Temperatura" << std::endl;
        std::cout << "Nombre: " << obtenerNombre() << std::endl;
        std::cout << "Cantidad de lecturas: " << historial.obtenerTamanio() << std::endl;
        std::cout << "===============================" << std::endl;
    }
};

#endif
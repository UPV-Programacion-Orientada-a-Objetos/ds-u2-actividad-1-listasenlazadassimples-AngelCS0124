#ifndef SENSORTEMPERATURA_H
#define SENSORTEMPERATURA_H

#include <iostream>
#include "SensorBase.h"
#include "ListaSensor.h"

class SensorTemperatura : public SensorBase {
    private:
        ListaSensor<float> historial;
    public:
        SensorTemperatura(const char* nombreSensor);
        ~SensorTemperatura();

        void procesarLectura() override {

        }

        void mostrarInfo() const override {
            std::cout << "INFORMACION DEL SENSOR" << std::endl;
            std::cout << "Tipo: Temperatura" << std::endl;
            std::cout << "Nombre: " << nombre << std::endl;
            std::cout << "Cantidad de lecturas almacenadas: " << 0 << std::endl;
            
        }
};

#endif 
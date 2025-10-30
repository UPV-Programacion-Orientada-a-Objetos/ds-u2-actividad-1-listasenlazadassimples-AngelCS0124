#ifndef SENSORBASE_H
#define SENSORBASE_H

class SensorBase {
    protected:
        char nombre[50];

    public:
        SensorBase(const char* nombreSensor);

        virtual ~SensorBase();

        virtual void procesarLectura() = 0;
        virtual void mostrarInfo() const = 0;

        const char* obtenerNombre() const;
};

#endif 
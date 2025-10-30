#ifndef SENSORBASE_H
#define SENSORBASE_H

class SensorBase {
    protected:
        char nombre[50];

    public:
        // Constructor
        SensorBase(const char* nombreSensor);
        // Destructor virtual
        virtual ~SensorBase();
        // Métodos virtuales puros
        virtual void procesarLectura() = 0;
        virtual void mostrarInfo() const = 0;

        const char* obtenerNombre() const { return nombre; }
};

#endif 
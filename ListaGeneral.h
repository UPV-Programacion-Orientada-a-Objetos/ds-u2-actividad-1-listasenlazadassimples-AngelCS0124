#ifndef LISTAGENERAL_H
#define LISTAGENERAL_H

#include <iostream>
#include "SensorBase.h"

// Nodo que almacena un puntero a SensorBase
struct NodoGeneral {
    SensorBase* sensor;
    NodoGeneral* siguiente;
};

class ListaGeneral {
private:
    // Puntero a la cabeza de la lista
    NodoGeneral* cabeza;

public:
    // Constructor inicializa la cabeza a nullptr
    ListaGeneral() : cabeza(nullptr) {}
    // Destructor libera toda la memoria de la lista
    ~ListaGeneral() {
        NodoGeneral* actual = cabeza;
        // Sigue liberando hasta que no haya más nodos
        while (actual != nullptr) {
            NodoGeneral* siguiente = actual->siguiente;
            // Log de liberación del sensor
            std::cout << "Liberando sensor: " << actual->sensor->obtenerNombre() << std::endl;
            delete actual->sensor;  
            delete actual;
            actual = siguiente;
        }
    }
    // Inserta un nuevo sensor al final de la lista
    void insertarSensor(SensorBase* sensor) {
        NodoGeneral* nuevoNodo = new NodoGeneral();
        nuevoNodo->sensor = sensor;
        nuevoNodo->siguiente = nullptr;
        
        if (cabeza == nullptr) {
            cabeza = nuevoNodo;
        } else {
            NodoGeneral* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevoNodo;
        }
        std::cout << "Sensor '" << sensor->obtenerNombre() << "' agregado a lista general" << std::endl;
    }
    // Ejecuta procesamiento polimórfico en todos los sensores
    void procesarTodos() {
        std::cout << "\nProcesando todos los sensores..." << std::endl;
        NodoGeneral* actual = cabeza;
        while (actual != nullptr) {
            actual->sensor->procesarLectura();
            actual = actual->siguiente;
        }
    }
    // Muestra información de todos los sensores en la lista
    void mostrarTodos() const {
        std::cout << "\n--- LISTA GENERAL DE SENSORES ---" << std::endl;
        NodoGeneral* actual = cabeza;
        while (actual != nullptr) {
            actual->sensor->mostrarInfo();  // Llamada polimórfica
            actual = actual->siguiente;
        }
    }
    // Busca un sensor por su nombre en la lista
    SensorBase* buscarSensor(const char* nombre) {
        NodoGeneral* actual = cabeza;
        while (actual != nullptr) {
            const char* nombreSensor = actual->sensor->obtenerNombre();
            int i = 0;
            // Se comparan los nombres carácter por carácter
            while (nombre[i] != '\0' && nombreSensor[i] != '\0' && nombre[i] == nombreSensor[i]) {
                i++;
            }
            if (nombre[i] == '\0' && nombreSensor[i] == '\0') {
                return actual->sensor;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }
    // Obtiene el puntero a la cabeza de la lista
    NodoGeneral* obtenerCabeza() const { return cabeza; }
};

#endif
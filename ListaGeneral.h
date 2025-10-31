#ifndef LISTAGENERAL_H
#define LISTAGENERAL_H

#include <iostream>
#include "SensorBase.h"

/**
 * @file ListaGeneral.h
 * @brief Lista enlazada para gestionar sensores de diferentes tipos
 * @author Angel Gabriel Coronado Sánchez
 * @date 2025
 */

/**
 * @struct NodoGeneral
 * @brief Nodo que almacena un puntero a SensorBase
 * 
 * Permite almacenar sensores de cualquier tipo derivado de SensorBase
 * mediante polimorfismo
 */
struct NodoGeneral {
    SensorBase* sensor;      ///< Puntero al sensor (polimórfico)
    NodoGeneral* siguiente;  ///< Puntero al siguiente nodo
};

/**
 * @class ListaGeneral
 * @brief Lista enlazada para gestionar una colección heterogénea de sensores
 * 
 * Esta lista permite almacenar diferentes tipos de sensores (temperatura,
 * presión, etc.) en una misma estructura mediante polimorfismo. Gestiona
 * automáticamente la memoria de los sensores almacenados.
 */
class ListaGeneral {
private:
    NodoGeneral* cabeza; ///< Puntero al primer nodo de la lista

public:
    /**
     * @brief Constructor por defecto
     * @post Inicializa la lista vacía con cabeza = nullptr
     */
    ListaGeneral() : cabeza(nullptr) {}
    
    /**
     * @brief Destructor de la lista general
     * @post Libera toda la memoria de nodos y sensores
     * 
     * Recorre la lista eliminando cada nodo y su sensor asociado.
     * Los sensores se destruyen polimórficamente.
     */
    ~ListaGeneral() {
        NodoGeneral* actual = cabeza;
        while (actual != nullptr) {
            NodoGeneral* siguiente = actual->siguiente;
            std::cout << "Liberando sensor: " << actual->sensor->obtenerNombre() << std::endl;
            delete actual->sensor;  
            delete actual;
            actual = siguiente;
        }
    }
    
    /**
     * @brief Inserta un nuevo sensor al final de la lista
     * @param sensor Puntero al sensor a insertar
     * @post El sensor se agrega al final de la lista
     * @warning La lista toma propiedad del puntero y lo liberará en el destructor
     */
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
    
    /**
     * @brief Ejecuta procesamiento polimórfico en todos los sensores
     * @post Llama al método procesarLectura() de cada sensor
     * 
     * Recorre la lista y ejecuta el procesamiento específico de cada
     * tipo de sensor mediante llamadas polimórficas
     */
    void procesarTodos() {
        std::cout << "\nProcesando todos los sensores..." << std::endl;
        NodoGeneral* actual = cabeza;
        while (actual != nullptr) {
            actual->sensor->procesarLectura();
            actual = actual->siguiente;
        }
    }
    
    /**
     * @brief Muestra información de todos los sensores en la lista
     * @post Imprime información detallada de cada sensor
     * 
     * Recorre la lista y ejecuta mostrarInfo() polimórficamente
     * para cada sensor
     */
    void mostrarTodos() const {
        std::cout << "\n--- LISTA GENERAL DE SENSORES ---" << std::endl;
        NodoGeneral* actual = cabeza;
        while (actual != nullptr) {
            actual->sensor->mostrarInfo();
            actual = actual->siguiente;
        }
    }
    
    /**
     * @brief Busca un sensor por su nombre en la lista
     * @param nombre Nombre del sensor a buscar
     * @return Puntero al sensor si se encuentra, nullptr en caso contrario
     * 
     * Realiza comparación carácter por carácter del nombre
     */
    SensorBase* buscarSensor(const char* nombre) {
        NodoGeneral* actual = cabeza;
        while (actual != nullptr) {
            const char* nombreSensor = actual->sensor->obtenerNombre();
            int i = 0;
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
    
    /**
     * @brief Obtiene el puntero a la cabeza de la lista
     * @return Puntero al primer nodo de la lista
     */
    NodoGeneral* obtenerCabeza() const { return cabeza; }
};

#endif
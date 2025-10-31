#ifndef LISTASENSOR_H
#define LISTASENSOR_H

#include <iostream>

/**
 * @file ListaSensor.h
 * @brief Implementación de lista enlazada simple genérica mediante templates
 * @author Angel Gabriel Coronado Sánchez
 * @date 2025
 */

/**
 * @struct Nodo
 * @brief Nodo de lista enlazada simple con tipo de dato genérico
 * @tparam T Tipo de dato que almacenará el nodo
 */
template <typename T>
struct Nodo {
    T dato;         ///< Valor almacenado en el nodo
    Nodo<T>* sig;   ///< Puntero al siguiente nodo en la lista
};

/**
 * @class ListaSensor
 * @brief Lista enlazada simple genérica para almacenar lecturas de sensores
 * @tparam T Tipo de dato que almacenará la lista (int, float, etc.)
 * 
 * Implementa una lista enlazada simple con operaciones básicas de inserción,
 * búsqueda, eliminación y consulta. Gestiona automáticamente la memoria
 * mediante constructores de copia y destructores.
 */
template <typename T>
class ListaSensor {
    private:
        Nodo<T>* cabeza; ///< Puntero al primer nodo de la lista
        
    public:
        /**
         * @brief Constructor por defecto
         * @post Inicializa la lista vacía con cabeza = nullptr
         */
        ListaSensor() : cabeza(nullptr) {}
        
        /**
         * @brief Constructor de copia
         * @param otra Referencia a la lista que se va a copiar
         * @post Crea una copia profunda de la lista original
         */
        ListaSensor(const ListaSensor<T>& otra) : cabeza(nullptr) {
            Nodo<T>* actual = otra.cabeza;
            while (actual != nullptr) {
                insertar(actual->dato);
                actual = actual->sig;
            }
        }
        
        /**
         * @brief Operador de asignación
         * @param otra Referencia a la lista que se va a asignar
         * @return Referencia a esta lista
         * @post Libera la memoria actual y crea una copia de la otra lista
         */
        ListaSensor<T>& operator=(const ListaSensor<T>& otra) {
            if (this != &otra) {
                Nodo<T>* actual = cabeza;
                while (actual != nullptr) {
                    Nodo<T>* sig = actual->sig;
                    delete actual;
                    actual = sig;
                }
                cabeza = nullptr;

                actual = otra.cabeza;
                while (actual != nullptr) {
                    insertar(actual->dato);
                    actual = actual->sig;
                }
            }
            return *this;
        }
        
        /**
         * @brief Destructor de la lista
         * @post Libera toda la memoria dinámica de los nodos
         * 
         * Recorre la lista eliminando cada nodo y liberando su memoria.
         * Imprime mensajes de log para cada nodo destruido.
         */
        ~ListaSensor() {
            Nodo<T>* actual = cabeza;
            while (actual != nullptr) {
                Nodo<T>* sig = actual->sig;
                std::cout << "Nodo con valor: " << actual->dato << " destruido" << std::endl;
                delete actual;
                actual = sig;
            }
        }
        
        /**
         * @brief Inserta un nuevo elemento al final de la lista
         * @param valor Valor a insertar en la lista
         * @post Se agrega un nuevo nodo al final de la lista
         */
        void insertar(T valor) {
            Nodo<T>* nuevoNodo = new Nodo<T>();
            nuevoNodo->dato = valor;
            nuevoNodo->sig = nullptr;
            
            if (cabeza == nullptr) {
                cabeza = nuevoNodo;
            } else {
                Nodo<T>* actual = cabeza;
                while (actual->sig != nullptr) {
                    actual = actual->sig;
                }
                actual->sig = nuevoNodo;
                std::cout << "Nodo insertado: " << valor << std::endl;
            }
        }
        
        /**
         * @brief Busca un valor en la lista
         * @param valor Valor a buscar
         * @return true si el valor existe en la lista, false en caso contrario
         */
        bool busqueda(T valor) {
            Nodo<T>* actual = cabeza;
            while (actual != nullptr) {
                if(actual->dato == valor) {
                    return true;
                }
                actual = actual->sig;
            }
            return false;
        }
        
        /**
         * @brief Calcula el número de elementos en la lista
         * @return Cantidad de nodos en la lista
         */
        int obtenerTamanio() const {
            int contador = 0;
            Nodo<T>* actual = cabeza;
            while (actual != nullptr) {
                contador++;
                actual = actual->sig;
            }
            return contador;
        }
        
        /**
         * @brief Elimina el primer nodo que contenga el valor especificado
         * @param valor Valor a eliminar de la lista
         * @return true si se eliminó el valor, false si no se encontró
         * @post El nodo con el valor especificado es eliminado de la lista
         */
        bool eliminarValor(T valor) {
            if (cabeza == nullptr) return false;
            
            if (cabeza->dato == valor) {
                Nodo<T>* temp = cabeza;
                cabeza = cabeza->sig;
                std::cout << "Nodo eliminado: " << temp->dato << std::endl;
                delete temp;
                return true;
            }
            
            Nodo<T>* actual = cabeza;
            while (actual->sig != nullptr && actual->sig->dato != valor) {
                actual = actual->sig;
            }
            
            if (actual->sig == nullptr) {
                std::cout << "Valor no encontrado: " << valor << std::endl;
                return false;
            }
            
            Nodo<T>* temp = actual->sig;
            actual->sig = temp->sig;
            std::cout << "Nodo eliminado: " << temp->dato << std::endl;
            delete temp;
            return true;
        }
        
        /**
         * @brief Obtiene el puntero a la cabeza de la lista
         * @return Puntero al primer nodo de la lista
         */
        Nodo<T>* obtenerCabeza() const { return cabeza; }
};

#endif
#ifndef LISTASENSOR_H
#define LISTASENSOR_H

#include <iostream>

// Definición del nodo con dato y sig
template <typename T>
struct Nodo {
    T dato;
    Nodo <T>* sig;
};

template <typename T>
class ListaSensor {
    private:
        // Puntero a la cabeza de la lista
        Nodo<T>* cabeza;
    public:
        // Constructor con inicialización de cabeza a nullptr
        ListaSensor() : cabeza(nullptr) {}
        // Constructor de copia
        ListaSensor(const ListaSensor<T>& otra) : cabeza(nullptr) {
            Nodo<T>* actual = otra.cabeza;
            while (actual != nullptr) {
                insertar(actual->dato);
                actual = actual->sig;
            }
        }
        // Operador de asignación
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
        // Destructor que libera memoria de todos los nodos (hasta que encuentra nullptr)
        ~ListaSensor() {
            Nodo<T>* actual = cabeza;
            while (actual != nullptr) {
                Nodo<T>* sig = actual->sig;
                std::cout << "Nodo con valor: " << actual->dato << " destruido" << std::endl;
                delete actual;
                actual = sig;
            }
        }
        // Inserción de un nuevo nodo al final de la lista
        void insertar(T valor) {
            Nodo<T>* nuevoNodo = new Nodo<T>();
            nuevoNodo->dato = valor;
            nuevoNodo->sig = nullptr;
            // Si la lista está vacía, se agrega como cabeza
            if (cabeza == nullptr) {
                cabeza = nuevoNodo;
            } else {
                Nodo<T>* actual = cabeza;

                while (actual->sig != nullptr) {
                    actual = actual->sig;
                }
                actual->sig = nuevoNodo;
                // Log de inserción de nodo
                std::cout << "Nodo insertado: " << valor << std::endl;
            }
        }
        // Búsqueda de un valor en la lista
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
        // Cuenta los elementos en la lista hasta encontrar nullptr
        int obtenerTamanio() const {
            int contador = 0;
            Nodo<T>* actual = cabeza;

            while (actual != nullptr) {
                contador++;
                actual = actual->sig;
            }
            return contador;
        }
        // Elimina el primer nodo que coincida con el valor dado
        bool eliminarValor(T valor) {
            // Si la lista está vacía, no hay nada que eliminar
            if (cabeza == nullptr) return false;
            // Si el valor a eliminar está en la cabeza, se actualiza la cabeza
            if (cabeza->dato == valor) {
                Nodo<T>* temp = cabeza;
                cabeza = cabeza->sig;
                std::cout << "Nodo eliminado: " << temp->dato << std::endl;
                delete temp;
                return true;
            }
            
            Nodo<T>* actual = cabeza;
            // Se busca el nodo anterior al que se quiere eliminar, hasta que se encuentra o se llega al final
            while (actual->sig != nullptr && actual->sig->dato != valor) {
                actual = actual->sig;
            }
            // Si se llega al final y no se encuenra el valor
            if (actual->sig == nullptr) {
                std::cout << "Valor no encontrado: " << valor << std::endl;
                return false;
            }
            // Si se encontro el valor, se elimina el nodo ajustando los punteros
            Nodo<T>* temp = actual->sig;
            actual->sig = temp->sig;
            std::cout << "Nodo eliminado: " << temp->dato << std::endl;
            delete temp;
            return true;
        }
        // Devuelve el puntero a la cabeza de la lista
        Nodo<T>* obtenerCabeza() const { return cabeza; }
};

#endif
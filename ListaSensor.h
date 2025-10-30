#include <iostream>

template <typename T>
struct Nodo {
    T dato;
    Nodo <T>* sig;
};

template <typename T>
class ListaSensor {
    private:
        Nodo<T>* cabeza;
    public:
        ListaSensor() : cabeza(nullptr) {}

        ListaSensor(const ListaSensor<T>& otra) : cabeza(nullptr) {
            Nodo<T>* actual = otra.cabeza;
            while (actual != nullptr) {
                insertar(actual->dato);
                actual = actual->sig;
            }
        }

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
        
        ~ListaSensor() {
            Nodo<T>* actual = cabeza;
            while (actual != nullptr) {
                Nodo<T>* sig = actual->sig;
                std::cout << "Nodo con valor: " << actual->dato << " destruido" << std::endl;
                delete actual;
                actual = sig;
            }
        }

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
};
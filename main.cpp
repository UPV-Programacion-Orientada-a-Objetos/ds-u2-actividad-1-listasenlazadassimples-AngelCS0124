#include <iostream>
#include "SensorTemperatura.h"
#include "SensorPresion.h"
#include "ListaGeneral.h"

int mostrarMenu();
void crearSensorTemperatura(ListaGeneral& lista);
void crearSensorPresion(ListaGeneral& lista);
void registrarLecturaSensor(ListaGeneral& lista);
void imprimirMensaje(const char* tipo, const char* mensaje);
void limpiarBuffer();
template<typename T> bool esEntradaValida();

int main() {
    ListaGeneral listaSensores;
    int opcion = 0;
    
    std::cout << "=== SISTEMA DE IoT ===" << std::endl;
    
    do {
        opcion = mostrarMenu();
        
        if (!esEntradaValida()) {
            imprimirMensaje("Advertencia", "Ingrese un numero valido");
            limpiarBuffer();
            continue;
        }
        
        switch(opcion) {
            case 1:
                crearSensorTemperatura(listaSensores);
                break;
            case 2:
                crearSensorPresion(listaSensores);
                break;
            case 3:
                registrarLecturaSensor(listaSensores);
                break;
            case 4:
                listaSensores.mostrarTodos();
                break;
            case 5:
                listaSensores.procesarTodos();
                break;
            case 6:
                imprimirMensaje("Info", "Saliendo y liberando memoria...");
                break;
            default:
                imprimirMensaje("Advertencia", "Opcion invalida");
                break;
        }
        
    } while (opcion != 6);
    
    imprimirMensaje("Info", "Programa finalizado correctamente");
    return 0;
}

int mostrarMenu() {
    int opcion;
    std::cout << "\n--- MENU PRINCIPAL ---" << std::endl;
    std::cout << "1. Crear Sensor de Temperatura" << std::endl;
    std::cout << "2. Crear Sensor de Presion" << std::endl;
    std::cout << "3. Registrar Lectura en Sensor" << std::endl;
    std::cout << "4. Mostrar Informacion de Sensores" << std::endl;
    std::cout << "5. Procesar Todas las Lecturas" << std::endl;
    std::cout << "6. Salir y Liberar Memoria" << std::endl;
    std::cout << "Seleccione opcion: ";
    std::cin >> opcion;
    return opcion;
}

void crearSensorTemperatura(ListaGeneral& lista) {
    char nombre[50];
    std::cout << "Ingrese nombre del sensor temperatura: ";
    std::cin >> nombre;
    SensorTemperatura* tempSensor = new SensorTemperatura(nombre);
    lista.insertarSensor(tempSensor);
}

void crearSensorPresion(ListaGeneral& lista) {
    char nombre[50];
    std::cout << "Ingrese nombre del sensor presion: ";
    std::cin >> nombre;
    SensorPresion* presSensor = new SensorPresion(nombre);
    lista.insertarSensor(presSensor);
}

void registrarLecturaSensor(ListaGeneral& lista) {
    char nombre[50];
    std::cout << "Ingrese nombre del sensor: ";
    std::cin >> nombre;
    
    SensorBase* sensor = lista.buscarSensor(nombre);
    if (sensor == nullptr) {
        imprimirMensaje("Advertencia", "Sensor no encontrado");
        return;
    }
    
    // Determinar tipo de sensor para lectura correcta
    SensorTemperatura* tempSensor = dynamic_cast<SensorTemperatura*>(sensor);
    if (tempSensor != nullptr) {
        float lectura;
        std::cout << "Ingrese lectura de temperatura: ";
        std::cin >> lectura;
        if (!esEntradaValida()) {
            imprimirMensaje("Advertencia", "Entrada invalida");
            limpiarBuffer();
            return;
        }
        tempSensor->registrarLectura(lectura);
        imprimirMensaje("Exito", "Lectura de temperatura registrada");
        return;
    }
    
    SensorPresion* presSensor = dynamic_cast<SensorPresion*>(sensor);
    if (presSensor != nullptr) {
        int lectura;
        std::cout << "Ingrese lectura de presion: ";
        std::cin >> lectura;
        if (!esEntradaValida()) {
            imprimirMensaje("Advertencia", "Entrada invalida");
            limpiarBuffer();
            return;
        }
        presSensor->registrarLectura(lectura);
        imprimirMensaje("Exito", "Lectura de presion registrada");
        return;
    }
    
    imprimirMensaje("Error", "Tipo de sensor desconocido");
}
// Validación de tipo de entrada
bool esEntradaValida() {
    if (!std::cin.good()) {
        return false;
    }
    // Verificar que no quedó basura en el buffer
    return std::cin.peek() == '\n';
}
// Limpieza del buffer de entrada
void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(1000, '\n');
}
// Impresión de mensajes con tipo y mensaje
void imprimirMensaje(const char* tipo, const char* mensaje) {
    std::cout << "[" << tipo << "] " << mensaje << std::endl;
}
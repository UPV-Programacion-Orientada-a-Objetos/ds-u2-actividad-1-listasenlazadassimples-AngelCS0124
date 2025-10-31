#include <iostream>
#include <windows.h>
#include <chrono>
#include "SensorTemperatura.h"
#include "SensorPresion.h"
#include "ListaGeneral.h"

/**
 * @file main.cpp
 * @brief Programa principal del sistema IoT de monitoreo polimórfico
 * @author Angel Gabriel Coronado Sánchez
 * @date 2025
 * 
 * Sistema de monitoreo que lee datos de sensores desde un dispositivo ESP32
 * conectado por puerto serial (COM6) y los procesa mediante polimorfismo
 */

// Prototipos de funciones
int mostrarMenu();
void crearSensorTemperatura(ListaGeneral& lista);
void crearSensorPresion(ListaGeneral& lista);
void leerDatosESP32(ListaGeneral& lista);
void imprimirMensaje(const char* tipo, const char* mensaje);
void limpiarBuffer();
bool esEntradaValida();

/**
 * @brief Lee datos en tiempo real desde el dispositivo ESP32
 * @param lista Referencia a la lista general de sensores
 * @post Lee datos del puerto COM6 durante 30 segundos y los registra en los sensores
 * 
 * Establece comunicación serial con ESP32, configura parámetros del puerto,
 * lee datos en formato CSV (TEMP,timestamp,valor o PRES,timestamp,valor)
 * y los registra en los sensores correspondientes
 */
void leerDatosESP32(ListaGeneral& lista) {
    std::cout << "\n=== LECTURA DESDE ESP32 (COM6) ===" << std::endl;
    std::cout << "Conectando con dispositivo IoT..." << std::endl;
    
    HANDLE hSerial = CreateFileA("\\\\.\\COM6", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    
    if (hSerial == INVALID_HANDLE_VALUE) {
        imprimirMensaje("Error", "No se pudo conectar con ESP32 en COM6");
        std::cout << "Verifica que:" << std::endl;
        std::cout << "1. La ESP32 este conectada por USB" << std::endl;
        std::cout << "2. Este programada con el codigo de sensores" << std::endl;
        std::cout << "3. El puerto COM6 este disponible" << std::endl;
        return;
    }
    
    // Configurar puerto serial
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        imprimirMensaje("Error", "Error en configuracion serial");
        CloseHandle(hSerial);
        return;
    }
    
    dcbSerialParams.BaudRate = 9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        imprimirMensaje("Error", "Error configurando puerto serial");
        CloseHandle(hSerial);
        return;
    }
    
    // Configurar timeouts
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);
    
    std::cout << "Conectado a ESP32" << std::endl;
    std::cout << "Leyendo datos por 30 segundos..." << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    char buffer[256];
    DWORD bytesRead;
    std::string datosAcumulados = "";
    int lecturasRegistradas = 0;
    
    // Crear sensores por defecto si no existen
    if (lista.buscarSensor("T-001") == nullptr) {
        SensorTemperatura* tempSensor = new SensorTemperatura("T-001");
        lista.insertarSensor(tempSensor);
        std::cout << "Sensor T-001 (Temperatura) creado" << std::endl;
    }
    if (lista.buscarSensor("P-001") == nullptr) {
        SensorPresion* presSensor = new SensorPresion("P-001");
        lista.insertarSensor(presSensor);
        std::cout << "Sensor P-001 (Presion) creado" << std::endl;
    }
    
    auto startTime = std::chrono::steady_clock::now();
    
    // Leer datos durante 30 segundos
    while (std::chrono::steady_clock::now() - startTime < std::chrono::seconds(30)) {
        if (ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
            buffer[bytesRead] = '\0';
            datosAcumulados += buffer;
            
            // Procesar lineas completas
            size_t pos;
            while ((pos = datosAcumulados.find('\n')) != std::string::npos) {
                std::string linea = datosAcumulados.substr(0, pos);
                datosAcumulados = datosAcumulados.substr(pos + 1);
                
                // Limpiar retorno de carro si existe
                if (!linea.empty() && linea.back() == '\r') {
                    linea.pop_back();
                }
                
                if (!linea.empty()) {
                    std::cout << "[ESP32] " << linea << std::endl;
                    
                    // Procesar datos de temperatura
                    if (linea.find("TEMP,") == 0) {
                        size_t lastComma = linea.find_last_of(",");
                        if (lastComma != std::string::npos) {
                            std::string valorStr = linea.substr(lastComma + 1);
                            try {
                                float temp = std::stof(valorStr);
                                SensorBase* sensor = lista.buscarSensor("T-001");
                                if (sensor) {
                                    SensorTemperatura* tempSensor = dynamic_cast<SensorTemperatura*>(sensor);
                                    if (tempSensor) {
                                        tempSensor->registrarLectura(temp);
                                        std::cout << "Temperatura registrada: " << temp << std::endl;
                                        lecturasRegistradas++;
                                    }
                                }
                            } catch (const std::exception& e) {
                                std::cout << "Error en dato de temperatura: " << valorStr << std::endl;
                            }
                        }
                    }
                    // Procesar datos de presion
                    else if (linea.find("PRES,") == 0) {
                        size_t lastComma = linea.find_last_of(",");
                        if (lastComma != std::string::npos) {
                            std::string valorStr = linea.substr(lastComma + 1);
                            try {
                                int pres = std::stoi(valorStr);
                                SensorBase* sensor = lista.buscarSensor("P-001");
                                if (sensor) {
                                    SensorPresion* presSensor = dynamic_cast<SensorPresion*>(sensor);
                                    if (presSensor) {
                                        presSensor->registrarLectura(pres);
                                        std::cout << "Presion registrada: " << pres << std::endl;
                                        lecturasRegistradas++;
                                    }
                                }
                            } catch (const std::exception& e) {
                                std::cout << "Error en dato de presion: " << valorStr << std::endl;
                            }
                        }
                    }
                }
            }
        }
        
        Sleep(100);
    }
    
    CloseHandle(hSerial);
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Tiempo de lectura completado (30 segundos)" << std::endl;
    std::cout << "Total de lecturas registradas: " << lecturasRegistradas << std::endl;
    std::cout << "Conexion serial cerrada" << std::endl;
}

/**
 * @brief Función principal del programa
 * @return 0 si el programa termina correctamente
 * 
 * Inicializa el sistema, muestra el menú principal y gestiona el flujo
 * del programa mediante un ciclo que permite crear sensores, leer datos
 * desde ESP32 y procesar información
 */
int main() {
    ListaGeneral listaSensores;
    int opcion = 0;
    
    std::cout << "=== SISTEMA IoT DE MONITOREO POLIMORFICO ===" << std::endl;
    std::cout << ">>> Entrada exclusiva por dispositivo ESP32 <<<" << std::endl;
    
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
                leerDatosESP32(listaSensores);
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

/**
 * @brief Muestra el menú principal y obtiene la opción del usuario
 * @return Opción seleccionada por el usuario
 * 
 * Presenta las opciones disponibles del sistema y lee la selección
 */
int mostrarMenu() {
    int opcion;
    std::cout << "\n--- MENU PRINCIPAL ---" << std::endl;
    std::cout << "1. Crear Sensor de Temperatura" << std::endl;
    std::cout << "2. Crear Sensor de Presion" << std::endl;
    std::cout << "3. Leer Datos desde ESP32 (COM6)" << std::endl;
    std::cout << "4. Mostrar Informacion de Sensores" << std::endl;
    std::cout << "5. Procesar Todas las Lecturas" << std::endl;
    std::cout << "6. Salir y Liberar Memoria" << std::endl;
    std::cout << "Seleccione opcion: ";
    std::cin >> opcion;
    return opcion;
}

/**
 * @brief Crea un nuevo sensor de temperatura y lo agrega a la lista
 * @param lista Referencia a la lista general de sensores
 * @post Crea un sensor de temperatura con el nombre especificado por el usuario
 */
void crearSensorTemperatura(ListaGeneral& lista) {
    char nombre[50];
    std::cout << "Ingrese nombre del sensor temperatura: ";
    std::cin >> nombre;
    SensorTemperatura* tempSensor = new SensorTemperatura(nombre);
    lista.insertarSensor(tempSensor);
}

/**
 * @brief Crea un nuevo sensor de presión y lo agrega a la lista
 * @param lista Referencia a la lista general de sensores
 * @post Crea un sensor de presión con el nombre especificado por el usuario
 */
void crearSensorPresion(ListaGeneral& lista) {
    char nombre[50];
    std::cout << "Ingrese nombre del sensor presion: ";
    std::cin >> nombre;
    SensorPresion* presSensor = new SensorPresion(nombre);
    lista.insertarSensor(presSensor);
}

/**
 * @brief Imprime un mensaje formateado con tipo y contenido
 * @param tipo Tipo de mensaje (Error, Advertencia, Info, etc.)
 * @param mensaje Contenido del mensaje a mostrar
 * @post Imprime el mensaje en formato [Tipo] Mensaje
 */
void imprimirMensaje(const char* tipo, const char* mensaje) {
    std::cout << "[" << tipo << "] " << mensaje << std::endl;
}

/**
 * @brief Valida si la entrada del usuario es correcta
 * @return true si la entrada es válida, false en caso contrario
 * 
 * Verifica que el estado del stream de entrada sea correcto y que
 * el siguiente carácter sea un salto de línea
 */
bool esEntradaValida() {
    if (!std::cin.good()) {
        return false;
    }
    return std::cin.peek() == '\n';
}

/**
 * @brief Limpia el buffer de entrada estándar
 * @post Restablece el estado del stream y descarta caracteres no procesados
 * 
 * Útil para limpiar entradas inválidas y prevenir errores en lecturas posteriores
 */
void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(1000, '\n');
}
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>

using namespace std;
// 1. Estructura que define el Nodo y sus atributos
struct Nodo {
    string nombre;
    int precio;
    string calidad;

    // Función para imprimir el nodo
    void imprimir() const {
        cout << "\n--- Nodo Creado ---\n";
        cout << "  Nombre:  " << nombre << "\n";
        cout << "  Precio:  " << precio << "\n";
        cout << "  Calidad: " << calidad << "\n";
        cout << "-------------------\n";
    }
};

/**
 * Función que crea y retorna un Nodo con atributos aleatorios.
 */
Nodo crear_nodo_aleatorio() {
    // Definición de los posibles valores
    const vector<string> NOMBRES = {"tornillo", "clavo", "remache"};
    const vector<int> PRECIOS = {5, 10, 15};
    const vector<string> CALIDADES = {"buena", "mala", "regular"};

    static mt19937 generador(static_cast<unsigned int>(time(0))); 
// Contenedores temporales para almacenar la selección (solo necesitamos 1 elemento)
    string nombre_elegido;
    int precio_elegido;
    string calidad_elegida;

    
    // 1. Seleccionar Nombre: Toma un elemento (1) del rango NOMBRES y lo pone en 'nombre_elegido'
    sample(NOMBRES.begin(), NOMBRES.end(), 
               &nombre_elegido, 1, generador);

    // 2. Seleccionar Precio: Toma un elemento (1) del rango PRECIOS y lo pone en 'precio_elegido'
    sample(PRECIOS.begin(), PRECIOS.end(), 
               &precio_elegido, 1, generador);

    // 3. Seleccionar Calidad: Toma un elemento (1) del rango CALIDADES y lo pone en 'calidad_elegida'
    sample(CALIDADES.begin(), CALIDADES.end(), 
               &calidad_elegida, 1, generador);
    // Crear y retornar el nodo
    return Nodo{nombre_elegido, precio_elegido, calidad_elegida};
}

// Función del menú principal
void mostrar_menu() {
    cout << "\n=========================================\n";
    cout << "         GENERADOR DE PRODUCTOS ALEATORIOS   \n";
    cout << "=========================================\n";
    cout << "1. Crear un nuevo producto de ferretería \n";
    cout << "2. Salir\n";
    cout << "Ingrese su opción: ";
}

int main() {
    int opcion;
    
    do {
        mostrar_menu();
        cin >> opcion;
        // Manejo de entrada del usuario
        if (!(opcion)) {
            cout << "Entrada inválida. Por favor, ingrese un número.\n";
            cin.clear(); // Limpia la bandera de error
            cin.ignore(10000, '\n'); // Descarta la entrada errónea
            continue;
        }

        switch (opcion) {
            case 1: {
                // Interacción: Llamada a la función de creación de nodo
                Nodo nuevo_nodo = crear_nodo_aleatorio();
                nuevo_nodo.imprimir();
                break;
            }
            case 2:
                cout << "\n¡Saliendo del programa!\n";
                break;
            default:
                cout << "Opción no valida. Intente de nuevo.\n";
                break;
        }
    } while (opcion != 2);

    return 0;
}
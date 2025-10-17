#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

using namespace std;
// Variables Globales y Recursos Compartidos
queue<int> cola_datos;          // La "cinta transportadora" compartida
mutex cola_mutex;               // Candado (Mutex) para proteger la cola
condition_variable cv;         // Variable de Condición para la notificación
const int MAX_PRODUCTOS = 10;        // Número de productos a generar
bool produccion_terminada = false;   // Bandera para indicar el fin

// 1. Hilo PRODUCTOR
void productor() {
    for (int i = 1; i <= MAX_PRODUCTOS; ++i) {
        // Simular el tiempo que toma producir un artículo
        this_thread::sleep_for(chrono::milliseconds(500)); 
        
        // --- Región Crítica (Productor) ---
        // Usamos un bloque para limitar el alcance del lock_guard
        {
            lock_guard<mutex> lock(cola_mutex);
            cola_datos.push(i);
            cout << "Productor: Producto [" << i << "] creado y colocado en la cola.\n";
        }
        // El lock_guard libera el mutex automáticamente aquí.
        
        // Notificar al consumidor que hay un nuevo dato
        cv.notify_one(); 
    }
    
    // Señalizar el final de la producción
    {
        lock_guard<mutex> lock(cola_mutex);
        produccion_terminada = true;
    }
    cout << "\n--- Productor ha finalizado su trabajo ---\n";
    // Notificar a todos los hilos en espera para que revisen la bandera de salida
    cv.notify_all(); 
}

// 2. Hilo CONSUMIDOR
void consumidor(int id) {
    int dato;
    
    while (true) {
        // Usamos unique_lock porque condition_variable lo requiere para liberar el mutex durante la espera
        unique_lock<mutex> lock(cola_mutex); 
        
        // Esperar la condición: La cola no está vacía O la producción ha terminado
        // wait() libera el mutex mientras espera, y lo readquiere al ser notificado
        cv.wait(lock, []{ return !cola_datos.empty() || produccion_terminada; });

        // Verificar la condición de salida: Si la cola está vacía Y el productor terminó, salimos.
        if (cola_datos.empty() && produccion_terminada) {
            cout << "Consumidor " << id << ": Producción finalizada. Saliendo.\n";
            break; 
        }

        // --- Región Crítica (Consumidor) ---
        // Tomar el dato solo si la cola NO está vacía
        if (!cola_datos.empty()) {
            dato = cola_datos.front();
            cola_datos.pop();
            
            // El lock se mantiene hasta el final del ámbito, o podemos liberarlo aquí:
            lock.unlock(); 

            // Simular el tiempo que toma procesar el artículo (fuera de la región crítica)
            cout << "Consumidor " << id << ": Procesa el dato [" << dato << "]\n";
            this_thread::sleep_for(chrono::milliseconds(800)); 
        }
    }
}

int main() {
    cout << "Iniciando simulacion Productor-Consumidor...\n";
    
    // Crear el hilo Productor
    thread hilo_productor(productor);
    
    // Crear dos hilos Consumidores
    thread consumidor1(consumidor, 1);
    thread consumidor2(consumidor, 2);

    // Esperar a que todos los hilos terminen su trabajo
    hilo_productor.join();
    consumidor1.join();
    consumidor2.join();

    cout << "\nTodos los hilos han terminado. Simulación completa.\n";
    return 0;
}
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <semaphore> // Se requiere para std::counting_semaphore

using namespace std;
// Semáforo con un contador inicial de 3. Solo 3 hilos pueden 'adquirir' el recurso a la vez.
counting_semaphore<3> limite_recurso(3); 

void usar_recurso(int id) {
    cout << "Hilo " << id << " esperando adquirir el recurso...\n";
    
    // Adquirir (Decrementar el contador. Bloquea si el contador es 0)
    limite_recurso.acquire(); 
    
    cout << "Hilo " << id << " >>> ESTÁ USANDO EL RECURSO CRÍTICO <<<\n";
    
    // Simular el uso del recurso
    this_thread::sleep_for(chrono::seconds(1));
    
    cout << "Hilo " << id << " ha terminado de usar el recurso.\n";
    
    // Liberar (Incrementar el contador. Despierta a un hilo en espera si el contador era 0)
    limite_recurso.release();
}

int main() {
    const int num_hilos = 6; // Intentaremos lanzar 6 hilos
    vector<thread> hilos;

    // Crear y lanzar los 6 hilos
    for (int i = 1; i <= num_hilos; ++i) {
        hilos.emplace_back(usar_recurso, i);
        // Pequeña pausa para asegurar que los hilos se lancen casi simultáneamente.
        this_thread::sleep_for(chrono::milliseconds(10));
    }

    // Esperar a que todos los hilos terminen
    for (auto& t : hilos) {
        t.join();
    }
    
    cout << "Todos los hilos han terminado de usar el recurso.\n";
    return 0;
}
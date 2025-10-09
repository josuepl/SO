#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;
// Recurso compartido
int contador_compartido = 0;
// Mutex para proteger el recurso
mutex contador_mutex;

void incrementar_seguro() {
    for (int i = 0; i < 100; ++i) {
        // CANDADO: lock_guard bloquea el mutex al entrar y lo libera al salir del ámbito.
        lock_guard<mutex> lock(contador_mutex);
        
        // --- Región Crítica ---
        contador_compartido++;
        // --- Fin Región Crítica ---
        
        // El 'lock' se destruye aquí al final del bucle, liberando el Mutex.
    }
}

int main() {
    const int num_hilos = 10;
    vector<thread> hilos;

    // Crear y lanzar hilos
    for (int i = 0; i < num_hilos; ++i) {
        hilos.emplace_back(incrementar_seguro);
    }

    // Esperar a que todos los hilos terminen
    for (auto& t : hilos) {
        t.join();
    }

    cout << "Resultado final con Mutex/lock_guard: " << contador_compartido << " (Esperado: 1000)\n";
    return 0;
}
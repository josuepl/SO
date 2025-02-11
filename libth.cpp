#include <iostream>
#include <thread> // Necesario para trabajar con hilos
#include <vector>

using namespace std;

// Función que será ejecutada por cada hilo
void imprimirMensaje(int id) {
    cout << "Hola desde el hilo " << id << endl;
}

int main() {
    const int NUM_HILOS = 5; // Número de hilos que queremos crear
    vector<thread> hilos;    // Vector para almacenar los objetos thread

    // Crear y lanzar los hilos
    for (int i = 0; i < NUM_HILOS; ++i) {
        hilos.push_back(thread(imprimirMensaje, i)); // Se pasa la función y el argumento
    }

    // Esperar a que todos los hilos terminen su ejecución
    for (auto& hilo : hilos) {
        hilo.join();  // Unir cada hilo con el hilo principal
    }

    cout << "Todos los hilos han terminado." << endl;

    return 0;
}

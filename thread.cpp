#include <iostream>
#include <pthread.h>

void* hola_mundo(void* arg) {
    std::cout << "¡Hola, mundo desde el hilo!" << std::endl;
    return nullptr;
}

int main() {
    pthread_t hilo;  // Identificador del hilo

    // Crear un hilo
    if (pthread_create(&hilo, nullptr, hola_mundo, nullptr) != 0) {
        std::cerr << "Error al crear el hilo" << std::endl;
        return 1;
    }

    // Esperar a que el hilo termine
    if (pthread_join(hilo, nullptr) != 0) {
        std::cerr << "Error al esperar el hilo" << std::endl;
        return 1;
    }

    std::cout << "Hilo principal terminado" << std::endl;
    return 0;
}

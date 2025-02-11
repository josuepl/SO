#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

// Función que ejecutarán los hilos
void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    printf("Hola desde el hilo %d, %lu -> PID:%d\n", thread_id, pthread_self(), getpid());
    sleep(1);  // Simula alguna tarea
    printf("Hilo %d finalizó\n", thread_id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Crear hilos
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function, (void*)&thread_ids[i]) != 0) {
            perror("Error creando el hilo");
            exit(EXIT_FAILURE);
        }
    }

    // Esperar a que los hilos terminen
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Todos los hilos han finalizado.\n");
    return 0;
}
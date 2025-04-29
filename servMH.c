#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PUERTO 8080
#define TAM_BUFFER 1024

// Estructura para pasar datos a los hilos
typedef struct {
    int cliente_fd;  // Descriptor del socket del cliente
    struct sockaddr_in direccion;  // Dirección del cliente
} datos_cliente_t;

// Función que maneja cada cliente en un hilo separado
void *manejar_cliente(void *arg) {
    datos_cliente_t *datos = (datos_cliente_t *)arg;
    char buffer[TAM_BUFFER] = {0};
    char respuesta[TAM_BUFFER] = {0};

    // Leer mensaje del cliente
    read(datos->cliente_fd, buffer, TAM_BUFFER);
    printf("Cliente %s:%d dice: %s\n", 
           inet_ntoa(datos->direccion.sin_addr), 
           ntohs(datos->direccion.sin_port), 
           buffer);

    // Preparar respuesta
    snprintf(respuesta, TAM_BUFFER, "¡Hola, %s! Soy el servidor.", buffer);

    // Enviar respuesta
    send(datos->cliente_fd, respuesta, strlen(respuesta), 0);

    // Cerrar conexión con este cliente
    close(datos->cliente_fd);
    free(datos);  // Liberar memoria de la estructura

    pthread_exit(NULL);
}

int main() {
    int servidor_fd;
    struct sockaddr_in direccion;

    // Crear socket
    if ((servidor_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Error al crear socket");
        exit(EXIT_FAILURE);
    }

    // Configurar dirección
    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = INADDR_ANY;
    direccion.sin_port = htons(PUERTO);

    // Enlazar socket
    if (bind(servidor_fd, (struct sockaddr *)&direccion, sizeof(direccion)) < 0) {
        perror("Error al enlazar");
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones
    if (listen(servidor_fd, 5) < 0) {
        perror("Error al escuchar");
        exit(EXIT_FAILURE);
    }

    printf("Servidor multihilo escuchando en el puerto %d...\n", PUERTO);

    while (1) {
        int cliente_fd;
        struct sockaddr_in cliente_dir;
        socklen_t addrlen = sizeof(cliente_dir);

        // Aceptar nueva conexión
        if ((cliente_fd = accept(servidor_fd, (struct sockaddr *)&cliente_dir, &addrlen)) < 0) {
            perror("Error al aceptar conexión");
            continue;  // Continuar esperando conexiones
        }

        // Crear estructura para pasar datos al hilo
        datos_cliente_t *datos = malloc(sizeof(datos_cliente_t));
        datos->cliente_fd = cliente_fd;
        datos->direccion = cliente_dir;

        // Crear hilo para manejar al cliente
        pthread_t hilo;
        if (pthread_create(&hilo, NULL, manejar_cliente, (void *)datos) != 0) {
            perror("Error al crear hilo");
            close(cliente_fd);
            free(datos);
        } else {
            pthread_detach(hilo);  // El hilo se libera automáticamente al terminar
        }
    }
    close(servidor_fd);
    return 0;
}

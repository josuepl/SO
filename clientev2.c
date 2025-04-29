#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PUERTO 8080
#define TAM_BUFFER 1024

int main() {
    int servidor_fd, cliente_fd;
    struct sockaddr_in direccion;
    char buffer[TAM_BUFFER] = {0};
    char respuesta[TAM_BUFFER] = {0};

    // Crear socket
    if ((servidor_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Error al crear socket");
        exit(EXIT_FAILURE);
    }

    // Configurar dirección
    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = INADDR_ANY;
    direccion.sin_port = htons(PUERTO);

    // Enlazar socket al puerto
    if (bind(servidor_fd, (struct sockaddr *)&direccion, sizeof(direccion)) < 0) {
        perror("Error al enlazar");
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones
    if (listen(servidor_fd, 3) < 0) {
        perror("Error al escuchar");
        exit(EXIT_FAILURE);
    }

    printf("Servidor escuchando en el puerto %d...\n", PUERTO);

    // Aceptar conexión
    int addrlen = sizeof(direccion);
    if ((cliente_fd = accept(servidor_fd, (struct sockaddr *)&direccion, (socklen_t*)&addrlen)) < 0) {
        perror("Error al aceptar conexión");
        exit(EXIT_FAILURE);
    }

    // Leer mensaje del cliente
    read(cliente_fd, buffer, TAM_BUFFER);
    printf("Mensaje recibido: %s\n", buffer);

    // Preparar respuesta
    snprintf(respuesta, TAM_BUFFER, "¡Hola, %s!", buffer);

    // Enviar respuesta al cliente
    send(cliente_fd, respuesta, strlen(respuesta), 0);
    printf("Respuesta enviada: %s\n", respuesta);

    // Cerrar conexiones
    close(cliente_fd);
    close(servidor_fd);

    return 0;
}

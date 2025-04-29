#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVIDOR_IP "127.0.0.1"
#define PUERTO 8080
#define TAM_BUFFER 1024

int main() {
    int cliente_fd;
    struct sockaddr_in direccion;
    char buffer[TAM_BUFFER] = {0};
    char nombre[50];

    // Crear socket
    if ((cliente_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Error al crear socket");
        exit(EXIT_FAILURE);
    }

    // Configurar dirección del servidor
    direccion.sin_family = AF_INET;
    direccion.sin_port = htons(PUERTO);

    // Convertir dirección IP a binario
    if (inet_pton(AF_INET, SERVIDOR_IP, &direccion.sin_addr) <= 0) {
        perror("Dirección inválida");
        exit(EXIT_FAILURE);
    }

    // Conectar al servidor
    if (connect(cliente_fd, (struct sockaddr *)&direccion, sizeof(direccion)) < 0) {
        perror("Conexión fallida");
        exit(EXIT_FAILURE);
    }

    printf("Ingresa tu nombre: ");
    fgets(nombre, 50, stdin);
    nombre[strcspn(nombre, "\n")] = '\0';  // Eliminar salto de línea

    // Enviar nombre al servidor
    send(cliente_fd, nombre, strlen(nombre), 0);
    printf("Nombre enviado: %s\n", nombre);

    // Recibir respuesta del servidor
    read(cliente_fd, buffer, TAM_BUFFER);
    printf("Respuesta del servidor: %s\n", buffer);

    // Cerrar socket
    close(cliente_fd);

    return 0;
}

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

using namespace std;

// Puerto que el servidor va a escuchar
#define PORT 8080 
#define MAX_BUFFER 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[MAX_BUFFER] = {0};
    
    // 1. Crear el file descriptor (identificador) del socket (AF_INET = IPv4, SOCK_STREAM = TCP)
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Fallo al crear el socket");
        return 1;
    }

    // Configuración de la estructura de la dirección del servidor
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Escuchar en cualquier interfaz disponible
    address.sin_port = htons(PORT);
    
    // 2. Vincular el socket a la dirección y puerto
    if (::bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Fallo al vincular (bind)");
        return 1;
    }
    
    // 3. Poner el socket en modo "escucha" (listen)
    if (listen(server_fd, 3) < 0) { // 3 es el tamaño de la cola de conexiones
        perror("Fallo al escuchar (listen)");
        return 1;
    }
    
    cout << "Servidor TCP esperando conexiones en el puerto " << PORT << "..." << endl;
    
    // 4. Aceptar la primera conexión entrante (se bloquea hasta que hay una)
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Fallo al aceptar (accept)");
        return 1;
    }
    
    cout << "Conexión aceptada." << endl;

    // 5. Leer los datos enviados por el cliente
    ssize_t valread = read(new_socket, buffer, MAX_BUFFER);
    cout << "Mensaje del cliente: " << buffer << endl;
    
    // 6. Enviar una respuesta
    const char *hello = "Hola desde el servidor TCP";
    send(new_socket, hello, strlen(hello), 0);
    cout << "Mensaje de respuesta enviado." << endl;
    
    // 7. Cerrar los sockets
    close(new_socket);
    close(server_fd);
    
    return 0;
}
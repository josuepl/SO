#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

// Dirección IP y puerto del servidor
#define SERVER_IP "127.0.0.1" // localhost
#define PORT 8080
#define MAX_BUFFER 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[MAX_BUFFER] = {0};
    
    // 1. Crear el file descriptor del socket (AF_INET = IPv4, SOCK_STREAM = TCP)
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Fallo al crear el socket");
        return 1;
    }

    // Configuración de la dirección del servidor
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Convertir dirección IPv4 de texto a binario
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        perror("Dirección IP inválida o no soportada");
        return 1;
    }
    
    // 2. Conectar el socket al servidor
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Fallo de conexión");
        return 1;
    }
    
    // 3. Enviar un mensaje
    const char *message = "Hola servidor, soy el cliente TCP";
    send(sock, message, strlen(message), 0);
    cout << "Mensaje enviado al servidor." << endl;
    
    // 4. Leer la respuesta del servidor
    ssize_t valread = read(sock, buffer, MAX_BUFFER);
    cout << "Respuesta del servidor: " << buffer << endl;
    
    // 5. Cerrar el socket
    close(sock);
    
    return 0;
}
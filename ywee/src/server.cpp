#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

int main() {
    // Create a socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Set socket options
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8080);

    // Bind the socket to the specified port and address
    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Listen for incoming connections
    listen(server_socket, 5);

    while (true) {
        // Accept a client request
        struct sockaddr_in client_addr;
        socklen_t client_addr_size = sizeof(client_addr);
        int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_size);

        // Read in client request
        char request[1024];
        read(client_socket, request, sizeof(request)-1);
        cout << "Client Request: " << request << endl;

        // Send response
        char response[] = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body>Hello World</body></html> ";
        write(client_socket, response, sizeof(response));

        // Close the socket
        close(client_socket);
    }

    // Close the server socket
    close(server_socket);

    return 0;
}
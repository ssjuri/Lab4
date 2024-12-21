#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_request(int client_fd) {
    char buffer[BUFFER_SIZE];
    read(client_fd, buffer, BUFFER_SIZE);
    printf("Request:\n%s\n", buffer);

    if (strstr(buffer, "GET / ")) {
        char response[] = 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n\r\n"
            "<html><body><h1>Welcome to my WebServer</h1></body></html>";
        write(client_fd, response, sizeof(response) - 1);
    } else if (strstr(buffer, "POST / ")) {
        char response[] = 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n\r\n"
            "<html><body><h1>POST Request Received</h1></body></html>";
        write(client_fd, response, sizeof(response) - 1);
    }

    close(client_fd);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 10);

    printf("Web server started on port %d\n", PORT);

    while (1) {
        int addrlen = sizeof(address);
        client_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        handle_request(client_fd);
    }

    return 0;
}

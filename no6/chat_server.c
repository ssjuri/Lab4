#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd, max_fd, activity;
    int client_sockets[MAX_CLIENTS] = {0};
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE];
    fd_set readfds;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, MAX_CLIENTS);

    printf("Chat server started on port %d\n", PORT);

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);
        max_fd = server_fd;

        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (client_sockets[i] > 0) FD_SET(client_sockets[i], &readfds);
            if (client_sockets[i] > max_fd) max_fd = client_sockets[i];
        }

        activity = select(max_fd + 1, &readfds, NULL, NULL, NULL);

        if (FD_ISSET(server_fd, &readfds)) {
            int addrlen = sizeof(address);
            client_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
            printf("New client connected\n");

            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (client_sockets[i] == 0) {
                    client_sockets[i] = client_fd;
                    break;
                }
            }
        }

        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (FD_ISSET(client_sockets[i], &readfds)) {
                int valread = read(client_sockets[i], buffer, BUFFER_SIZE);
                if (valread == 0) {
                    close(client_sockets[i]);
                    client_sockets[i] = 0;
                    printf("Client disconnected\n");
                } else {
                    buffer[valread] = '\0';
                    printf("Received: %s\n", buffer);
                    for (int j = 0; j < MAX_CLIENTS; j++) {
                        if (client_sockets[j] > 0 && j != i) {
                            send(client_sockets[j], buffer, strlen(buffer), 0);
                        }
                    }
                }
            }
        }
    }
    return 0;
}

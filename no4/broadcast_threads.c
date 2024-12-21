#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_CLIENTS 3

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

char message[256];
int new_message = 0;

void* client_thread(void* arg) {
    int id = *(int*)arg;

    while (1) {
        pthread_mutex_lock(&mutex);

        while (!new_message) {
            pthread_cond_wait(&cond, &mutex);
        }

        printf("Client %d received: %s\n", id, message);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

void* server_thread(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        printf("Enter message to broadcast: ");
        fgets(message, 256, stdin);
        message[strcspn(message, "\n")] = '\0';
        new_message = 1;

        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

int main() {
    pthread_t clients[MAX_CLIENTS], server;
    int ids[MAX_CLIENTS];

    for (int i = 0; i < MAX_CLIENTS; i++) {
        ids[i] = i + 1;
        pthread_create(&clients[i], NULL, client_thread, &ids[i]);
    }

    pthread_create(&server, NULL, server_thread, NULL);

    for (int i = 0; i < MAX_CLIENTS; i++) {
        pthread_join(clients[i], NULL);
    }

    pthread_join(server, NULL);
    return 0;
}

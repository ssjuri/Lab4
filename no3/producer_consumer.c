#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;
int in = 0, out = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;

void* producer(void* arg) {
    int id = *(int*)arg;
    while (1) {
        int item = rand() % 100;
        pthread_mutex_lock(&mutex);

        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&not_full, &mutex);
        }

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;
        printf("Producer %d produced %d\n", id, item);

        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

void* consumer(void* arg) {
    int id = *(int*)arg;
    while (1) {
        pthread_mutex_lock(&mutex);

        while (count == 0) {
            pthread_cond_wait(&not_empty, &mutex);
        }

        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;
        printf("Consumer %d consumed %d\n", id, item);

        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

int main() {
    pthread_t producers[2], consumers[2];
    int ids[2] = {1, 2};

    for (int i = 0; i < 2; i++) {
        pthread_create(&producers[i], NULL, producer, &ids[i]);
        pthread_create(&consumers[i], NULL, consumer, &ids[i]);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }

    return 0;
}

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* print_numbers(void* arg) {
    int* num = (int*)arg;
    for (int i = 0; i < 5; i++) {
        printf("Thread %d: %d\n", *num, i);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[2];
    int ids[2] = {1, 2};

    for (int i = 0; i < 2; i++) {
        if (pthread_create(&threads[i], NULL, print_numbers, &ids[i])) {
            perror("Failed to create thread");
            exit(1);
        }
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads finished.\n");
    return 0;
}

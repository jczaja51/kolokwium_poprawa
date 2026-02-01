#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 10
#define T 3

int numbers[N];
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *worker(void *arg) {
    int id = *(int *)arg;

    for (int i = id; i < N; i += T) {
        pthread_mutex_lock(&mtx);
        printf("[Watek %d] Element[%d] = %d\n", id, i, numbers[i]);
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main(void) {
    pthread_t threads[T];
    int ids[T];

    srand(time(NULL));
    for (int i = 0; i < N; i++)
        numbers[i] = rand() % 100;

    for (int i = 0; i < T; i++) {
        ids[i] = i;
        if (pthread_create(&threads[i], NULL, worker, &ids[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < T; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    pthread_mutex_destroy(&mtx);
    return 0;
}
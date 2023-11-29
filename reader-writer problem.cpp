#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

int data = 0; // Shared resource
int readers_count = 0; // Number of active readers
sem_t mutex, wrt; // Semaphores for mutual exclusion and write access

void *reader(void *arg) {
    int reader_id = *((int *)arg);

    while (1) {
        // Entry section
        sem_wait(&mutex);
        readers_count++;
        if (readers_count == 1) {
            sem_wait(&wrt); // First reader locks the writer out
        }
        sem_post(&mutex);

        // Reading section
        printf("Reader %d reads data: %d\n", reader_id, data);

        // Exit section
        sem_wait(&mutex);
        readers_count--;
        if (readers_count == 0) {
            sem_post(&wrt); // Last reader unlocks the writer
        }
        sem_post(&mutex);

        // Sleep to simulate reading time
        usleep(100000);
    }
}

void *writer(void *arg) {
    int writer_id = *((int *)arg);

    while (1) {
        // Entry section
        sem_wait(&wrt);

        // Writing section
        data++;
        printf("Writer %d writes data: %d\n", writer_id, data);

        // Exit section
        sem_post(&wrt);

        // Sleep to simulate writing time
        usleep(200000);
    }
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; ++i) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; ++i) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Join threads (never reached in this example)
    for (int i = 0; i < NUM_READERS; ++i) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; ++i) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}


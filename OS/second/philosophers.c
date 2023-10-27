#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

#define N 5
#define LEFT (i + N - 1) % N
#define RIGHT (i + 1) % N

typedef struct {
    sem_t forks[N];
    sem_t mutex;
} SharedData;

void philosopher(int i, SharedData* data) {
    while (1) {
        printf("Philosopher %d is thinking.\n", i);

        // Wait for forks
        sem_wait(&data->mutex);
        sem_wait(&data->forks[LEFT]);
        sem_wait(&data->forks[RIGHT]);
        sem_post(&data->mutex);

        // Eat
        printf("Philosopher %d is eating.\n", i);
        usleep(1000000);

        // Put down forks
        sem_post(&data->forks[LEFT]);
        sem_post(&data->forks[RIGHT]);
    }
}

int main() {
    int i;
    int shmid;
    SharedData* data;

    // Create shared memory segment
    shmid = shmget(IPC_PRIVATE, sizeof(SharedData), 0666 | IPC_CREAT);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach shared memory
    data = (SharedData*)shmat(shmid, NULL, 0);
    if (data == (SharedData*)-1) {
        perror("shmat");
        exit(1);
    }

    // Initialize semaphores
    sem_init(&data->mutex, 1, 1);
    for (i = 0; i < N; i++) {
        sem_init(&data->forks[i], 1, 1);
    }

    // Create philosopher processes
    for (i = 0; i < N; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        }
        if (pid == 0) {
            philosopher(i, data);
            exit(0);
        }
    }

    // Wait for child processes to finish
    for (i = 0; i < N; i++) {
        wait(NULL);
    }

    // Clean up and detach shared memory
    for (i = 0; i < N; i++) {
        sem_destroy(&data->forks[i]);
    }
    sem_destroy(&data->mutex);
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

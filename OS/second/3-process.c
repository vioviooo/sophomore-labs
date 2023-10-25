#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>

#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS];

void dine(int id) {
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    printf("Philosopher %d is thinking...\n", id);

    sleep(2);

    // philosopher picks up forks
    sem_wait(&forks[left_fork]);
    sem_wait(&forks[right_fork]);

    // philosopher now has both forks => can start eating
    printf("Philosopher %d is eating.\n", id);

    sleep(2);

    // philosopher puts down the forks
    sem_post(&forks[left_fork]);
    sem_post(&forks[right_fork]);

    printf("Philosopher %d has finished eating.\n", id);
}

int main(void) {
    pid_t child_pid;

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 1, 1); // Initialize all forks to 1 (unlocked)
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        child_pid = fork();
        if (child_pid == 0) {
            dine(i); // <- child process
            exit(0);
        }
    }

    // wait for all child processes to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        wait(NULL);
    }

    printf("~All philpsophers dined successfully!\n");

    return 0;
}

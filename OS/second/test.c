#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

enum status_codes {
    MUTEX_FAILED = -1
};

#define NUM_PHILOSOPHERS 5
#define NUM_FORKS 5

pthread_t philosopher[NUM_PHILOSOPHERS + 1];
pthread_mutex_t cutlery[NUM_FORKS + 1];

void dine(int n) {
    // no action
    printf("\nPhilosopher %d is thinking ", n);

    // philosopher picks up the left fork = wait
    pthread_mutex_lock(&cutlery[n]);

    // philosopher picks up the right fork = wait
    pthread_mutex_lock(&cutlery[(n + 1) % NUM_FORKS]);

    // philosopher now has both forks => can start eating
    printf("\nPhilosopher %d is eating ", n);

    sleep(2);

    // philosopher puts down the first fork = signal
    printf("\nPhilosopher %d puts down 1st fork ", n);
    pthread_mutex_unlock(&cutlery[n]);

    // philosopher puts down the second fork = signal
    printf("\nPhilosopher %d puts down 2nd fork ", n);
    pthread_mutex_unlock(&cutlery[(n + 1) % NUM_FORKS]);

    // philosopher dined successfully!
    printf("\nPhilosopher %d Finished eating ", n);
} 

int main() {
    // Define counter var i and status_message
    int status_message;
    void *msg;

    // Initialise the semaphore array
    for (int i = 1; i <= NUM_FORKS; i++) {
        status_message = pthread_mutex_init(&cutlery[i], NULL);
        // Check if the mutex is initialised successfully
        if (status_message == -1) {
            printf("\n Mutex initialization failed");
            exit(1);
        }
    }

    // Run the philosopher Threads using *dine() function
    for (int i = 1; i <= NUM_PHILOSOPHERS; i++) {
        status_message = pthread_create(&philosopher[i], NULL, (void*)dine, (int*)i);
        if (status_message != 0) {
            printf("\n Thread creation error \n");
            exit(1);
        }
    }

    // Wait for all philosophers threads to complete executing (finish dining) before closing the program
    for (int i = 1; i <= NUM_PHILOSOPHERS; i++) {
        status_message = pthread_join(philosopher[i], &msg);
        if (status_message != 0) {
            printf("\n Thread join failed \n");
            exit(1);
        }
    }

    // Destroy the FORK Mutex array
    for (int i = 1; i <= NUM_FORKS; i++) {
        status_message = pthread_mutex_destroy(&cutlery[i]);
        if (status_message != 0) {
            printf("\n Mutex Destroyed \n");
            exit(1);
        }
    }

    return 0;
}

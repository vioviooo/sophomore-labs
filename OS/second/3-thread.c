#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define NUM_PHILOSOPHERS 5
#define NUM_FORKS 5

pthread_t philosopher[NUM_PHILOSOPHERS + 1];
pthread_mutex_t forks[NUM_FORKS + 1]; // <- семафоры

void dine(int id) {
    int right_fork = (id + 1) % NUM_FORKS;
    int left_fork = id;

    printf("Philosopher %d is thinking...\n", id);

    printf("Philosopher %d takes 1st fork \n", id);
    pthread_mutex_lock(&forks[left_fork]);

    printf("Philosopher %d takes 2nd fork\n", id);
    pthread_mutex_lock(&forks[right_fork]);

    // philosopher now has both forks => can start eating
    printf("Philosopher %d is eating...\n", id);

    sleep(2);

    // philosopher puts down the first fork 
    printf("Philosopher %d puts down 1st fork\n", id);
    pthread_mutex_unlock(&forks[left_fork]);

    // philosopher puts down the second fork 
    printf("Philosopher %d puts down 2nd fork\n", id);
    pthread_mutex_unlock(&forks[right_fork]);

    // philosopher dined successfully!
    printf("Philosopher %d has finished eating\n", id);
} 

/* прототип
void philosopher_dine {
    while (true) {
        // Section where the philosopher is using chopstick
        wait(use_resource[x]);  
        wait(use_resource[(x + 1) % 5]); 

        // Section where the philosopher is thinking
        signal(free_resource[x]);  
        signal(free_resource[(x + 1) % 5]);  
    }  
}
*/

int main(void) {

    // initialize mutex array
    for (int i = 1; i <= NUM_FORKS; i++) {
        int status = pthread_mutex_init(&forks[i], NULL); // в нем большие отрицательные числа
        // Check if the mutex is initialised successfully
        if (status == -1) {
            perror("Mutex initialization failed.\n");
            exit(1);
        }
    }

    // run the philosopher threads using dine function
    for (int i = 1; i <= NUM_PHILOSOPHERS; i++) {
        // int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
        int status = pthread_create(&philosopher[i], NULL, (void*)dine, (void*)(intptr_t)i);
        if (status != 0) {
            perror("Thread creation failed.\n");
            exit(1);
        }
    }

    // wait for all philosophers threads to execute (finish dining) before finishing the program
    for (int i = 1; i<= NUM_PHILOSOPHERS; i++) {
        void* message;
        // int pthread_join(pthread_t thread, void **status);
        int status = pthread_join(philosopher[i], &message);
        if (status != 0) {
            perror("Thread join failed.\n");
            exit(1);
        }
    }

    // destroy mutex array
    for (int i = 1; i <= NUM_FORKS; i++) {
        int status = pthread_mutex_destroy(&forks[i]);
        if (status != 0) {
            perror("Mutex destruction failed.\n");
            exit(1);
        }
    }

    printf("~All philpsophers dined successfully!\n");

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>


#define N 5
#define LEFT (i + N - 1) % N
#define RIGHT (i + 1) % N

// union semun {
//     int val;
//     struct semid_ds *buf;
//     unsigned short *array;
// };

void philosopher(int i, int semid) {
    struct sembuf up[2], down[2];
    
    up[0].sem_num = i;
    up[0].sem_op = 1;
    up[0].sem_flg = 0;
    
    down[0].sem_num = i;
    down[0].sem_op = -1;
    down[0].sem_flg = 0;

    up[1].sem_num = LEFT;
    up[1].sem_op = 1;
    up[1].sem_flg = 0;

    down[1].sem_num = RIGHT;
    down[1].sem_op = -1;
    down[1].sem_flg = 0;
    
    while (1) {
        printf("Philosopher %d is thinking.\n", i);

        // Wait for forks
        semop(semid, down, 2);

        // Eat
        printf("Philosopher %d is eating.\n", i);
        usleep(1000000);

        // Put down forks
        semop(semid, up, 2);
    }
}

int main() {
    int semid;
    
    // Create semaphore set
    semid = semget(IPC_PRIVATE, N, 0666 | IPC_CREAT); // чекнуть
    if (semid < 0) {
        perror("semget");
        exit(1);
    }
    
    union semun semopts;
    semopts.val = 1; // Initialize all semaphores to 1
    for (int i = 0; i < N; i++) {
        if (semctl(semid, i, SETVAL, semopts) == -1) {
            perror("semctl");
            exit(1);
        }
    }

    // Create philosopher processes
    for (int i = 0; i < N; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        }
        if (pid == 0) {
            philosopher(i, semid);
            exit(0);
        }
    }

    // Wait for child processes to finish
    for (int i = 0; i < N; i++) {
        wait(NULL);
    }

    // Clean up and remove the semaphore set
    semctl(semid, 0, IPC_RMID);
    
    return 0;
}

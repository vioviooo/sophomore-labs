#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

typedef long long ll;

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

enum status_codes {
    OK = 1,
    INVALID_INPUT = -1,
    NO_MEMORY = -2,
    INVALID = -3,
    OVERFLOW_ = -4
};

void print_scs(int choice) {
    switch(choice) {
        case 2:
            printf("Invalid input.\n");
            break;
        case 1:
            printf("Project finished successfully\n");
            break;
        case -1:
            printf("No memory left.\n");
            break;
        case -2: 
            printf("Invalid something.\n");
            break;
        case -3:
            printf("Overflow!\n");
            break;
        default:
            break;
    }
}

int main() {

    // идентификатор группы вызывающего процесса
    // The getpgid() function shall return the process group ID of the process whose process ID is equal to pid.
    printf("PID of the current process is: %d\n", getpgid(0));

    // эффективный идентификатор группы владельца
    printf("Effective PID of the user group is: %d\n", getegid());

    // эффективный идентификатор владельца 
    printf("Effective PID of the user is: %d\n", geteuid());

    // реальный идентификатор группы владельца
    printf("Real PID of the user group is: %d\n", getgid());

    // реальный идентификатор владельца 
    printf("Real PID of the user is: %d\n", getuid());

    // идентификатор текущего процесса
    printf("PID of the current process is: %d\n", getpid());
    
    // идентификатор родительского процесса
    printf("PPID of the parent process: %d\n", getppid());

    return 0;
}
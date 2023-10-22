#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>
#include <unistd.h>

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

/////////////////////// validations ///////////////////////////

////////////////////main functions////////////////////////

int main() {

    int pid;
    pid = fork();

    printf("%d \n", pid);

    return 0;
}
/*
The operating system is using a unique id for every process to keep track of all processes. And for that, fork() doesn’t take any parameter and return an int value as following:

Zero: if it is the child process (the process created).
Positive value: if it is the parent process.
Negative value: if an error occurred.
*/
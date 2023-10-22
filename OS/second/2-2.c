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

    fork(); 
    printf("Hi\n"); 

    fork(); 
    printf("Hi\n");

    return 0;
}


/*
fork() — системный вызов в Unix-подобных операционных системах, создающий новый процесс (потомок), который является 
практически полной копией процесса-родителя, выполняющего этот вызов.
При вызове fork() порождается новый процесс (процесс-потомок), который почти идентичен порождающему процессу-родителю. 
При вызове fork() возникают два полностью идентичных процесса. Весь код после fork() выполняется дважды, как в процессе-потомке,
так и в процессе-родителе.
*/
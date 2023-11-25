#ifndef MAIN_H
#define MAIN_H
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ARRAY_NAME 1
#define MAX_FILENAME 256
#define MAX_COMMAND_LENGTH 300
#define LETTERS_COUNT 26

enum status_codes { OK = 1, ERROR = -2, INVALID_INPUT = 2, NO_MEMORY = -1, OVERFLOW_ = -3, UNDEFINED = -4 };

inline void print_scs(int choice) {
    switch (choice) {
        case INVALID_INPUT:
            printf("\nERROR: INVALID INPUT\n");
            break;
        case OK:
            printf("\nProject finished successfully!\n");
            break;
        case NO_MEMORY:
            printf("\nERROR: NO MEMORY\n");
            break;
        case OVERFLOW_:
            printf("\nERROR: OVERFLOW\n");
            break;
        case UNDEFINED:
            printf("\nError! What you're trying to calculate IS UNDEFINED or uses complex numbers.\n");
            break;
        default:
            break;
    }
}

typedef struct {
    int size;
    int maxInd;
    int maxVal;
    int minVal;
    int minInd;
    int mostFrequent;
    double average;
    int maxDeviation;
} Stats;

int loadArr(int array[], int* size, const char* filename);
int saveArr(const int array[], int size, const char* filename);
int randomArr(int array[], int size, int lb, int rb);
int concatArrs(int dest[], int* destSize, const int src[], int srcSize);
int freeArray(int array[], int* size);
int removeElems(int array[], int* size, int startIdx, int numElements);
int copyElems(const int src[], int srcSize, int dest[], int* destSize, int startIdx, int endIdx);
void shuffleArr(int array[], int size);
Stats calcStats(const int array[], int size);

int compareAsc(const void* a, const void* b);
int compareDesc(const void* a, const void* b);
int compareShuffle();

void printAll(const int array[], int size);
int printRange(const int array[], int size, int start, int end);
void printElement(const int array[], int size, int index);

#endif
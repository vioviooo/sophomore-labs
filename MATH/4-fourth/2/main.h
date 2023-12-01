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
int shuffleArr(int array[], int size);
Stats calcStats(const int array[], int size);

int compareAsc(const void* a, const void* b);
int compareDesc(const void* a, const void* b);
int compareShuffle();

int printAll(const int array[], int size);
int printRange(const int array[], int size, int start, int end);
int printElement(const int array[], int size, int index);

#endif
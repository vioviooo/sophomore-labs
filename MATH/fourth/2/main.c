#include "main.h"

int main() {
    int arrays[LETTERS_COUNT][BUFSIZ];
    int arraySizes[LETTERS_COUNT] = {0};

    char command[MAX_COMMAND_LENGTH];
    char filename[MAX_FILENAME];
    char arr1, arr2;
    int count, lb, rb, pos;

    // TODO: run tests

    while (true) {
        printf("Enter command: ");
        fgets(command, MAX_COMMAND_LENGTH, stdin);
        // TODO:check return values from functions and print errors if necessary
        // FIXME: sscanf doesn't react when ; is absent
        if (sscanf(command, "load %c, %255[^;];\n", &arr1, filename) == 2 && isalpha(arr1)) {
            printf("HEERRE:%s\n", filename);
            loadArr(arrays[toupper(arr1) - 'A'], &arraySizes[toupper(arr1) - 'A'], filename);
            printf("Array %c loaded from %s\n", arr1, filename);
        } else if (sscanf(command, "save %c, %19[^;];", &arr1, filename) == 2 && isalpha(arr1)) {
            saveArr(arrays[toupper(arr1) - 'A'], arraySizes[toupper(arr1) - 'A'], filename);
            printf("Array %c saved to %s\n", arr1, filename);
        } else if (sscanf(command, "rand %c, %d, %d, %d;", &arr1, &count, &lb, &rb) == 4 && isalpha(arr1)) {
            randomArr(arrays[toupper(arr1) - 'A'], count, lb, rb);
            arraySizes[toupper(arr1) - 'A'] = count;
            printf("Array %c filled with %d random elements between %d and %d\n", arr1, count, lb, rb);
        } else if (sscanf(command, "concat %c, %c;", &arr1, &arr2) == 2 && isalpha(arr1) && isalpha(arr2)) {
            concatArrs(arrays[toupper(arr1) - 'A'], &arraySizes[toupper(arr1) - 'A'], arrays[arr2 - 'A'],
                       arraySizes[arr2 - 'A']);
            printf("Arrays %c and %c concatenated\n", arr1, arr2);
        } else if (sscanf(command, "free %c;", &arr1) == 1 && isalpha(arr1)) {
            freeArray(arrays[toupper(arr1) - 'A'], &arraySizes[toupper(arr1) - 'A']);
            printf("Array %c freed\n", arr1);
        } else if (sscanf(command, "remove %c, %d, %d;", &arr1, &lb, &rb) == 3 && isalpha(arr1)) {
            removeElems(arrays[toupper(arr1) - 'A'], &arraySizes[toupper(arr1) - 'A'], lb, rb);
            printf("%d elements removed from array %c starting from index %d\n", rb, arr1, lb);
        } else if (sscanf(command, "copy %c, %d, %d, %c;", &arr1, &lb, &rb, &arr2) == 4 && isalpha(arr1)) {
            copyElems(arrays[toupper(arr1) - 'A'], arraySizes[toupper(arr1) - 'A'], arrays[arr2 - 'A'],
                      &arraySizes[arr2 - 'A'], lb, rb);
            printf("Elements copied from array %c to %c\n", arr1, arr2);
        } else if (sscanf(command, "sort %c+;", &arr1) == 1 && isalpha(arr1)) {
            qsort(arrays[toupper(arr1) - 'A'], arraySizes[toupper(arr1) - 'A'], sizeof(int), compareAsc);
            // TODO: change output format
            printf("Array A sorted in ascending order\n");
        } else if (sscanf(command, "sort %c-;", &arr1) == 1 && isalpha(arr1)) {
            qsort(arrays[toupper(arr1) - 'A'], arraySizes[toupper(arr1) - 'A'], sizeof(int), compareDesc);
            printf("Array A sorted in descending order\n");
        } else if (sscanf(command, "shuffle %c;", &arr1) == 1 && isalpha(arr1)) {
            shuffleArr(arrays[toupper(arr1) - 'A'], arraySizes[toupper(arr1) - 'A']);
            printf("Array A shuffled\n");
        } else if (sscanf(command, "stats %c;", &arr1) == 1 && isalpha(arr1)) {
            Stats stats = calcStats(arrays[toupper(arr1) - 'A'], arraySizes[toupper(arr1) - 'A']);
            printf("Array %c statistics:\n", arr1);
            printf("Size of the array: %d\n", stats.size);
            printf("Max element: %d (index: %d)\n", stats.maxVal, stats.maxInd);
            printf("Min element: %d (index: %d)\n", stats.minVal, stats.minInd);
            printf("Most frequent element: %d\n", stats.mostFrequent);
            printf("Average: %.2f\n", stats.average);
            printf("Max deviation: %d\n", stats.maxDeviation);
            printf("\n");
        } else if (sscanf(command, "print %c, %d, %d;", &arr1, &lb, &rb) == 3 && isalpha(arr1)) {
            printRange(arrays[toupper(arr1) - 'A'], arraySizes[toupper(arr1) - 'A'], lb, rb);
        } else if (sscanf(command, "print %c, %d;", &arr1, &pos) == 2 && isalpha(arr1)) {
            printElement(arrays[toupper(arr1) - 'A'], arraySizes[toupper(arr1) - 'A'], pos);
        } else if (sscanf(command, "print %c, all;", &arr1) == 1 && isalpha(arr1)) {
            printAll(arrays[toupper(arr1) - 'A'], arraySizes[toupper(arr1) - 'A']);
        } else if (strcmp(command, "exit;\n") == 0) {
            break;
        } else {
            printf("Invalid command\n");
        }
    }

    return 0;
}

int compareAsc(const void* a, const void* b) { return (*(int*)a - *(int*)b); }
int compareDesc(const void* a, const void* b) { return (*(int*)b - *(int*)a); }
int compareShuffle() { return rand() % 3 - 1; }

int concatArrs(int dest[], int* destSize, const int src[], int srcSize) {
    for (int i = 0; i < srcSize; i++) {
        dest[*destSize + i] = src[i];
    }
    *destSize += srcSize;

    return OK;
}

void shuffleArr(int array[], int size) {
    srand(time(NULL));
    qsort(array, size, sizeof(int), compareShuffle);
}

int freeArray(int array[], int* size) {
    memset(array, 0, *size * sizeof(int));
    *size = 0;

    return OK;
}

int copyElems(const int src[], int srcSize, int dest[], int* destSize, int startIdx, int endIdx) {
    int copySize = endIdx - startIdx + 1;

    if (startIdx < 0 || startIdx >= srcSize || endIdx < startIdx || endIdx >= srcSize) {
        printf("Invalid copy parameters\n");
        return ERROR;
    }

    for (int i = 0; i < copySize; i++) {
        dest[i] = src[startIdx + i];
    }
    *destSize = copySize;

    return OK;
}

int removeElems(int array[], int* size, int startIdx, int numElements) {
    if (size == 0) {
        return ERROR;
    }

    if (startIdx < 0 || startIdx >= *size || numElements <= 0) {
        return INVALID_INPUT;
    }

    for (int i = startIdx; i < *size - numElements; i++) {
        array[i] = array[i + numElements];
    }

    *size -= numElements;

    return OK;
}

int loadArr(int array[], int* size, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return ERROR;
    }

    // FIXME: SKIP invalid strings in the input file
    // int value;
    // *size = 0;
    // while (fscanf(file, "%s", &value) != EOF && *size < BUFSIZ) {
    //     array[(*size)++] = value;
    // }

    fclose(file);

    return OK;
}

int saveArr(const int array[], int size, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return ERROR;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", array[i]);
    }

    fclose(file);

    return OK;
}

void printElement(const int array[], int size, int index) {
    if (index >= 0 && index < size) {
        printf("Element at position %d: %d\n", index, array[index]);
    } else {
        printf("Invalid index\n");
    }
}

int printRange(const int array[], int size, int start, int end) {
    if (start >= 0 && start < size && end >= start && end < size) {
        for (int i = start; i <= end; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
    } else {
        return INVALID_INPUT;
    }
    return OK;
}

void printAll(const int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int randomArr(int array[], int size, int lb, int rb) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % (rb - lb + 1) + lb;
    }
    return OK;
}

Stats calcStats(const int array[], int size) {
    Stats stats;

    if (size == 0) {
        stats.size = 0;
        stats.maxInd = -1;
        stats.minVal = 0;
        stats.minInd = -1;
        stats.maxVal = 0;
        stats.mostFrequent = 0;
        stats.average = 0.0;
        stats.maxDeviation = 0;
        return stats;
    }

    stats.size = size;
    stats.minVal = array[0];
    stats.minInd = 0;
    stats.maxInd = 0;
    stats.maxVal = array[0];
    stats.mostFrequent = array[0];
    stats.average = (double)array[0];
    stats.maxDeviation = 0;

    int sum = array[0], deviation, maxCount = 1, currCount = 1, prev = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] > stats.maxVal) {
            stats.maxVal = array[i];
            stats.maxInd = i;
        } else if (array[i] < stats.minVal) {
            stats.minVal = array[i];
            stats.minInd = i;
        }
        sum += array[i];

        deviation = abs(array[i] - sum / (i + 1));

        if (deviation > stats.maxDeviation) {
            stats.maxDeviation = deviation;
        }

        if (array[i] == array[i - 1]) {
            currCount++;
        } else {
            currCount = 1;
        }

        if (currCount > maxCount || (currCount == maxCount && array[i] > prev)) {
            maxCount = currCount;
            stats.mostFrequent = array[i];
            prev = array[i];
        }

        stats.average = (double)sum / (i + 1);
    }

    return stats;
}
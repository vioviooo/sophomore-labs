#include "main.h"

enum status_codes {
    OK = 1,
    ERROR = -2,
    INVALID_INPUT = 2,
    NO_MEMORY = -1,
    OVERFLOW_ = -3,
    INVALID_INPUT_FILE = -4,
    EMPTY_ARR = -5
};

void print_scs(int choice) {
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
        case INVALID_INPUT_FILE:
            printf("\nERROR: INVALID FILE INPUT\n");
            break;
        case EMPTY_ARR:
            printf("\nNOTICE: EMPTY ARRAY\n");
            break;
        default:
            break;
    }
}

int compareAsc(const void* a, const void* b) { return (*(int const*)a - *(int const*)b); }
int compareDesc(const void* a, const void* b) { return (*(int const*)b - *(int const*)a); }
int compareShuffle() { return rand() % 3 - 1; }

int concatArrs(int dest[], int* destSize, const int src[], int srcSize) {
    if (*destSize + srcSize >= BUFSIZ) {
        return OVERFLOW_;
    }
    for (int i = 0; i < srcSize; i++) {
        dest[*destSize + i] = src[i];
    }
    *destSize += srcSize;

    if (*destSize == 0) {
        return EMPTY_ARR;
    }

    return OK;
}

int shuffleArr(int array[], int size) {
    if (size == 0) {
        return EMPTY_ARR;
    }
    srand(time(NULL));
    qsort(array, size, sizeof(int), compareShuffle);
    return OK;
}

int freeArray(int array[], int* size) {
    memset(array, 0, *size * sizeof(int));
    *size = 0;

    return OK;
}

int copyElems(const int src[], int srcSize, int dest[], int* destSize, int beginInd, int endIdx) {
    if (srcSize == 0) {
        return EMPTY_ARR;
    }

    int copySize = endIdx - beginInd + 1;

    if (beginInd < 0 || beginInd >= srcSize || endIdx < beginInd || endIdx >= srcSize) {
        printf("Invalid copy parameters\n");
        return ERROR;
    }

    for (int i = 0; i < copySize; i++) {
        dest[i] = src[beginInd + i];
    }
    *destSize = copySize;

    return OK;
}

int removeElems(int array[], int* size, int beginInd, int numElements) {
    if (size == 0) {
        return ERROR;
    }

    if (*size - numElements == 0) {
        return EMPTY_ARR;
    }

    if (beginInd < 0 || beginInd >= *size || numElements <= 0) {
        return INVALID_INPUT;
    }

    for (int i = beginInd; i < *size - numElements; i++) {
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

    *size = 0;
    int res;
    while (*size < BUFSIZ) {
        res = fscanf(file, "%d", &array[*size]);
        if (res == 1) {
            (*size)++;
        } else if (res == 0) {
            fclose(file);
            return INVALID_INPUT_FILE;
        } else {
            fclose(file);
            return ERROR;
        }
    }

    if (fscanf(file, "%d", &res) == 1) {
        return OVERFLOW_;
    }

    fclose(file);

    return OK;
}

int saveArr(const int array[], int size, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return ERROR;
    }

    if (size == 0) {
        return EMPTY_ARR;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", array[i]);
    }

    fclose(file);

    return OK;
}

int printElement(const int array[], int size, int index) {
    if (size == 0) {
        return EMPTY_ARR;
    }
    if (index >= 0 && index < size) {
        printf("Element at position %d: %d\n", index, array[index]);
    } else {
        return INVALID_INPUT;
    }
    return OK;
}

int printRange(const int array[], int size, int start, int end) {
    if (size == 0) {
        return EMPTY_ARR;
    }
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

int printAll(const int array[], int size) {
    if (size == 0) {
        return EMPTY_ARR;
    }
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    return OK;
}

int randomArr(int array[], int size, int lb, int rb) {
    if (size == 0) {
        return EMPTY_ARR;
    }
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
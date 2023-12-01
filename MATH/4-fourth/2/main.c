#include "functions.c"

int main() {
    int arrays[LETTERS_COUNT][BUFSIZ];
    int arraySizes[LETTERS_COUNT] = {0};

    char command[MAX_COMMAND_LENGTH];
    char filename[MAX_FILENAME];
    char arr1, arr2;
    int count, lb, rb, pos;

    while (true) {
        printf("Enter command: ");
        fgets(command, MAX_COMMAND_LENGTH, stdin);
        // TODO:check return values from functions and print errors if necessary
        int status = 0;
        if (sscanf(command, "load %c, %255[^;];\n", &arr1, filename) == 2 && isalpha(arr1) && strchr(command, ';')) {
            if ((status = loadArr(arrays[toupper(arr1) - 'A'], &arraySizes[toupper(arr1) - 'A'], filename)) != OK) {
                print_scs(status);
            } else
                printf("Array %c loaded from %s\n", arr1, filename);
        } else if (sscanf(command, "save %c, %19[^;];", &arr1, filename) == 2 && isalpha(arr1) && strchr(command, ';')) {
            saveArr(arrays[toupper(arr1) - 'A'], arraySizes[toupper(arr1) - 'A'], filename);
            printf("Array %c saved to %s\n", arr1, filename);
        } else if (sscanf(command, "rand %c, %d, %d, %d;", &arr1, &count, &lb, &rb) == 4 && isalpha(arr1) && strchr(command, ';')) {
            randomArr(arrays[toupper(arr1) - 'A'], count, lb, rb);
            arraySizes[toupper(arr1) - 'A'] = count;
            printf("Array %c filled with %d random elements between %d and %d\n", arr1, count, lb, rb);
        } else if (sscanf(command, "concat %c, %c;", &arr1, &arr2) == 2 && isalpha(arr1) && isalpha(arr2) && strchr(command, ';')) {
            concatArrs(arrays[toupper(arr1) - 'A'], &arraySizes[toupper(arr1) - 'A'], arrays[arr2 - 'A'],
                       arraySizes[arr2 - 'A']);
            printf("Arrays %c and %c concatenated\n", arr1, arr2);
        } else if (sscanf(command, "free %c;", &arr1) == 1 && isalpha(arr1) && strchr(command, ';') && strchr(command, ';')) {
            freeArray(arrays[toupper(arr1) - 'A'], &arraySizes[toupper(arr1) - 'A']);
            printf("Array %c freed\n", arr1);
        } else if (sscanf(command, "remove %c, %d, %d;", &arr1, &lb, &rb) == 3 && isalpha(arr1) && strchr(command, ';')) {
            removeElems(arrays[toupper(arr1) - 'A'], &arraySizes[toupper(arr1) - 'A'], lb, rb);
            printf("%d elements removed from array %c starting from index %d\n", rb, arr1, lb);
        } else if (sscanf(command, "copy %c, %d, %d, %c;", &arr1, &lb, &rb, &arr2) == 4 && isalpha(arr1) && strchr(command, ';')) {
            copyElems(arrays[toupper(arr1) - 'A'], arraySizes[toupper(arr1) - 'A'], arrays[arr2 - 'A'],
                      &arraySizes[arr2 - 'A'], lb, rb);
            printf("Elements copied from array %c to %c\n", arr1, arr2);
        } else if (sscanf(command, "sort %c+;", &arr1) == 1 && isalpha(arr1) && strchr(command, ';')) {
            if (arraySizes[toupper(arr1) - 'A'] == 0) {
                print_scs(EMPTY_ARR);
            }
            else {
                qsort(arrays[toupper(arr1) - 'A'], arraySizes[toupper(arr1) - 'A'], sizeof(int), compareAsc);
                printf("Array %c sorted in ascending order\n", arr1);
            }
        } else if (sscanf(command, "sort %c-;", &arr1) == 1 && isalpha(arr1) && strchr(command, ';')) {
            if (arraySizes[toupper(arr1) - 'A'] == 0) {
                print_scs(EMPTY_ARR);
            }
            else {
                qsort(arrays[toupper(arr1) - 'A'], arraySizes[toupper(arr1) - 'A'], sizeof(int), compareDesc);
                printf("Array %c sorted in descending order\n", arr1);
            }
        } else if (sscanf(command, "shuffle %c;", &arr1) == 1 && isalpha(arr1) && strchr(command, ';')) {
            if ((status = shuffleArr(arrays[toupper(arr1) - 'A'], arraySizes[toupper(arr1) - 'A'])) != OK) {
                print_scs(status);
            } else 
                printf("Array %c shuffled\n", arr1);
        } else if (sscanf(command, "stats %c;", &arr1) == 1 && isalpha(arr1) && strchr(command, ';')) {
            Stats stats = calcStats(arrays[toupper(arr1) - 'A'], arraySizes[toupper(arr1) - 'A']);
            printf("Array %c statistics:\n", arr1);
            printf("Size of the array: %d\n", stats.size);
            printf("Max element: %d (index: %d)\n", stats.maxVal, stats.maxInd);
            printf("Min element: %d (index: %d)\n", stats.minVal, stats.minInd);
            printf("Most frequent element: %d\n", stats.mostFrequent);
            printf("Average: %.2f\n", stats.average);
            printf("Max deviation: %d\n", stats.maxDeviation);
            printf("\n");
        } else if (sscanf(command, "print %c, %d, %d;", &arr1, &lb, &rb) == 3 && isalpha(arr1) && strchr(command, ';')) {
            if ((status = printRange(arrays[toupper(arr1) - 'A'], arraySizes[toupper(arr1) - 'A'], lb, rb)) != OK) {
                print_scs(status);
            }
        } else if (sscanf(command, "print %c, %d;", &arr1, &pos) == 2 && isalpha(arr1) && strchr(command, ';')) {
            if ((status = printElement(arrays[toupper(arr1) - 'A'], arraySizes[toupper(arr1) - 'A'], pos)) != OK) {
                print_scs(status);
            }
        } else if (sscanf(command, "print %c, all;", &arr1) == 1 && isalpha(arr1) && strchr(command, ';')) {
            if ((status = printAll(arrays[toupper(arr1) - 'A'], arraySizes[toupper(arr1) - 'A'])) != OK) {
                print_scs(status);
            }
        } else if (strcmp(command, "exit;\n") == 0) {
            break;
        } else {
            printf("Invalid command\n");
        }
    }

    return 0;
}
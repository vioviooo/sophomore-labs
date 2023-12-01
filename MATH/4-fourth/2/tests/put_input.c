#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBERS_TO_GENERATE 2000
#define FILENAME "overflow.txt"

int main() {
    srand((unsigned int)time(NULL));

    FILE *file = fopen(FILENAME, "w");

    if (file == NULL) {
        fprintf(stderr, "Unable to open file for writing.\n");
        return 1; // Exit with an error code
    }

    for (int i = 0; i < NUMBERS_TO_GENERATE; ++i) {
        fprintf(file, "%d ", rand() % 200);
    }

    fclose(file);

    printf("Random numbers written to %s\n", FILENAME);

    return 0; // Exit successfully
}

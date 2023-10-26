#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID_INPUT -1

int count_pattern_in_file(const char* pattern, const char* filename) {
    FILE* fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("Failed to open file: %s\n", filename);
        return INVALID_INPUT;
    }

    printf("Occurrences in file %s:\n", filename);

    char* line = NULL;
    size_t len = 0;
    int cnt = 0;
    int line_number = 1;

    while (getline(&line, &len, fptr) != -1) {
        char* position = line;
        while ((position = strstr(position, pattern)) != NULL) {
            printf("Pattern found at line %d, position %ld\n", line_number, position - line + 1);
            position++;
            cnt++;
        }
        line_number++;
    }

    free(line);
    fclose(fptr);

    return cnt;
}

int main() {
    const char* pattern = "HERE";
    const char* filename = "1.txt"; // Replace with your file path

    int result = count_pattern_in_file(pattern, filename);
    if (result != INVALID_INPUT) {
        printf("Total occurrences: %d\n", result);
    }

    return 0;
}

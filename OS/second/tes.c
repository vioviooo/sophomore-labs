#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_FILENAMES 100
#define MAX_FILENAME_LENGTH 256
#define MAX_SEARCH_PATTERN_LENGTH 256

enum status_codes {
    OK = 0,
    INVALID_INPUT = 1,
    FILE_NOT_OPEN = 2,
};

void print_scs(int choice) {
    switch (choice) {
        case INVALID_INPUT:
            printf("Invalid input.\n");
            break;
        case FILE_NOT_OPEN:
            printf("Couldn't open the file.\n");
            break;
        default:
            break;
    }
}

int search_pattern_in_file(const char* pattern, const char* filename, int* cnt) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return FILE_NOT_OPEN;
    }

    char* line = NULL;
    size_t len = 0;
    int line_number = 1;
    int pattern_len = strlen(pattern);
    int found = 0;

    while (getline(&line, &len, file) != -1) {
        if (strstr(line, pattern) != NULL) {
            printf("Found '%s' in %s at line %d\n", pattern, filename, line_number);
            (*cnt) += 1;
            found = 1;
        }
        line_number++;
    }

    free(line);
    fclose(file);

    return (found ? OK : -1);
}

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("Invalid input! Usage: %s <file_with_filenames> <search_pattern>\n", argv[0]);
        return INVALID_INPUT;
    }

    const char* filenames_file = argv[1];
    const char* search_pattern = argv[2];

    FILE* filenames = fopen(filenames_file, "r");
    if (filenames == NULL) {
        perror("Couldn't open the file with filenames");
        return FILE_NOT_OPEN;
    }

    char filename[MAX_FILENAME_LENGTH];
    int child_status, cnt = 0;

    while (fgets(filename, MAX_FILENAME_LENGTH, filenames) != NULL) {

        size_t len = strlen(filename);
        if (len > 0 && filename[len - 1] == '\n') {
            filename[len - 1] = '\0';
        }

        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("fork() failed");
            exit(1);
        } else if (child_pid == 0) {
            int status = search_pattern_in_file(search_pattern, filename, &cnt);
            exit(status);
        }
    }

    // wait for all child processes to complete
    while (wait(&child_status) > 0);

    if (cnt == 0) {
        printf("Pattern not found.\n");
    }

    fclose(filenames);

    return 0;
}

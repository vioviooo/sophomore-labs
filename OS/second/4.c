#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>

typedef long long ll;

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

typedef struct {
    int row;
    int column;
} Data;

enum status_codes {
    OK = 1,
    INVALID_INPUT = 2,
    NO_MEMORY = -5,
    INVALID = -2,
    OVERFLOW_ = -3,
    UNDEFINED = -4,
    WARNING_UNUSED = 3,
    WARNING_SMALL = 4,
    FILE_NOT_OPEN = -1,
    NO = 7
};

void print_scs(int choice) {
    switch(choice) {
        case INVALID_INPUT:
            printf("Invalid input.\n");
            break;
        case OK:
            printf("Project finished successfully\n");
            break;
        case NO_MEMORY:
            printf("No memory left.\n");
            break;
        case INVALID: 
            printf("Invalid something.\n");
            break;
        case OVERFLOW_:
            printf("Overflow!\n");
            break;
        case UNDEFINED:
            printf("Error! What you're trying to calculate IS UNDEFINED or uses complex numbers.\n");
            break;
        case WARNING_UNUSED:
            printf("Warning! Not all input data was used.\n");
            break;
        case WARNING_SMALL:
            printf("Warning! Small values may result in near zero results.\n");
            break;
        case FILE_NOT_OPEN:
            printf("Couldn't open the file.\n");
            break;
        default:
            break;
    }
}

int count_next_line(const char* pattern) {
    int cnt = 0;
    for (int i = 0; pattern[i] != '\0'; i++) {
        if (pattern[i] == '\n') {
            cnt++;
        }
    }
    return cnt;
}

int count_pattern_in_files(const char* pattern, char* filename) {

    FILE* fptr = fopen(filename, "r");

    if (fptr == NULL) {
        return FILE_NOT_OPEN;
    }
    
    char* line = NULL;
    size_t len = 0;
    int cnt_all = 0, cnt = 0;
    int line_number = 1;

    while (getline(&line, &len, fptr) != -1) {
        char* line_ptr = line;
        int line_len = strlen(line);
        int pattern_len = strlen(pattern);

        for (int i = 0; i < line_len; i++) {
            if (line_ptr[i] == pattern[0]) {
                bool match = 1;
                
                for (int j = 1; j < pattern_len && match; j++) {
                    if (i + j >= line_len || line_ptr[i + j] != pattern[j]) {
                        match = 0;
                    }
                }

                if (match) {
                    cnt_all++;
                    cnt++;

                    return OK;
                }
            }
        }
        free(line);
        fclose(fptr);
    }

    return NO;
}

int main(int argc, char* argv[]) {

    const char* filenames_file = argv[1];
    const char* search_pattern = argv[2];

    FILE* filenames = fopen(filenames_file, "r");
    if (filenames == NULL) {
        perror("Couldn't open the file with filenames");
        return FILE_NOT_OPEN;
    }

    char filename[256];
    int child_status;

    while (fgets(filename, 256, filenames) != NULL) {

        size_t len = strlen(filename);
        if (len > 0 && filename[len - 1] == '\n') {
            filename[len - 1] = '\0';
        }

        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("fork() failed");
            exit(1);
        } else if (child_pid == 0) {
            int status = count_pattern_in_files(search_pattern, filename);
            if (status == OK) {
                printf("Found in file %s'n", filename);
            }
            exit(status);
        }
    }

    // Wait for all child processes to complete
    while (wait(&child_status) > 0);

    fclose(filenames);

    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>

enum status_codes {
    OK = 0,
    ERROR = -1,
};

void return_codes(int code) {
    switch (code) {
        case OK:
            printf("Program finished successfully.\n");
            break;
        case ERROR:
            printf("An error occurred.\n");
            break;
    }
}

bool is_txt_file(char *filename) {
    size_t len = strlen(filename);
    
    if (len >= 4 && len <= 255) {
        if (strcmp(filename + len - 4, ".txt") == 0) {
            return true;
        }
    }
    
    return false;
}

////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("Invalid amount of arguments. Usage: %s <input_file-path> <output_file-path> \n", argv[0]);
        return ERROR;
    }

    char* file1 = argv[1];
    char* file2 = argv[2];

    if (!is_txt_file(file1) || !is_txt_file(file2)) {
        printf("Invalid filename.\n");
        return ERROR;
    }

    char input_file[256];
    strcpy(input_file, argv[1]);

    char output_file[256];
    strcpy(output_file, argv[2]);

    FILE* fptr_in = fopen(input_file, "r");

    if (fptr_in == NULL) {
        printf("File couldn't be opened.\n");
        return ERROR;
    }

    FILE* fptr_out = fopen(output_file, "w");

    if (fptr_out == NULL) {
        printf("File couldn't be opened.\n");
        fclose(fptr_in);
        return ERROR;
    }

    char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), fptr_in)) > 0) {
        fwrite(buffer, 1, bytes_read, fptr_out);
    }

    fclose(fptr_in);
    fclose(fptr_out);

    return_codes(OK);
    return OK;
}

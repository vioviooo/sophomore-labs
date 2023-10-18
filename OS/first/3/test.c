#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Invalid amount of arguments. Usage: %s <input_file> <output_file>\n", argv[0]);
        return ERROR;
    }

    char* input_file = argv[1];
    char* output_file = argv[2];

    FILE* fptr_in = fopen(input_file, "r");  // Open for reading
    if (fptr_in == NULL) {
        printf("Input file couldn't be opened.\n");
        return ERROR;
    }

    FILE* fptr_out = fopen(output_file, "w");  // Open for writing
    if (fptr_out == NULL) {
        printf("Output file couldn't be opened.\n");
        fclose(fptr_in);
        return ERROR;
    }

    char buffer[1024];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fptr_in)) > 0) {
        fwrite(buffer, 1, bytesRead, fptr_out);
    }

    fclose(fptr_in);
    fclose(fptr_out);

    return_codes(OK);
    return OK;
}

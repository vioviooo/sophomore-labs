#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>

typedef long long ll;

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

enum status_codes {
    OK = 0,
    NO_MEMORY,
    ERROR = -1
};

////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Invalid amount of arguments. Usage: %s <file-path> \n", argv[0]);
        return 1;
    }

    char data[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};

    char output_file[BUFSIZ];

    strcpy(output_file, argv[1]);

    FILE* ptr_out = fopen(output_file, "wb"); // write binary

    if (ptr_out == NULL) {
        printf("Couldn't open the file.\n");
        return 1;
    }

    int data_size = sizeof(data);

    size_t cnt = fwrite(data, sizeof(char), data_size, ptr_out);

    if (cnt != data_size) {
        printf("Couldn't write to file.");
        return 1;
    }

    fclose(ptr_out);

    char input_file[BUFSIZ];
    strcpy(input_file, argv[1]);

    FILE* ptr_in = fopen(input_file, "rb"); // read binary

    if (ptr_in == NULL) {
        printf("Couldn't open the file.\n");
        return 1;
    }

    char ch;
    while ((ch = fgetc(ptr_in)) != EOF) {
        printf("CHAR: %d \n", ch);
        printf("Size of the internal buffer: %d \n", ptr_in->_blksize); 
        printf("Set of bit flags: %d \n", ptr_in->_flags);
        printf("File descriptor: %d \n", ptr_in->_file);
        printf("Size of line buffer: %d \n", ptr_in->_lbfsize);
        printf("Value of the _ur field: %d \n", ptr_in->_ur);
        printf("Value of the _w field: %d \n", ptr_in->_w);
    }

    fclose(ptr_in);

    ptr_in = fopen(input_file, "rb"); // read binary

    if (fseek(ptr_in, 3, SEEK_SET) != 0) {
        printf("Failed to move file pointer.\n");
        return 1;
    }

    char buf[BUFSIZ];

    size_t cnt_read = fread(buf, 1, 4, ptr_in);

    if (cnt_read != 4) {
        printf("File reading failed.\n");
        return 1;
    }

    for (int i = 0; i < 4; i++) {
        printf("%d ", (int)buf[i]); // Print the bytes in hexadecimal
    }
    printf("\n");

    fclose(ptr_in);

    printf("\n");

    return 0;
}

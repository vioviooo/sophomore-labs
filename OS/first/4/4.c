#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>
#include "my_functions.h"

typedef long long ll;

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

enum status_codes {
    OK = 0,
    ERROR = -1,
    OVERFLOW = -2
};

int xor8(FILE* fptr_in);
int xor32(FILE* fptr_in);
int mask(FILE* fptr_in, int mask);

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("Invalid amount of arguments. Usage: %s  \n", argv[0]);
        return ERROR;
    }

    char* input_file = argv[1];
    char* flag = argv[2];

    FILE* fptr_in = fopen(input_file, "rb");
    if (!fptr_in) {
        printf("Failed to open input file\n");
        return ERROR;
    }

    int res;

    if (strcmp(flag, "xor8") == 0) {
        res = xor8(fptr_in);
        printf("%d \n", res);
    } else if (strcmp(flag, "xor32") == 0) {
        res = xor32(fptr_in);
        printf("%d \n", res);
    } else if (strcmp(flag, "mask") == 0) {
        int mask_hx = 0x37333732;
        res = mask(fptr_in, mask_hx);
        if (res < 0) {
            return OVERFLOW;
        } else 
            printf("%d \n", res);
    } else {
        printf("Invalid flag: %s\n", flag);
        return ERROR;
    }

    fclose(fptr_in);

    return 0;
}

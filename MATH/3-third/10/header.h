#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>
#include <complex.h>

enum status_codes {
    OKAY = 1,
    ERROR = -2,
    INVALID_INPUT = 2,
    INVALID_INPUT_FILE = -6,
    NO_MEMORY = -1,
    OVERFLOW_ = -3,
    UNDEFINED = -4,
    FILE_NOT_OPEN = -5
};

inline void print_scs(int choice) {
    switch(choice) {
        case INVALID_INPUT:
            printf("\nInvalid input.\n");
            break;
        case OKAY:
            printf("\nProject finished successfully!\n");
            break;
        case NO_MEMORY:
            printf("\nNo memory left.\n");
            break;
        case OVERFLOW_:
            printf("\nOverflow!\n");
            break;
        case UNDEFINED:
            printf("\nError! What you're trying to calculate IS UNDEFINED or uses complex numbers.\n");
            break;
        case FILE_NOT_OPEN:
            printf("\nCan't open file.\n");
            break;
        case INVALID_INPUT_FILE:
            printf("\nInvalid format of data in file.\n");
            break;
        default:
            break;
    }
}

#endif
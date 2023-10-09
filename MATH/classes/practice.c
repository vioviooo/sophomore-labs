#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

typedef long long ll;

enum factorial_status_codes {
    fsc_ok,
    fsc_overflow,
    fsc_inv_arg
};

enum factorial_status_codes factorial(unsigned int value, unsigned long *result) {
    if (value > 20) {
        return fsc_overflow;
    }
    enum factorial_status_codes recursive_status_code;
    if (value == 0 || value == 1) {
        *result = 1;
        return fsc_ok;
    }

    recursive_status_code = factorial(value - 1, result);

    if (recursive_status_code == fsc_ok) {
        *result *= value;
    }

    return recursive_status_code;
}

int main(int argc, char* argv[]) {

    // if (argc != 1) {
    //     printf("Invalid amount of arguments. Usage: %s <integer> <\"flag\"> \n", argv[0]);
    //     return 1;
    // }

    // printf("\n");

    unsigned long factorial_result;
    switch(factorial(6, &factorial_result)) {
        case fsc_ok:
            // printf();
            break;
        case fsc_overflow:
            printf("Overflow detected! \n");
            break;
        case fsc_inv_arg:
            printf("Invalid arguments! \n");
            break;
    }

    return 0;
}
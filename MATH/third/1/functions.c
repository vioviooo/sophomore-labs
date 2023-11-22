#include "header.h"

int print_enter_menu(int* num, int* r) {
    printf("Welcome! This program will transform decimal number to numeral system with radix 2^r.\n");
    printf("Please, enter a decimal number: ");

    if (scanf("%d", num) != 1) {
        return INVALID_INPUT;
    }

    printf("Now, enter the power of 2 (r variable): ");

    if (scanf("%d", r) != 1) {
        return INVALID_INPUT;
    }

    return OK;
}

void print_scs(int choice) {
    switch(choice) {
        case INVALID_INPUT:
            printf("\nInvalid input.\n");
            break;
        case OK:
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
        default:
            break;
    }
}

int subtract(int x, int y) {
    while (y != 0) {
        int borrow = (~x) & y; // contains common set bits of y and unset bits of x
        x = x ^ y;
        y = borrow << 1;
    }
    return x;
}

int add(int x, int y) {
    while (y != 0) {
        unsigned carry = x & y; // get common set bits of x and y
        x = x ^ y; 
        y = carry << 1;
    }
    return x;
}

int decimal_to_base_2r(int num, int r, char** result) {
    if (r < 1 || r > 5) {
        return INVALID_INPUT;
    }

    char res[BUFSIZ];
    char* ptr = res + BUFSIZ - 1; // start from the end

    *ptr = '\0';

    while (num > 0) {
        int digit = num & (subtract((1 << r), 1)); // Extract 'r' bits (radix 2^r)
        
        ptr--; // pointer arithmetic, can't change to bitwise operators

        if (digit > 9) {
            *ptr = add(subtract(digit, 10), 'A'); 
        } else {
            *ptr = add(digit, '0');
        }

        num >>= r; // Right-shift by 'r' bits to process next digit
    }

    *result = (char*)malloc(sizeof(char) * (strlen(ptr) + 1));
    if (*result == NULL) {
        return NO_MEMORY;
    }

    strcpy(*result, ptr);

    return OK;
}

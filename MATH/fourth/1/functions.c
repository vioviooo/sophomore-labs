#include "libs.h"

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
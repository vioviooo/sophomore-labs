#include "header.h"

/////////////////////// main functions////////////////////////

int add_in_base(char** ans, const char* num1, const char* num2, int radix, char** clear_me);
int find_sum(char** res, int base, int cnt, ...);

int main(void) {

    printf("Welcome! This program will calculate sum of N integer non-negative numbers in the given base.\n");

    char* res; // stores the resulted number

    // int status = find_sum(&res, 10, 3, "00000003", "03", "003");
    // int status = find_sum(&res, 36, 3, "00CRINGE", "00100", "ZZZ");
    // int status = find_sum(&res, 36, 3, "TOMATO90999", "00000000", "777");
    // int status = find_sum(&res, 2, 3, "0100", "000010", "1");
    int status = find_sum(&res, 2, 3, "0", "0", "0");

    if (status != OK) {
        print_scs(status);
        return status;
    }
    else {
        printf("Final sum: %s\n", res);
    }

    return 0;
}
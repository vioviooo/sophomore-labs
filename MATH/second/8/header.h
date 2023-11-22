#ifndef MYHEADER_H
#define MYHEADER_H

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

typedef long long ll;

enum status_codes {
    OK = 1,
    INVALID_INPUT = 2,
    NO_MEMORY = -1,
    INVALID = -2,
    OVERFLOW_ = -3,
    UNDEFINED = -4,
    INVALID_BASE = 3,
    WARNING_SMALL = 4
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
        case INVALID_BASE:
            printf("Error! Invalid base for one or more given numbers.\n");
            break;
        case WARNING_SMALL:
            printf("Warning! Small values may result in near zero results.\n");
            break;
        default:
            break;
    }
}

bool is_valid_base(int base, char ch[]) {
    for (int i = 0; ch[i] != '\0'; i++) {
        if (isdigit(ch[i])) {
            int digit = ch[i] - '0';
            if (digit >= base) {
                return false;  
            }
        } 
        else if (isalpha(ch[i])) {
            int digit = toupper(ch[i]) - 'A' + 10;
            if (digit >= base) {
                return false; 
            }
        } 
        else {
            return false; 
        }
    }
    return true; 
}

int add_in_base(char** ans, const char* num1, const char* num2, int base, char** clear_me) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int maxLen = (len1 > len2) ? len1 : len2;
    int carry = 0;

    char* result = (char*)malloc((maxLen + 2) * sizeof(char)); // +1 for potential carry, +1 for the null terminator
    if (result == NULL) {
        return -1;
    }

    int i = len1 - 1;
    int j = len2 - 1;
    int k = maxLen + 1; // Start at the end of the result, including space for carry and null terminator
    result[k] = '\0';

    while (i >= 0 || j >= 0 || carry > 0) {
        int digit1 = (i >= 0) ? (isdigit(num1[i]) ? num1[i] - '0' : num1[i] - 'A' + 10) : 0;
        int digit2 = (j >= 0) ? (isdigit(num2[j]) ? num2[j] - '0' : num2[j] - 'A' + 10) : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / base;

        result[--k] = (sum % base < 10) ? (sum % base) + '0' : (sum % base) + 'A' - 10;

        if (i >= 0) i--;
        if (j >= 0) j--;
    }

    *clear_me = result;

    // exclude leading zeros
    while (result[k] == '0' && result[k + 1] != '\0') {
        k++;
    }

    *ans = result + k;

    return 1;
}

int find_sum(char** res, int base, int cnt, ...) {
    if (base < 2 || base > 36 || cnt < 1) {
        return INVALID_INPUT;
    }

    va_list args;
    va_start(args, cnt);

    char* result = NULL;
    char* clear_me = NULL;

    for (int i = 0; i < cnt; i++) {
        char* elem = va_arg(args, char*);

        int m = 0;
        while (elem[m] == '0' && elem[m + 1] != '\0') {
            elem++;
        }

        if (!is_valid_base(base, elem)) {
            return INVALID_BASE;
        }
        
        char* tmp;
        int status = add_in_base(&result, (i == 0) ? "0" : result, elem, base, &clear_me);
        if (status != OK) {
            va_end(args);
            free(clear_me);
            return NO_MEMORY;
        }

        char *result_copied = (char *)malloc(sizeof(char) * (strlen(result) + 1));
        // TODO: check malloc result
        strcpy(result_copied, result);
        *res = result_copied;

        free(clear_me);
    }

    va_end(args);

    return OK;
}

#endif
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
            printf("tmpoject finished successfully\n");
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

int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    else {
        return n * factorial(n - 1);
    }
}

int find_coefs(double eps, int a, double **res, int power, ...) {
    *res = (double*)malloc(sizeof(double) * (power + 1));
    if (*res == NULL) {
        return NO_MEMORY;
    }

    double* coef = (double*)malloc(sizeof(double) * power);
    if (coef == NULL) {
        return NO_MEMORY;
    }

    va_list args;
    va_start (args, power);

    double sum = 0.0;
    for (int i = 0; i < power; i++) {
        double g = va_arg(args, double);
        coef[i] = g;
        sum += (coef[i] * pow(a, power - i));
    }

    sum += va_arg(args, double); // last num
    (*res)[0] = sum;

    double *tmp = (double*)malloc(sizeof(double) * power);
    if (tmp == NULL) {
        return NO_MEMORY;
    }

    int cnt = 0;
    while (cnt != power) {
        double sum = 0.0;
        int var = power - cnt;
        for (int i = 0; i <= var - 1; i++) {
            tmp[i] = coef[i] * (var - i);
            sum += tmp[i] * pow(a, var - i - 1);
        }

        (*res)[cnt + 1] = sum / factorial(cnt + 1);

        for (int i = 0; i <= var - 1; i++) {
            coef[i] = tmp[i];
        }

        cnt++;
    }

    free(coef);
    free(tmp);

    va_end(args);

    return OK;
}

#endif
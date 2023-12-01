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

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

enum status_codes {
    OK = 1,
    INVALID_INPUT = 2,
    NO_MEMORY = -1,
    INVALID = -2,
    OVERFLOW_ = -3,
    UNDEFINED = -4,
    WARNING_UNUSED = 3,
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
        case WARNING_UNUSED:
            printf("Warning! Not all input data was used.\n");
            break;
        case WARNING_SMALL:
            printf("Warning! Small values may result in near zero results.\n");
            break;
        default:
            break;
    }
}

/////////////////////// validations ///////////////////////////

bool is_valid_double(char ch[]) {
    if (ch[0] == '.' || strlen(ch) == 1 || strlen(ch) == 2) {
        return 0;
    }

    int i;
    if (ch[0] == '-') {
        i = 1;
    } else {
        i = 0;
    }
    
    int cnt_dot = 0;
    for (; ch[i] != '\0'; i++) {
        if (ch[i] == '.') {
            cnt_dot++;
        }
        else {
            if (!isdigit(ch[i])) {
                return 0;
            }
        }
        if (cnt_dot > 1) {
            return 0;
        }
    }

    return 1;
}

bool is_valid_integer(char ch[]) {
    int i = 0;

    if (ch[0] == '-' && ch[1] == '\0') {
        return 0;
    }
    else if (ch[0] == '-') {
        i = 1;
    }

    while (ch[i] == '0') {
        i++;
    }

    int prev = i;
    if (strlen(ch) - i > 9) {
        return 0;
    }

    for (; ch[i] != '\0'; i++) {
        if (!isdigit(ch[i])) {
            return 0;
        }
    }

    return 1;
}   

////////////////////main functions////////////////////////

double pow_double(double num, int power) {
    if (power == 0) {
        return 1;
    } 
    else if (power > 0) {
        double res = pow_double(num, power / 2);
        if (power & 1) {
            return res * res * num;
        }
        else {
            return res * res;
        }
    }
    else {
        double res = pow_double(num, power / 2);
        if (power & 1) {
            return res * res * (1.0 / num);
        }
        else {
            return res * res;
        }
    }
}

int find_pow(double* res, char base_ch[], char power_ch[]) {

    if (!is_valid_double(base_ch) && !is_valid_integer(base_ch)) {
        return INVALID_INPUT;
    }

    double num = strtod(base_ch, NULL);

    if (!is_valid_integer(power_ch)) {
        return INVALID_INPUT;
    }

    int power = atoi(power_ch);

    double eps = 1.0;
    while (1.0 + eps / 2.0 > 1.0) {
        eps /= 2.0;
    }

    if (fabs(num) < eps && power == 0) {
        return UNDEFINED;
    }

    *res = pow_double(num, power);

    if (fabs(num) < 0.1) {
        return WARNING_SMALL;
    }

    return OK;
}

int geometric_mean(double* res, int cnt, ...) {
    if (cnt < 1) {
        return INVALID_INPUT;
    }

    va_list args;
    va_start(args, cnt);

    double mult = 1;
    for (int i = 0; i < cnt; i++) {
        mult *= va_arg(args, double);
    }
 
    if (mult < 0.0) {
        va_end(args);
        return UNDEFINED;
    }

    *res = pow(mult, 1.0 / cnt);

    if (va_arg(args, double) != 0) {
        return WARNING_UNUSED;
        va_end(args);
    }

    va_end(args);

    return OK;
}

#endif

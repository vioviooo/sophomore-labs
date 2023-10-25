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
    WARNING_SMALL = 4,
    OVERLAP = -5
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
        case OVERLAP:
            printf("Error! Two or more dots overlap.\n");
            break;
        default:
            break;
    }
}

/////////////////////// struct-related ///////////////////////////

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

// only positive bases are allowed
bool is_valid_integer(char ch[]) {

    if (ch[0] == '-') {
        return 0;
    }
    
    int i = 0;

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

double get_eps() {
    double eps = 1.0;
    while (1.0 + eps / 2.0 > 1.0) {
        eps /= 2.0;
    }
    return eps;
}

int gcd(int a, int b) {
    if (a == 0) {
        return b;
    }
    else {
        return gcd(b % a, a);
    }
}

bool is_prime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

bool helper(int base, int p, int q) {
    for (int i = 2; i <= q; i++) {
        if (q % i == 0) {
            if (is_prime(i) && base % i != 0) {
                return false;
            }
        }
    }
    return true;
}

int is_finite_repr(bool** res, int base, int cnt, ...) {
    if (base < 2 || base > 36 || cnt < 1) {
        return INVALID_INPUT;
    }

    *res = (bool*)malloc(sizeof(bool) * cnt);
    if (*res == NULL) {
        return NO_MEMORY;
    }

    va_list args;
    va_start(args, cnt);

    double eps = get_eps();

    for (int i = 0; i < cnt; i++) {
        double x = va_arg(args, double);
        double elem = x;

        int p, q = 1; // numerator && denominator
        while (elem > (int)elem) {
            elem *= 10;
            q *= 10;
        }

        p = (int)elem;

        int gcd_ = gcd(p, q);

        p /= gcd_;
        q /= gcd_;

        (*res)[i] = helper(base, p, q);
    }

    va_end(args);

    return OK;
}

int main(void) {

    printf("Welcome! This program will identify if certain fraction has a finite representation in the <base> pal system.\n");
    printf("Enter base: ");
    char ch[BUFSIZ];

    scanf("%s", ch);

    if (!is_valid_integer(ch)) {
        print_scs(INVALID_INPUT);
        return INVALID_INPUT;
    }

    int base = atoi(ch);

    bool* res;

    // change input
    int cnt = 5;
    double num1 = 0.046875, num2 = 0.1, num3 = 0.25, num4 = 0.2, num5 = 0.3;

    // change accrodingly
    int status = is_finite_repr(&res, base, cnt, num1, num2, num3, num4, num5);

    if (status != OK) {
        print_scs(status);
        return status;
    }

    for (int i = 0; i < cnt; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    free(res);

    return 0;
}
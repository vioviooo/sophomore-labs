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
typedef long double ld;

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

void print_scs(ll choice) {
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

////////////////////main functions////////////////////////

ld get_eps() {
    ld eps = 1.0;
    while (1.0 + eps / 2.0 > 1.0) {
        eps /= 2.0;
    }
    return eps;
}

ll gcd(ll a, ll b) {
    if (a == 0) {
        return b;
    }
    else {
        return gcd(b % a, a);
    }
}

bool is_prime(ll n) {
    if (n <= 1) {
        return false;
    }
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

bool helper(ll base, ll p, ll q) {
    for (ll i = 2; i <= q; i++) {
        if (q % i == 0) {
            if (is_prime(i) && base % i != 0) {
                return false;
            }
        }
        // while (q % i == 0) {
        //     q /= i;
        // }
    }
    return true;
}

ll is_finite_repr(bool** res, ll base, ll cnt, ...) {
    if (base < 2 || base > 36 || cnt < 1) {
        return INVALID_INPUT;
    }

    *res = (bool*)malloc(sizeof(bool) * cnt);
    if (*res == NULL) {
        return NO_MEMORY;
    }

    va_list args;
    va_start(args, cnt);

    ld eps = 1e-9;

    for (ll i = 0; i < cnt; i++) {
        ld x = va_arg(args, ld);
        ld elem = x;

        ll p, q = 1; // numerator && denominator
        while (fabsl(elem - floor(elem)) > eps) {
            elem *= 10;
            q *= 10;
        }

        p = (ll)elem;

        ll gcd_ = gcd(p, q);

        printf("HERE: %lld %lld\n", p, q);

        p /= gcd_;
        q /= gcd_;

        printf("HERE: %lld %lld\n", p, q);

        (*res)[i] = helper(base, p, q);
    }

    va_end(args);

    return OK;
}

int main(void) {

    printf("Welcome! This program will identify if certain fraction has a finite representation in the <base> pal system.\n");
    printf("Enter base: ");
    
    ll base;
    if (scanf("%lld", &base) != 1 || getchar() != '\n') {
        print_scs(INVALID_INPUT);
        return INVALID_INPUT;
    }

    bool* res;

    // change input
    ll cnt = 5;

    // ans : 0 0 1 1 1
    ld num1 = 0.3, num2 = 0.1, num3 = 0.25, num4 = 0.125, num5 = 0.00006103515625;
    
    // correct : 1 1 1 1 1
    // ld num1 = 0.0000152587890625, num2 = 0.000030517578125, num3 = 0.00006103515625, num4 = 0.0001220703125, num5 = 0.0009765625;

    // change accrodingly
    ll status = is_finite_repr(&res, base, cnt, num1, num2, num3, num4, num5);

    if (status != OK) {
        print_scs(status);
        return status;
    }

    for (ll i = 0; i < cnt; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    free(res);

    return 0;
}
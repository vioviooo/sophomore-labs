#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

typedef long long ll;
typedef long double ld;

long long MAX_LL = LLONG_MAX;

ll charToNum(char* ch) {
    ll num = atoll(ch);
    return num;
}

int myAtoi(const char* ch) {
    int sign = 1;
    if (ch[0] == '-') {
        sign *= -1;
    }

    int res = 0, d = 1;
    for (int i = 0; ch[i] != '\0'; i++) {
        if (ch[i] >= '0' && ch[i] <= '9') {
            res = res + d * (ch[i] - '0');
        }
        d *= 10;
    }

    return sign * res;
}

ld eSeries(ld eps) {
    ld res = 2.0, diff = eps + 1.0;
    ll fact = 1;
    for (int n = 2; eps < diff; n++) {
        fact *= n;
        res += (1.0 / fact);
        diff = 1.0 / fact;
    }
    return res;
}

int main(int argc, char *argv[]) {

    // int nunu = myAtoi(argv[1]);

    // printf("%d", nunu);

    ld eps = 1e-5;
    printf("%.9Lf \n", eSeries(eps));

    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

typedef long long ll;
typedef long double ld;

long long MAX_LL = LLONG_MAX;

ll factorial(ll n) {
    if (n < 0) {
        return -1;
    }
    ll res = 1;
    for (ll i = 2; i <= n; i++) {
        if (i > MAX_LL / res) {
            return -2;
        }
        res *= i;
    }
    return res;
}

ld eLimit(ld eps) {
    ld res = 0, prev = 1.0, curr = 0.0;
    for (int n = 1; fabsl(prev - curr) > eps; n *= 2) {
        prev = curr;
        curr = pow(1.0 + 1.0 / n, n); 
    }
    return curr;
}

ld eQuation(ld eps) {
    ld x = 1.0, n = 0;
    while (fabsl((x * log(x) - x)) > eps) {
        x = x - (log(x) - 1.0) / (1.0 / x);
    }
    return x;
}

ld eSeries(ld eps) {
    ld res = 2.0, diff = eps + 1.0;
    ll fact = 1;
    for (int n = 2; eps < diff; n++) {
        fact *= n;
        res += (1.0 / fact);
        diff = (1.0 / fact);
    }
    return res;
}

ld piLimit(ld eps) {
    ld res, diff = eps + 1.0, prev = 0.0;
    for (ll n = 1; diff > eps; n++) {
        if (factorial(n) < 0) {
            break;
        }
        res = pow(pow(2, n) * factorial(n), 4) / n * pow(factorial(2 * n), 2);
        diff = fabsl(res - prev);
        prev = res;
    }
    return res;
}

ld piSeries(ld eps) {
    ld res = 1.0, diff = eps + 1.0, n = 1.0;
    ll sign = 1;

    for (n = 3.0; diff > eps; n += 2.0) { // начинаем с n = 1.0 + 2.0, так как подсчет предполагается для следующего же значения
        sign *= -1;
        res += (sign / n);
        diff = fabsl(sign / n);
    }

    return 4 * res;
}

ld piEquation(ld eps) {
    ld x = 1.0, n = 0;
    while (fabsl((cos(x) + 1.0) / sin(x)) > eps) {
        x = x + (cos(x) + 1.0) / (sin(x));
    }
    return x;
}

ld lnLimit(ld eps) {
    ld res, diff = eps + 1.0, prev = 0.0;
    for (int n = 1; diff > eps; n++) {
        res = n * (pow(2, 1.0 / n) - 1.0);
        diff = fabsl(prev - res);
        prev = res;
    }
    return res;
}

ld lnEquation(ld eps) {
    ld x = 1.0; // initial guess
    while (fabsl((pow(exp(1.0), x) - 2.0)) > eps) {
        x = x - (pow(exp(1.0), x) - 2.0) / exp(1.0);
    }
    return x;
}

ld lnSeries(ld eps) {
    ld res = 0.0, sign = 1.0, diff = 1.0 + eps;
    for (int n = 1; eps < diff; n++) {
        res += sign / n;
        sign *= -1;
        diff = fabsl(sign / n);
    }
    return res;
}

ld sqrtEquation(ld eps) {
    ld x = 1.0;
    while (fabsl((x * x - 2) / 2 * x) > eps) {
        x = x - (x * x - 2) / 2 * x;
    }
    return x;
}

// ld sqrtSeries(ld eps) {
//     ld res, diff = 1.0 + eps;
//     int power = 0;
//     ll res = 1, prev;
//     for (int k = 2; diff > eps; k++) {
//         power -= k;
//         prev = res;
//         res *= pow(pow(2, pow(2, power)), 4);
//         diff = absl(prev - res);
//     }
//     return res - 2;
// }

ld sqrtLimit(ld eps) {
    ld res, prev = -0.5, diff = eps + 1.0;
    while (diff > eps) {
        res = prev - 0.5 * prev * prev + 1;
        diff = fabsl(res - prev);
        prev = res;
    }
    return res;
}

int main() {

    ld eps;
    scanf("%Lf", &eps);

    int l; // how many decimal places 
    scanf("%d", &l);
    
    // ld res = eQuation(eps);

    // printf("%.*Lf", l, res);

    // int n = atoi(argv[1]);

    printf("Choose a number: \n 1. Euler's number \n 2. Pi \n 3. Natural logarithm of 2 \n 4. Square root of 2 \n 5. Y \n");

    int number;
    scanf("%d", &number);

    // printf("%d", number);

    switch(number) {
        case 1:
            printf("%.*Lf \n%.*Lf \n%.*Lf \n", l, eLimit(eps), l, eQuation(eps), l, eSeries(eps));
            // printf("%.*Lf \n", l, eSeries(eps));
            break;
        case 2:
            // printf("%.*Lf \n%.*Lf \n%.*Lf \n", l, piLimit(eps), l, piEquation(eps), l, piSeries(eps));
            printf("%.*Lf\n%.*Lf\n%.*f", l, piEquation(eps), l, piSeries(eps), l, acos(-1));
            // piSeries(1e-9);
            break;
        case 3: 
            printf("%.*Lf\n%.*Lf\n%.*Lf\n", l, lnLimit(eps), l, lnEquation(eps), l, lnSeries(eps));
            break;
        case 4:
            printf("%.*Lf\n", l, sqrtLimit(eps) /* sqrtEquation(eps) *//* , l, piSeries(eps), l, acos(-1) */);
            break;
        case 5: 
            break;
    }

    printf("\n");

    return 0;
}
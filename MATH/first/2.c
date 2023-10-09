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
    if (n == 0 || n == 1) {
        return 1;
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

bool isDigit(char ch) {
    return (ch >= '0' && ch <= '9') ? true : false;
}

bool isValidInteger(int n) {
    return n > 21 ? false : true;
}

// scientific notation ~1e±n
ld sciNotation(char* ch) {
    int coef = 1, d = 10, i;
    for (i = 0; ch[i] != 'e'; i++) {
        if (i == 0 && isDigit(ch[i]) && ch[i] != '0') {
            coef *= (ch[i] - '0');
        }
        else if (isDigit(ch[i])) {
            coef = coef * d + (ch[i] - '0');
            d *= 10;
        }
    }

    if (ch[i + 1] != '-') { // eps is too big
        return 2.0; 
    }

    i += 2; // we stopped at e => '-' will be right after e

    int power = 1;
    if (isDigit(ch[i]) && ch[i] != '0') {
        power *= (ch[i] - '0');
    }

    i++; 
    d = 10;
    for (; ch[i] != '\0'; i++) {
        if (isDigit(ch[i])) {
            power = power * d + (ch[i] - '0');
            d *= 10;
        }
    }

    ld eps = coef * pow(10, -power);

    return eps;
}

ld getEpsilon(char* ch) { // нет проверки на корректность последовательной записи экспоненц эпсилона
    for (int i = 0; ch[i] != '\0'; i++) {
        if (ch[i] == 'e') {
            ld eps = sciNotation(ch);
            return eps;
        }
    }
    ld eps = strtold(ch, NULL);
    return eps;
}

bool isInteger(char* ch) {
    for (int i = 0; ch[i] != '\0'; i++) {
        if (ch[i] < '0' || ch[i] > '9') {
            return false;
        }
    }
    return true;
}

ld eLimit(ld eps) {
    ld res = 0, prev = 1.0, curr = 0.0;
    for (int n = 1; fabsl(prev - curr) > eps; n++) {
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

ld piLimit(ld eps) { // выразить через предыдущий
    ld res = 4.0, diff = eps + 1.0, prev = 0.0;
    for (int n = 1; diff > eps; n++) {
        prev = res;
        res *= (4 * n * (n + 1) / pow(2 * n + 1, 2));
        diff = fabsl(res - prev);
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

ld lnSeries(ld eps) {
    ld res = 0.0, sign = 1.0, diff = 1.0 + eps;
    for (int n = 1; eps < diff; n++) {
        res += sign / n;
        sign *= -1;
        diff = fabsl(sign / n);
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

ld sqrtLimit(ld eps) {
    ld res, prev = -0.5, diff = eps + 1.0;
    while (diff > eps) {
        res = prev - 0.5 * prev * prev + 1;
        diff = fabsl(res - prev);
        prev = res;
    }
    return res;
}

ld sqrtSeries(ld eps) {
    ld diff = 1.0 + eps, power = 0.25, res = pow(2, power), prev;
    for (int k = 2; diff > eps; k++) {
        power *= 0.5;
        prev = res;
        res *= pow(2, power);
        diff = fabsl(prev - res);
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

//////////

double combination(int m, int k) {
    double res = 1;
    for (int i = k + 1; i <= m; ++i) {
        res *= i;
    }
    return res / factorial(m - k);
}

double gammaLimit(double eps) {
    eps = 1e-3;
    int m = 2, c = 0;
    double prev, res, sum, fact;
    do {
        prev = res, sum = 0, fact = 1;
        for (int i = 1; i <= m; ++i) {
            fact *= i;
            c = combination(m, i);
            sum += (c * log(fact) * pow(-1, i)) / i;
        }
        res = sum;
        m++;
    } while (eps < fabs(res - prev));

    return res;
}

/////////

double gammaSeries() {
    double eps = 1e-15; // если число больше, то TL
    double res = 0.5, diff = 1.0 + eps, prev, elem;
    for (int k = 3; diff > eps; k++) {
        prev = res;
        elem = ((1.0 / pow(floor(sqrt(k)), 2)) - (1.0 / k));
        res += elem;
        if (elem < eps) {
            prev = 0.0;
        }
        diff = fabsl(res - prev);
    }
    return res - acos(-1) * acos(-1) / 6;
}
///////////

bool isPrime(int n) {
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

double gammaEquationP(int t) {
    double res = 1.0;
    for (int i = 2; i <= t; i++) {
        if (isPrime(i)) {
            res *= (i - 1.0) / i;
        }
    }
    return res;
}

double gammaEquationLimit(double eps) {
    double res = 0.0, prev = 0.0;
    int t = 2;

    eps = 1e-4;

    do {
        prev = res;
        res = log(t) * gammaEquationP(t);
        t++;
    } while (fabs(res - prev) > eps);

    return res;
}

double gammaEquation(double eps) {
    double prev = 0.0, res = 1.0;
    for (;; res += prev) {
        prev = (exp(-res) - gammaEquationLimit(eps)) / exp(-res);
        if (eps >= fabs(prev)) {
            break;
        }
    }
    return res;
}

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("Error! Invalide amount of arguments. Usage: %s <epsilon> <integer> \n", argv[0]);
        return 1;
    }

    ld eps = getEpsilon(argv[1]);

    if (!isInteger(argv[2])) {
        printf("Error! Second parameter is not an integer. \n");
        return 1;
    }

    int l = atoi(argv[2]); // how many decimal points

    if (!isValidInteger(l)) {
        printf("Error! l is out of bounds of the long double type. \n");
        return 1;
    }

    if (eps > 1.0) {
        printf("Bruh eps > 1.0");
        return 1;
    }

    printf("Choose a number: \n 1. Euler's number \n 2. Pi \n 3. Natural logarithm of 2 \n 4. Square root of 2 \n 5. Y \n");

    int number;
    scanf("%d", &number);

    switch(number) {
        case 1:
            printf("Limit: %.*Lf \nSeries: %.*Lf \nEquation: %.*Lf \n", l, eLimit(eps), l, eSeries(eps), l, eQuation(eps));
            break;
        case 2:
            printf("Limit: %.*Lf \nSeries: %.*Lf \nEquation: %.*Lf \n", l, piLimit(eps), l, piSeries(eps), l, piEquation(eps));
            break;
        case 3: 
            printf("Limit: %.*Lf \nSeries: %.*Lf \nEquation: %.*Lf \n", l, lnLimit(eps), l, lnSeries(eps), l, lnEquation(eps));
            break;
        case 4:
            printf("Limit: %.*Lf \nSeries: %.*Lf \nEquation: %.*Lf \n", l, sqrtLimit(eps), l, sqrtSeries(eps), l, sqrtEquation(eps));
            break;
        case 5: 
            printf("Limit: %.*f\nSeries: %.*f\nEquation: %.*f\n", l, gammaSeries(), l, gammaEquation(eps), l, gammaLimit(eps));
            break;
    }

    printf("\n");

    return 0;
}
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

bool isDigit(char ch) {
    return (ch >= '0' && ch <= '9') ? true : false;
}

ld sciNotation(char* ch) {
    int coef = 1, d = 10, i;
    for (i = 0; ch[i] != 'e'; i++) {
        if (i == 0 && isDigit(ch[i]) && ch[i] != '0') {
            coef *= (ch[i] - '0');
            printf("%d \n", coef);
        }
        else if (isDigit(ch[i])) {
            coef = coef * d + (ch[i] - '0');
            d *= 10;
        }
    }

    if (ch[i + 1] != '-') {
        return 2.0;
    }

    i += 2; // cause we stopped at e, then will be '-', and after the power

    int power = 1;
    if (isDigit(ch[i]) && ch[i] != '0') {
        power *= (ch[i] - '0');
    }

    i += 1; 
    d = 10;
    for (; ch[i] != '\0'; i++) {
        if (isDigit(ch[i])) {
            power = power * d + (ch[i] - '0');
            d *= 10;
        }
    }

    printf("%d %d \n", coef, power);

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

double gammaSeries() {
    double eps = 0.0000000000001;
    double res = 0.5, diff = 1.0 + eps, prev, elem;
    for (int k = 3; diff > eps; k++) {
        prev = res;
        elem = ((1.0 / pow(floor(sqrt(k)), 2)) - (1.0 / k));
        res += elem;
        if (elem < eps) {
            prev = 0.0;
        }
        diff = fabs(res - prev);
    }
    return res - acos(-1) * acos(-1) / 6;
}

double boogammaSeries()
{
    double preres = 0;
    double n = 3;
    double eps = 0.0000000000001;
    // floor - отбрасывает дробную часть
    double res = 0.5;
    double elem = 0;
    do
    {
        preres = res;
        elem = ((1.0 / pow(floor(sqrt(n)), 2)) - (1.0 / n));
        res += elem;
        if (elem < eps) preres = 0;
        n++;
    } 
    while (eps < fabs(res - preres));
    return (res - (pow(acos(-1), 2) / 6));
}

int main(int argc, char *argv[]) {

    // int nunu = myAtoi(argv[1]);

    // printf("%d", nunu);

    ld eps = getEpsilon(argv[1]);

    printf("%.*f", 10, gammaSeries());

    return 0;
}

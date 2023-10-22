#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>

typedef long long ll;

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

enum status_codes {
    OK = 1,
    INVALID_INPUT = -1,
    NO_MEMORY = -2,
    INVALID = -3,
    OVERFLOW_ = -4,
    OK_SCI = 2,
    OK_DOUBLE = 3
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
        default:
            break;
    }
}

/////////////////////// validations ///////////////////////////

bool is_valid_double(const char ch[]) {
    if (ch[0] == '.') {
        return false;
    }

    int i = (ch[0] == '-') ? 1 : 0;
    int cnt_dot = 0;

    while (ch[i] != '\0') {
        if (ch[i] == '.') {
            cnt_dot++;
        } else if (!isdigit(ch[i])) {
            return false;
        }
        if (cnt_dot > 1) {
            return false;
        }
        i++;
    }

    return true;
}

int is_valid_eps(char ch[]) {
    if (strlen(ch) >= 4 && ch[0] == '1' && ch[1] == 'e' && ch[2] == '-') {
        if (ch[3] == '0') {
            return 0;
        }

        int i = 3;
        for (; ch[i] != '\0'; i++) {
            if (!isdigit(ch[i])) {
                return 0;
            }
        }

        if (strlen(ch) == 5 && ch[4] > '5') {
            return 0;
        }

        return OK_SCI;
    }

    if (strlen(ch) < 3 || ch[0] != '0' || ch[1] != '.') {
        return 0;
    }
    
    if (is_valid_double(ch)) {
        return OK_DOUBLE;
    }

    return 0;
}

double get_eps(char ch[]) {
    double eps;
    double power = 1.0, d = 10;
    for (int i = 3; ch[i] != '\0'; i++) {
        if (i != 3) {
            power = power * d + (ch[i] - '0');
            d *= 10;
        }
        else {
            power = ch[i] - '0';
        }
    }

    eps = pow(10, -power);

    return eps;
}

////////////////////main functions////////////////////////

// ans = 2.0
double easy_function(double x) {
    return x * x - 4;
}

// x <= 1.0, ans = 0.57
double hard_function(double x) {
    return sqrt(1 - x) - tan(x);
}

// ans = 0.98
double another_function(double x) {
    return x + cos(pow(x, 0.52) + 2);
}

typedef double (*foo)(double);

// вывод енамо с сошибками + проверками жпсилон прямо внутри функции
bool dichotomy(double a, double b, double EPS, foo this_function, double* res) {
    bool flag = true;
    double c = 0;
    int cnt = 0;
    while (fabsl(a - b) > EPS && flag) {
        c = (a + b) / 2; // middle point
        if (this_function(c) == 0) {
            break;
        }
        else {
            if (this_function(c) * this_function(a) < 0) {
                b = c;
            }
            else if (this_function(b) * this_function(c) < 0) {
                a = c;
            }
            cnt++;
        }
        if (cnt > 1000) {
            flag = false;
        }
    }
    
    *res = c;

    return flag;
}

int main(int argc, char* argv[]) {

    if (!is_valid_double(argv[1]) || !is_valid_double(argv[2]) || !is_valid_eps(argv[3])) {
        print_scs(INVALID_INPUT);
        return INVALID_INPUT;
    }

    double eps;
    if (is_valid_eps(argv[3]) == OK_DOUBLE) {
        eps = strtod(argv[3], NULL);
    }
    else {
        eps = get_eps(argv[3]);
    }

    double low = strtod(argv[1], NULL), high = strtod(argv[2], NULL);

    // printf("%.15f %.15f %.15f\n", low, high, eps);
    
    double res;
    if (dichotomy(high, low, eps, another_function, &res)) {
        printf("Result: %.15f\n", res);
    }
    else {
        printf("Couldn't calculate the result.\n");
        return INVALID;
    }

    return 0;
}

/* TASK 
Реализуйте функцию, которая находит корень уравнения одной переменной методом дихотомии. Аргументами функции являются
 границы интервала, на котором находится корень; точность (эпсилон), с которой корень необходимо найти, а также указатель 
 на функцию, связанной с уравнением от одной переменной. Продемонстрируйте работу функции на разных значениях интервалов и 
 точности, для различных уравнений.
*/
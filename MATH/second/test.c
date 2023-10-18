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
    INVALID_INPUT = 2,
    NO_MEMORY = -1,
    INVALID = -2
};

void print_scs(int choice) {
    switch(choice) {
        case 2:
            printf("Invalid input.\n");
            break;
        case 1:
            printf("Project finished successfully\n");
            break;
        case -1:
            printf("No memory left.\n");
            break;
        case -2: 
            printf("Invalid something.\n");
            break;
        case -3:
            printf("Overflow!\n");
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

// -00000000098980900
// -000000 => 0
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

double pow_double(double num, int power) {
    if (power == 0) {
        return 1;
    }
    double res = pow_double(num, power / 2);
    if (power & 1) {
        return res * res * num;
    }
    else {
        return res * res;
    }
}

double biba(int cnt, ...) {
    va_list args;
    va_start(args, cnt);

    double mult = 1;
    for (int i = 0; i < cnt; i++) {
        mult *= va_arg(args, double);
    }

    double res = pow(mult, 1.0 / cnt);

    va_end(args);

    return res;
}

int main(int argc, char* argv[]) {

    double res = biba(3, 1.3, 1.1, 2.1);
    printf("%f \n", res);

    return 0;
}

/* TASK 
1. Реализуйте функцию с переменным числом аргументов, 
вычисляющую среднее геометрическое переданных ей чисел вещественного 
типа. Количество (значение типа int) переданных вещественных чисел 
задаётся в качестве последнего обязательного параметра функции.

2. Реализуйте рекурсивную функцию возведения вещественного числа в 
целую степень. При реализации используйте алгоритм быстрого 
возведения в степень. Продемонстрируйте работу реализованных функций.
*/
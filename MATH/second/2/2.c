#include "header.h"

////////////////////////// validations ///////////////////////////

void print_scs(int choice);
bool is_valid_double(char ch[]);
bool is_valid_integer(char ch[]);

/////////////////////// main functions////////////////////////

double pow_double(double num, int power);
int find_pow(double* res, char base_ch[], char power_ch[]);
int geometric_mean(double* res, int cnt, ...);

int main(void) {

    printf("Welcome to the program! Choose the desired action:\n");
    printf("1. Find geometric mean [no input allowed]\n2. Raise a double number to the n-th power\n");

    int choice;
    if (scanf("%d", &choice) != 1 || getchar() != '\n') {
        print_scs(INVALID_INPUT);
        return INVALID_INPUT;
    }

    switch(choice) {
        case 1: {
            double res = 0.0;
            int status = geometric_mean(&res, 3, 1.0, -1.0, 1.0);
            if (status != OK && status != WARNING_UNUSED) {
                print_scs(status);
                exit(status);
            }
            else if (status == WARNING_UNUSED) {
                print_scs(status);
            }

            printf("Geometric mean: %f\n", res);

            break;
        }
        case 2: {

            char base[BUFSIZ];
            char power[BUFSIZ];

            printf("Please, enter the base [double]: ");

            scanf("%s", base);

            printf("Now, enter the power [integer]: ");

            scanf("%s", power);

            double res;
            int status = find_pow(&res, base, power);
            if (status != OK && status != WARNING_SMALL) {
                print_scs(status);
                exit(status);
            }
            else {
                print_scs(status);
            }

            printf("Result: %.15f\n", res);

            break;
        }
    }

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
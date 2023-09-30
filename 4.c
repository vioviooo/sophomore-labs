#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

typedef long long ll;

enum status_codes
{
    sc_okay,
    sc_no_solution,
    sc_one_solution,
    sc_two_solutions
};

enum status_codes solve_equation(double eps, double a, double b, double c, double* x1, double* x2) 
{
    double D = b * b - 4 * a * c;

    if (D < 0) {
        return sc_no_solution;
    }

    if (D == 0) {
        *x1 = (-b + sqrt(D)) / 2 * a;
        return sc_one_solution;
    }
    
    *x1 = (-b + sqrt(D)) / 2 * a;
    *x2 = (-b - sqrt(D)) / 2 * a;

    return sc_two_solutions;
}

void swap(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

struct Solution {
    int code;
    double res1, res2;
};

void solutions_to_array(double (*ptr)[3], struct Solution* arr, double eps, int* count) {

    double res1, res2;

    if (solve_equation(eps, (*ptr)[0], (*ptr)[1], (*ptr)[2], &res1, &res2) == sc_one_solution) {
        arr[*count].code = 1;
        arr[*count].res1 = res1;
    }
    if (solve_equation(eps, (*ptr)[0], (*ptr)[1], (*ptr)[2], &res1, &res2) == sc_two_solutions) {
        arr[*count].code = 2;
        arr[*count].res1 = res1;
        arr[*count].res2 = res2;
    }
    if (solve_equation(eps, (*ptr)[0], (*ptr)[1], (*ptr)[2], &res1, &res2) == sc_no_solution) {
        arr[*count].code = 0;
    }
}

void next_permutation(double (*ptr)[3], double eps, int start, int finish, struct Solution* arr, int* count) {
    if (start == finish) 
    {
        solutions_to_array(&(*ptr), arr, eps, count);
        (*count)++;
        return;
    }

    for (int i = start; i < finish; i++) 
    {
        swap(&(*ptr)[start], &(*ptr)[i]);
        next_permutation(&(*ptr), eps, start + 1, finish, arr, count);
        swap(&(*ptr)[start], &(*ptr)[i]);
    }
}

bool is_digit(char ch) {
    return (ch >= '0' && ch <= '9') ? true : false;
}

double scientific_notation(char* ch) 
{
    int coef = 1, d = 10, i;
    for (i = 0; ch[i] != 'e'; i++) 
    {
        if (i == 0 && is_digit(ch[i]) && ch[i] != '0') 
        {
            coef *= (ch[i] - '0');
        }
        else if (is_digit(ch[i])) 
        {
            coef = coef * d + (ch[i] - '0');
            d *= 10;
        }
    }

    if (ch[i + 1] != '-') 
    {
        return 2.0; 
    }

    i += 2; // we stopped at e => '-' will be right after e

    int power = 1;
    if (is_digit(ch[i]) && ch[i] != '0') 
    {
        power *= (ch[i] - '0');
    }

    i += 1, d = 10;
    for (; ch[i] != '\0'; i++) 
    {
        if (is_digit(ch[i])) 
        {
            power = power * d + (ch[i] - '0');
            d *= 10;
        }
    }

    double eps = coef * pow(10, -power);

    return eps;
}

double get_epsilon(char* ch) 
{
    for (int i = 0; ch[i] != '\0'; i++) 
    {
        if (ch[i] == 'e') 
        {
            double eps = scientific_notation(ch);
            return eps;
        }
    }

    double eps = strtod(ch, NULL);

    return eps;
}

void selection_sort(double *arr, int size, double eps) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] - arr[j] > eps) swap(&arr[i], &arr[j]);
        }
    }
}

bool is_triangle(double a, double b, double c, double eps) {
    if (fabs(sqrt(a * a + b * b) - c) < eps) {
        return true;
    }
    if (fabs(sqrt(c * c + b * b) - a) < eps) {
        return true;
    }
    if (fabs(sqrt(a * a + c * c) - b) < eps) {
        return true;
    }
    return false;
}

/////////////////////////////////

int main(int argc, char* argv[]) 
{
    if (argc < 3 || argc > 4) 
    {
        printf("Invalid amount of arguments. Usage: %s <flag> <input_file> [output_file]\n", argv[0]);
        return 1;
    }

    char* flags[] = {"d", "i", "s", "a"};

    char ind = '0';
    for (int i = 0; i < 3 && argv[1][2] == '\0' && (argv[1][0] == '/' || argv[1][0] == '-'); i++) 
    {
        if (argv[1][1] == *flags[i]) // ??
        {
            ind = argv[1][1];
        }
    }

    if (ind == '0') {
        for (int i = 0; i < 3 && argv[1][1] == 'n' && argv[1][3] == '\0' && (argv[1][0] == '/' || argv[1][0] == '-'); i++) 
        {
            if (argv[1][2] == *flags[i]) // ??
            {
                ind = argv[1][2];
            }
        }
    }
    
    if (ind == '0') 
    {
        printf("Invalid command. Try again.\n");
        return 1;
    }

    char* input_file_name = argv[2];
    char* output_file_name;

    if (argc == 3) 
    {
        output_file_name = argv[3];
        char* st = "out_";
        strcat(st, input_file_name);

        for (int i = 0; st[i] != '\0'; i++) {
            printf("%c", st[i]);
        }
    }
    else
    {
        output_file_name = argv[3];
    }


    // switch(ind) 
    // {
    //     case 'd': 
    //         break;
    //     case 'i':
    //         break;
    //     case 's':
    //         break;
    //     case 'a':
    //         break;
    // }

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

typedef long long ll;

struct Solution {
    int code;
    double res_fi, res_se;
};

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

void swap(double* a, double* b) {
    double tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
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

void result_array(double* coef_array, double eps, struct Solution res[]) {
    double res1, res2;
    if (solve_equation(eps, coef_array[0], coef_array[1], coef_array[2], &res1, &res2) == sc_one_solution) {
        res[0].code = 1;
    }
    if (solve_equation(eps, coef_array[0], coef_array[1], coef_array[2], &res1, &res2) == sc_two_solutions) {
        printf("%.7f %.7f \n", res1, res2);
    }
    if (solve_equation(eps, coef_array[0], coef_array[1], coef_array[2], &res1, &res2) == sc_no_solution) {
        printf("No solutions such that x ∈ R. \n");
    }
    // for (int i = 0; i < 3; i++) {
    //     printf("%.5f ", arr[i]);
    // }
    // printf("\n");
}

void make_permutations(double* arr[], int start, int finish, double eps, struct Solution* res[]) {
    if (start == finish) {
        result_array(arr, eps, res);
        return;
    }

    for (int i = start; i < finish; i++) {
        swap(&arr[start], &arr[i]);
        make_permutations(arr, start + 1, finish, eps, res);
        swap(&arr[start], &arr[i]);
    }
}

int main(int argc, char* argv[]) 
{
    double eps = get_epsilon(argv[2]);
    double a = strtod(argv[3], NULL), b = strtod(argv[4], NULL), c = strtod(argv[5], NULL); // check correctness of input

    double coef_array[] = {a, b, c};

    int num = 6;
    struct Solution* res_array = (struct Solution*)malloc(num * sizeof(struct Solution));

    // // посортить изначальный массивчик

    make_permutations(coef_array, 0, 3, eps, res_array);


    return 0;
}
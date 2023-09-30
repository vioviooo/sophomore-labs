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
    if (argc < 5) 
    {
        printf("Invalid amount of arguments. \n");
        return 1;
    }

    char* flags[] = {"q", "m", "t"};

    int ind = -1;
    for (int i = 0; i < 3 && argv[1][2] == '\0' && (argv[1][0] == '/' || argv[1][0] == '-'); i++) 
    {
        if (argv[1][1] == *flags[i]) // ??
        {
            ind = i + 1;
        }
    }

    if (ind == -1) {
        printf("Invalid command. Try again. \n");
        return 1;
    }

    if (ind == 1)
    {
        if (argc != 6) 
        {
            printf("Invalid amount of arguments. Usage: %s <flag> <epsilon> <coef #1> ... <coef #4> \n", argv[0]);
            return 1;
        }

        double a = strtod(argv[3], NULL), b = strtod(argv[4], NULL), c = strtod(argv[5], NULL);
        double eps = get_epsilon(argv[2]);

        double initial_array[3] = {a, b, c};

        selection_sort(initial_array, 3, eps);
        
        int size_array = 6; // n! -- num of permutations
        struct Solution* solution_array = (struct Solution*)malloc(size_array * sizeof(struct Solution));

        if (solution_array == NULL) 
        {
            printf("Memory allocation failed lol \n");
            return 1;
        }

        int cnt = 0;
        int* count = &cnt;

        next_permutation(&initial_array, eps, 0, 3, solution_array, count);

        for (int i = 0; i < 6; i++) 
        {
            if (solution_array[i].code == 0) 
            {
                printf("No solutions such that x ∈ R found. \n");
            }
            else if (solution_array[i].code == 1) 
            {
                printf("One solution found: x1 = %.2f \n", solution_array[i].res1);
            }
            else if (solution_array[i].code == 2) 
            {
                printf("Two solutions found: x1 = %.2f, x2 = %.2f \n", solution_array[i].res1, solution_array[i].res2);
            }
        }

        free(solution_array);
    }
    
    if (ind == 2) 
    {
        if (argc != 5) 
        {
            printf("Invalid amount of arguments. Usage: %s <flag> <n1> <n2> <epsilon> \n", argv[0]);
            return 1;
        }

        double a = strtod(argv[2], NULL), b = strtod(argv[3], NULL);
        double eps = strtod(argv[4], NULL);

        double rem = fabs(a) - fabs((int)(a / b) * b);

        if (rem < eps) 
        {
            printf("%.4f Yes\n", rem);
        }
        else 
        {
            printf("%.4f No\n", rem);
        }
    }

    if (ind == 3)
    {
        if (argc != 6) 
        {
            printf("Invalid amount of arguments. Usage: %s <flag> <a> <b> <c> <epsilon> \n", argv[0]);
            return 1;
        }

        double a = strtod(argv[2], NULL), b = strtod(argv[3], NULL), c = strtod(argv[4], NULL);
        double eps = strtod(argv[5], NULL);

        if (is_triangle(a, b, c, eps)) 
        {
            printf("Yes\n");
        }
        else 
        {
            printf("No\n");
        }
    }    

    return 0;
}
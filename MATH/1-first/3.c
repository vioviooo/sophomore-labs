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
        solutions_to_array(ptr, arr, eps, count);
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

////

enum status_codes_eps 
{
    sc_okay_exp, // exponential form 1e-5
    sc_okay_ord, // ordinary form : 0.00001
    sc_error
};

bool is_digit(char ch) 
{
    return (ch >= '0' && ch <= '9') ? true : false;
}

double scientific_notation(char* ch) 
{
    double eps;

    double coef = ch[0] - '0';

    double power = 1.0, d = 10;
    for (int i = 3; ch[i] != '\0'; i++) 
    {
        if (i != 3) 
        {
            power = power * d + (ch[i] - '0');
            d *= 10;
        }
        else 
        {
            power = ch[i] - '0';
        }
    }

    eps = coef * pow(10, -power);

    return eps;
}

enum status_codes_eps get_epsilon(char* ch) 
{   
    int e_count = 0, hyphen_count = 0, dot_count = 0, ind_e, ind_h;
    for (int i = 0; ch[i] != '\0'; i++) {
        if (ch[i] == 'e') {
            ind_e = i;
            e_count++;
        }
        else if (ch[i] == '-') {
            hyphen_count++;
            ind_h = i;
        }
        else if (ch[i] == '.') {
            dot_count++;
        }
        else if (!is_digit(ch[i])) {
            return sc_error;
        }
    }

    printf("%d \n", dot_count);

    if (dot_count > 1 || hyphen_count > 1 || e_count > 1) {
        return sc_error;
    }

    if (e_count == 0 && hyphen_count == 0 && dot_count == 1) {
        return sc_okay_ord;
    }

    if (ind_e != 1) {
        return sc_error;
    }

    if (ind_e == ind_h - 1) {
        return sc_okay_exp;
    }

    return sc_error;

}

/////

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
            printf("Invalid amount of arguments. Usage: %s <flag> <epsilon> <coef #1> ... <coef #3> \n", argv[0]);
            return 1;
        }

        double a = strtod(argv[3], NULL), b = strtod(argv[4], NULL), c = strtod(argv[5], NULL);

        double eps;
        if (get_epsilon(argv[2]) == sc_error) 
        {
            printf("Invalid epsilon\n");
            return 1;
        }
        else if (get_epsilon(argv[2]) == sc_okay_exp) 
        {
            eps = scientific_notation(argv[2]);
            // printf("%.5f\n", eps);
        }
        else if (get_epsilon(argv[2]) == sc_okay_ord) 
        {
            eps = strtod(argv[2], NULL);
            // printf("%.5f\n", eps);
        }

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

        double eps;
        if (get_epsilon(argv[4]) == sc_error) 
        {
            printf("Invalid epsilon\n");
            return 1;
        }
        else if (get_epsilon(argv[4]) == sc_okay_exp) 
        {
            eps = scientific_notation(argv[4]);
            printf("%.5f\n", eps);
        }
        else if (get_epsilon(argv[4]) == sc_okay_ord) 
        {
            eps = strtod(argv[4], NULL);
            printf("%.5f\n", eps);
        }

        double rem = fabs(a) - fabs((int)(a / b) * b);

        if (rem < eps) 
        {
            printf("Yes\n");
        }
        else 
        {
            printf("No\n");
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

        double eps;
        if (get_epsilon(argv[5]) == sc_error) 
        {
            printf("Invalid epsilon\n");
            return 1;
        }
        else if (get_epsilon(argv[5]) == sc_okay_exp) 
        {
            eps = scientific_notation(argv[5]);
            // printf("%.5f\n", eps);
        }
        else if (get_epsilon(argv[5]) == sc_okay_ord) 
        {
            eps = strtod(argv[5], NULL);
            // printf("%.5f\n", eps);
        }

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
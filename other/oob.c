#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

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

void solutions_to_array(double vec[3], struct Solution* arr, double eps, int* count) {

    double res1, res2;

    if (solve_equation(eps, vec[0], vec[1], vec[2], &res1, &res2) == sc_one_solution) {
        arr[*count].code = 1;
        arr[*count].res1 = res1;
    }
    if (solve_equation(eps, vec[0], vec[1], vec[2], &res1, &res2) == sc_two_solutions) {
        arr[*count].code = 2;
        arr[*count].res1 = res1;
        arr[*count].res2 = res2;
    }
    if (solve_equation(eps, vec[0], vec[1], vec[2], &res1, &res2) == sc_no_solution) {
        arr[*count].code = 0;
    }

    // for (int i = 0; i < 3; i++) {
    //     printf("%.3f ", vec[i]);
    // }
    // printf("\n");
}

void next_permutation(double* vec, double eps, int start, int finish, struct Solution* arr, int* count) {
    if (start == finish) 
    {
        solutions_to_array(vec, arr, eps, count);
        (*count)++;
        return;
    }

    for (int i = start; i < finish; i++) 
    {
        swap(&vec[start], &vec[i]);
        next_permutation(vec, eps, start + 1, finish, arr, count);
        swap(&vec[start], &vec[i]);
    }
}

void selection_sort(double* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size; j++) {
            if (arr[i] < arr[j]) swap(&arr[i], &arr[j]);
        }
    }
}

int main() {
    double initial_array[3] = {-1, 20, -14};

    selection_sort(initial_array , 3);

    for (int i = 0; i < 3; i++) {
        printf("%.2f ", initial_array[i]);
    }

    int size_array = 6;
    struct Solution* solution_array = (struct Solution*)malloc(size_array * sizeof(struct Solution));

    if (solution_array == NULL) 
    {
        printf("Memory allocation failed lol \n");
        return 1;
    }

    int cnt = 0;
    int* count = &cnt;

    next_permutation(initial_array, 0.0001, 0, 3, solution_array, count);

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

    return 0;
}

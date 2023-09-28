#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

typedef long long ll;

double first(double x, double eps) 
{
    double res = exp(x);
    return res;
}

double second(double x, double eps) 
{
    double res = cos(x);
    return res;
}

enum convergence_status_codes
{
    csc_okay, 
    csc_error
};

enum convergence_status_codes third(double x, double eps) // converges only @ |x| <= 1
{   
    if (fabs(x) > 1.0) {

    } 
    double res = 1.0, elem = 1.0, diff = 1.0 + eps, last = 1.0, curr = 2.0, next = 3.0;
    for (int n = 1; elem > eps; n++) 
    {
        elem *= 27 * x * x * n * n * n / (last * curr * next);
        res += elem;
        last += 3, curr += 3, next += 3;
    }
    return res;
}

double fourth(double x, double eps) // converges only @ |x| <= 1
{
    // if (fabs(x) > 1) {
    //     return 
    // }
    double res = 0.0, elem = 1.0, odd = 1.0, even = 2.0;
    for (int n = 1; fabs(elem) > eps; n++) 
    {
        elem *= (-1) * x * x * odd / even;
        res += elem;
        even += 2.0, odd += 2.0;
    }
    return res;
}

int main(int argc, char* argv[]) 
{

    if (argc != 3) 
    {
        printf("Invalid amount of arguments. Usage: %s <integer> <epsilon> \n", argv[0]);
        return 1;
    }

    double x = strtod(argv[1], NULL);
    double eps = strtod(argv[2], NULL);

    printf("Choose the equation: a, b, c or d? \nOr, if you want to output all of them, press z.\n");

    char choice;
    scanf("%c", &choice);

    switch(choice) 
    {
        case 'a':
            printf("%.8f\n", first(x, eps));
            // printf("i work like a dog 7 days a week\n");
            break;
        case 'b':
            printf("%.8f\n", second(x, eps));
            break;
        case 'c':
            printf("%.8f\n", third(x, eps));
            break;
        case 'd':
            printf("%.8f\n", fourth(x, eps));
            break;
        case 'z':
            printf("Equation a: %.8f\n", first(x, eps));
            printf("Equation b: %.8f\n", second(x, eps));
            printf("Equation c: %.8f\n", third(x, eps));
            printf("Equation d: %.8f\n", fourth(x, eps));
            break;
    }

    printf("\n");

    return 0;
}
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

enum convergence_status_codes third(double x, double eps, double* res) 
{
    if (fabs(x) >= 1.0 - eps) 
    {
        return csc_error;
    }
    else 
    {
        double elem = 1.0, last = 1.0, curr = 2.0, next = 3.0;
        for (int n = 1; elem > eps; n++) 
        {
            elem *= 27 * x * x * n * n * n / (last * curr * next);
            *res += elem;
            last += 3, curr += 3, next += 3;
        }
        return csc_okay;
    }
}

enum convergence_status_codes fourth(double x, double eps, double* res) 
{
    if (fabs(x) >= 1.0 - eps) 
    {
        return csc_error;
    }
    else {
        *res = 0;
        double elem = 1.0, odd = 1.0, even = 2.0;
        for (int n = 1; fabs(elem) > eps; n++) 
        {
            elem *= (-1) * x * x * odd / even;
            *res += elem;
            even += 2.0, odd += 2.0;
        }
        printf("Result: %.5f \n", *res);
        return csc_okay;
    }
}

bool is_valid(enum convergence_status_codes code) 
{
    return code == csc_okay ? true : false;
}

bool is_digit(char ch) 
{
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

int main(int argc, char* argv[]) 
{

    if (argc != 3) 
    {
        printf("Invalid amount of arguments. Usage: %s <integer> <epsilon> \n", argv[0]);
        return 1;
    }

    double x = strtod(argv[1], NULL);
    double eps = get_epsilon(argv[2]);

    printf("Choose the equation: a, b, c or d? \n");

    char choice;
    scanf("%c", &choice);

    double res = 1.0;

    switch(choice) 
    {
        case 'a':
            printf("%.10f\n", first(x, eps));
            break;

        case 'b':
            printf("%.10f\n", second(x, eps));
            break;

        case 'c':
            if (is_valid(third(x, eps, &res))) 
            { 
                printf("%.10f\n", res);
            }
            else 
                printf("Error! The series diverges when |x| > 1\n");
            break;

        case 'd':
            if (is_valid(fourth(x, eps, &res)))
            { 
                printf("%.10f\n", res);
            }
            else 
                printf("Error! The series diverges when |x| > 1\n");
            break;
    }

    return 0;
}
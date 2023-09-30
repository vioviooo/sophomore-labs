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
        return csc_okay;
    }
}

bool is_valid(enum convergence_status_codes code) 
{
    return code == csc_okay ? true : false;
}

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

bool check_valid_x(char* ch) {
    int dot_count = 0;
    for (int i = 0; ch[i] != '\0'; i++) {
        if (ch[i] == '.') {
            dot_count++;
        }
        else if (!is_digit(ch[i])) {
            return 0;
        }
    }

    if (dot_count > 1) {
        return 0;
    }

    return 1;
}

int main(int argc, char* argv[]) 
{

    if (argc != 3) 
    {
        printf("Invalid amount of arguments. Usage: %s <integer> <epsilon> \n", argv[0]);
        return 1;
    }

    double x;
    if (check_valid_x(argv[1])) {
        x = strtod(argv[1], NULL);
    }
    else {
        printf("Invalid x.\n");
        return 1;
    }
    
    double eps;
    if (get_epsilon(argv[2]) == sc_error) 
    {
        printf("Invalid epsilon\n");
        return 1;
    }
    else if (get_epsilon(argv[2]) == sc_okay_exp) 
    {
        eps = scientific_notation(argv[2]);
        printf("%.5f\n", eps);
    }
    else if (get_epsilon(argv[2]) == sc_okay_ord) 
    {
        eps = strtod(argv[2], NULL);
        printf("%.5f\n", eps);
    }

    printf("Choose your integral: a, b, c or d? Enter z if you want to output all of them.\n");

    char choice;
    scanf("%c", &choice);

    double res = 1.0;

    switch(choice) 
    {
        case 'a':
            printf("%.10f\n", first(x, eps));
            // printf("i work like a dog 7 days a week\n");
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

        case 'z':
            printf("Equation a: %.10f\n", first(x, eps));
            printf("Equation b: %.10f\n", second(x, eps));

            if (is_valid(third(x, eps, &res))) 
            {
                printf("Equation c: %.10f\n", res);
            }
            else 
                printf("Error! The series diverges when |x| > 1\n");

            if (is_valid(fourth(x, eps, &res))) 
            {
                printf("Equation d: %.10f\n", res);
            }
            else 
                printf("Error! The series diverges when |x| > 1\n");
            break;
    }

    return 0;
}
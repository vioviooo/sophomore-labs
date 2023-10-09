#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

typedef long long ll;

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

typedef double (*foo)(double);

// we can represent integral as a power series
double calc_first(double eps) {
    double res = 1.0, diff = 1.0 + eps, odd = 3, elem = 1.0;
    int sign = 1;
    for (int n = 1; fabs(sign / elem) > eps; n++) {
        elem = fabs(elem) + odd;
        sign *= -1;
        odd += 2;
        res += sign / elem;
    }
    return res;
}

double second_func(double x) 
{
    return exp(-(x * x) / 2);
}

double third_func(double x) {
    return -log(1 - x);
}

double fourth_func(double x) {
    return pow(x, x);
}

double calc_integral(double eps, double up_bound, double low_bound, foo this_function) {
    int n = 1; // Start with n = 1
    double res = 0.0, diff = 1 + eps;
    for (double h = (up_bound - low_bound); h > eps; h /= 2) {
        
        res = 0;
        for (int j = 0; j < n; j++) {
            double x = low_bound + j * h;
            res += this_function(x) * h;
            diff = this_function(x) * h;
        }
        
        n *= 2; // double num of subdiviosons (each time twice more)
    }

    return res;
}

int main(int argc, char* argv[]) 
{
    if (argc != 2) 
    {
        printf("Invalid amount of arguments. Usage: %s <eps>\n", argv[0]);
        return 1;
    }

    double eps;
    if (get_epsilon(argv[1]) == sc_error) 
    {
        printf("Invalid epsilon\n");
        return 1;
    }
    else if (get_epsilon(argv[1]) == sc_okay_exp) 
    {
        eps = scientific_notation(argv[1]);
        printf("%.5f\n", eps);
    }
    else if (get_epsilon(argv[1]) == sc_okay_ord) 
    {
        eps = strtod(argv[1], NULL);
        printf("%.5f\n", eps);
    }

    printf("Choose your integral: a, b, c or d? Enter z if you want to output all of them.\n");

    char choice;
    scanf("%c", &choice);

    double res;

    switch(choice)
    {
        case 'a':
            res = calc_first(eps);
            printf("%.8f\n", res);
            break;
        case 'b':
            res = calc_integral(eps, 1.0, 0.0, second_func);
            printf("%.8f\n", res);
            break;
        case 'c':
            res = calc_integral(eps, 1.0, 0.0, third_func);
            printf("%.8f\n", res);
            break;
        case 'd':
            res = calc_integral(eps, 1.0, 0.0, fourth_func);
            printf("%.8f\n", res);
            break;
        case 'z':
            res = calc_first(eps);
            double res1 = calc_integral(eps, 1.0, 0.0, fourth_func), 
            res2 = calc_integral(eps, 1.0, 0.0, third_func), 
            res3 = calc_integral(eps, 1.0, 0.0, second_func);
            
            printf("First integral: %.8f\nSecond integral: %.8f\nThird integral: %.8f\nFourth integral: %.8f\n", res, res3, res2, res1);

            break;
    }
    
    return 0;
}
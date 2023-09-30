#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

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

int main(int argc, char* argv[]) 
{
    
    if (get_epsilon(argv[1]) == sc_error) 
    {
        printf("Invalid epsilon\n");
        return 1;
    }
    else if (get_epsilon(argv[1]) == sc_okay_exp) 
    {
        double res = scientific_notation(argv[1]);
        printf("%.5f\n", res);
    }
    else if (get_epsilon(argv[1]) == sc_okay_ord) 
    {
        double res = strtod(argv[1], NULL);
        printf("%.5f\n", res);
    }

    return 0;
}

#include "header.h"

void print_scs(int choice);
int find_coefs(double eps, int a, double **res, int power, ...);
int factorial(int n);

int main(void) {

    printf("Welcome! This program will find decomposition of a given polynomial.\n");

    double* res;
    int power = 3;
    int status = find_coefs(1e-6, 1.0, &res, power, 1.0, 2.0, 3.0, 4.0);
    if (status != OK) {
        print_scs(status);
        return status;
    }
    else {
        for (int i = power; i >= 0; i--) {
            printf("Coefs: %.3f\n", res[i]);
        }
    }

    free(res);

    return 0;
}
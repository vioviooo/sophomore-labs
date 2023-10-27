#include "header.h"

void print_scs(int choice);
bool is_overlap(Point points[], int n);
double cross_product(Point p[]);
int is_convex(bool* res, int cnt, ...);
int horner(double* res, double x0, int cnt, ...);

int main(void) {

    printf("Welcome to the program! Choose the desired action:\n");
    printf("1. Check if the figure is a rectangle [no input]\n2. Find power of a certain polynomial at a given point\n");

    int choice;
    if (scanf("%d", &choice) != 1 || getchar() != '\n') {
        print_scs(INVALID_INPUT);
        return INVALID_INPUT;
    }

    switch(choice) {
        case 1: {
            int cnt = 4;
            Point coord1 = {-3.5, -2.5};
            Point coord2 = {-3.5, -6.5};
            Point coord3 = {0.5, -6.5};
            Point coord4 = {0.5, -6.5};
            // Point coord4 = {0.5, -2.5}; // convex
            // Point coord5 = {-2.0, -2.6}; // add this dot => concave

            bool res = 0;
            int status = is_convex(&res, cnt, coord1, coord2, coord3, coord4);

            if (status != OK) {
                print_scs(status);
                exit(status);
            }

            if (res) {
                printf("It is a convex polygon.\n");
            }
            else {
                printf("It's a concave polygon.\n");
            }

            break;
        }
        case 2: {

            double res = 0;

            int power = 0;
            int cnt = power + 1;

            // int status = horner(&res, 2.0 , cnt, 1.0, 3.0, 5.0, 7.0, 9.0);
            int status = horner(&res, 2.0, cnt, 45.0);

            if (status!= OK) {
                print_scs(status);
                return status;
            }

            printf("Result: %f\n", res);

            break;
        }
    }

    return 0;
}
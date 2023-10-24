#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>
#include <complex.h>

typedef long long ll;

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

enum status_codes {
    OK = 1,
    INVALID_INPUT = 2,
    NO_MEMORY = -1,
    INVALID = -2,
    OVERFLOW_ = -3,
    UNDEFINED = -4,
    WARNING_UNUSED = 3,
    WARNING_SMALL = 4,
    OVERLAP = -5
};

void print_scs(int choice) {
    switch(choice) {
        case INVALID_INPUT:
            printf("Invalid input.\n");
            break;
        case OK:
            printf("Project finished successfully\n");
            break;
        case NO_MEMORY:
            printf("No memory left.\n");
            break;
        case INVALID: 
            printf("Invalid something.\n");
            break;
        case OVERFLOW_:
            printf("Overflow!\n");
            break;
        case UNDEFINED:
            printf("Error! What you're trying to calculate IS UNDEFINED or uses complex numbers.\n");
            break;
        case WARNING_UNUSED:
            printf("Warning! Not all input data was used.\n");
            break;
        case WARNING_SMALL:
            printf("Warning! Small values may result in near zero results.\n");
            break;
        case OVERLAP:
            printf("Error! Two or more dots overlap.\n");
            break;
        default:
            break;
    }
}

/////////////////////// struct-related ///////////////////////////

typedef struct {
    double x;
    double y;
} Point;


/////////////////////// validations ///////////////////////////

bool is_valid_double(char ch[]) {
    if (ch[0] == '.' || strlen(ch) == 1 || strlen(ch) == 2) {
        return 0;
    }

    int i;
    if (ch[0] == '-') {
        i = 1;
    } else {
        i = 0;
    }
    
    int cnt_dot = 0;
    for (; ch[i] != '\0'; i++) {
        if (ch[i] == '.') {
            cnt_dot++;
        }
        else {
            if (!isdigit(ch[i])) {
                return 0;
            }
        }
        if (cnt_dot > 1) {
            return 0;
        }
    }

    return 1;
}

// -00000000098980900
// -000000 => 0
bool is_valid_integer(char ch[]) {
    int i = 0;

    if (ch[0] == '-' && ch[1] == '\0') {
        return 0;
    }
    else if (ch[0] == '-') {
        i = 1;
    }

    while (ch[i] == '0') {
        i++;
    }

    int prev = i;
    if (strlen(ch) - i > 9) {
        return 0;
    }

    for (; ch[i] != '\0'; i++) {
        if (!isdigit(ch[i])) {
            return 0;
        }
    }

    return 1;
}   

////////////////////main functions////////////////////////

bool is_overlap(Point points[], int n) {
    double eps = 1.0;
    while (1.0 + eps / 2.0 > 1.0) {
        eps /= 2.0;
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            double x_diff = fabs(points[i].x - points[j].x);
            double y_diff = fabs(points[i].y - points[j].y);
            
            if (x_diff <= eps && y_diff <= eps) {
                return true;
            }
        }
    }
    return false;
}

double cross_product(Point p[]) {
    // Coordinates of vector p[1]p[0]
    double x1 = p[1].x - p[0].x;
    double y1 = p[1].y - p[0].y;

    // Coordinates of vector p[2]p[0]
    double x2 = p[2].x - p[0].x;
    double y2 = p[2].y - p[0].y;

    return (x1 * y2 - y1 * x2);
}

int is_convex(bool* res, int cnt, ...) {
    if (cnt < 3) {
        return INVALID_INPUT;
    }

    Point* points = (Point*)malloc(sizeof(Point) * cnt);
    if (points == NULL) {
        return NO_MEMORY;
    }

    va_list args;
    va_start(args, cnt);

    for (int i = 0; i < cnt; i++) {
        points[i] = va_arg(args, Point);
    }

    if (is_overlap(points, cnt)) {
        return OVERLAP;
    }

    double eps = 1.0;
    while (1.0 + eps / 2.0 > 1.0) {
        eps /= 2.0;
    }

    double prev = 1;
    for (int i = 0; i < cnt; i++) {
        Point tmp[3];
        tmp[0] = points[i];
        tmp[1] = points[(i + 1) % cnt];
        tmp[2] = points[(i + 2) % cnt];
        
        double curr = cross_product(tmp);
        // printf("HERE: %f\n", curr * prev);
        if (curr * prev < 0.0 - eps) {
            *res = false;
            va_end(args);
            free(points);
            return OK;
        }
        else {
            prev = curr;
        }
    }

    *res = true;

    va_end(args);

    free(points);

    return OK;
}

int horner(double* res, double x0, int cnt, ...) {
    if (cnt < 1) {
        return INVALID_INPUT;
    }

    double* vec = (double*)malloc(sizeof(double) * cnt);
    if (vec == NULL) {
        return NO_MEMORY;
    }

    va_list args;
    va_start(args, cnt);

    for (int i = 0; i < cnt; i++) {
        double elem = va_arg(args, double);
        vec[i] = elem;
    }

    // 1 3 5 7 9
    double curr = vec[0], tmp = curr;
    for (int i = 1; i < cnt; i++) {
        curr = vec[i] + tmp * x0;
        tmp = curr;
    }

    *res = tmp;

    va_end(args);

    return OK;
}

int main(void) {

    printf("Welcome to the program! Choose the desired action:\n");
    printf("1. Check if the figure is a rectangle [no input]\n2. Find power of a certain polynomial at a given point\n");

    char ch[BUFSIZ];
    scanf("%s", ch);

    if (strcmp(ch, "1") != 0 && strcmp(ch, "2") != 0) {
        print_scs(INVALID_INPUT);
        return INVALID_INPUT;
    }

    int choice = atoi(ch);

    switch(choice) {
        case 1: {
            int cnt = 4;
            Point coord1 = {-3.5, -2.5};
            Point coord2 = {-3.5, -6.5};
            Point coord3 = {0.5, -6.5};
            Point coord4 = {0.5, -6.5};
            // Point coord4 = {0.5, -2.5}; // convex
            // Point coord5 = {-2.0, -2.6}; // add this dot => concave

            // todo: fix overlap

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
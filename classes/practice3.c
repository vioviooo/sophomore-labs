#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>

typedef long long ll;

double average(int n, ...);

double average(int n, ...) {
    double sum = 0;
    va_list ptr; // синноим для имени типа / typedef / valist и char * одно и то же
    va_start(ptr, n);
    for (int i = 0; i < n; i++) {
        sum += va_arg();
    }
    return sum / n;
};

int main(int argc, char* argv[]) {

    

    return 0;
}

// реализовать fprintf 

// fprintf(stdout, "", 12, malloc(100));

// int fprintf(FILE* _stream, char const * format, ...);
// int printf(char const* _format, ...);
#ifndef STACK_DOUBLE_H
#define STACK_DOUBLE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack_double {
    int top;
    unsigned capacity;
    double *array;
};

struct Stack_double *initStackDouble(unsigned capacity);
int isEmptyStackDouble(struct Stack_double *stack);
double popStackDouble(struct Stack_double *stack);
void pushStackDouble(struct Stack_double *stack, double value);

#endif
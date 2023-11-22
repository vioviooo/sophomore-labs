#include "stack_double.h"

struct Stack_double *initStackDouble(unsigned capacity) {
    struct Stack_double *stack = (struct Stack_double *)malloc(sizeof(struct Stack_double));

    if (!stack) {
        fprintf(stderr, "ERROR: NO MEMORY\n");
        exit(EXIT_FAILURE);
    }

    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (double *)malloc(stack->capacity * sizeof(double));

    if (!stack->array) {
        free(stack);
        fprintf(stderr, "ERROR: NO MEMORY\n");
        exit(EXIT_FAILURE);
    }

    return stack;
}

int isEmptyStackDouble(struct Stack_double *stack) { return stack->top == -1; }

double popStackDouble(struct Stack_double *stack) {
    double flag = 0;
    if (!isEmptyStackDouble(stack)) flag = stack->array[stack->top--];
    return flag;
}

void pushStackDouble(struct Stack_double *stack, double value) { stack->array[++stack->top] = value; }

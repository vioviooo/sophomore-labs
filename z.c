#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum status_codes {
    OK = 0,
    ERROR = -1
};

typedef struct {
    char op;
    int (*operation)(int left_op, int right_op, int* result);
} Operation;

int add(int x, int y, int* res) {
    *res = x + y;
    return OK;
}

int subtract(int x, int y, int* res) {
    *res = x - y;
    return OK;
}

int mult(int x, int y, int* res) {
    *res = x * y;
    return OK;
}

typedef struct {
    int top;
    unsigned capacity;
    int* array;
} Stack;

int init_stack(int capacity, Stack** stack) {
    *stack = (Stack*)malloc(sizeof(Stack)); // Allocate memory for the Stack structure
    if (*stack == NULL) {
        return ERROR;
    }

    (*stack)->array = (int*)malloc(sizeof(int) * capacity);
    if ((*stack)->array == NULL) {
        free(*stack);
        return ERROR;
    }

    (*stack)->top = -1;
    (*stack)->capacity = capacity;

    return OK;
}

int push_stack(Stack** stack, int val) {
    int pos = (*stack)->top + 1;
    if (pos > (*stack)->capacity - 1) {
        // realloc function...
    }
    (*stack)->array[++((*stack)->top)] = val;
    return OK;
}

int pop_stack(Stack** stack) {
    return (*stack)->array[(*stack)->top--];
}

int isOperator(char c) {
    return (c == '-' || c == '+' || c == '*');
}

int evaluatePostfix(char *exp, int* res, ...) {
    Stack *stack = NULL;
    if (init_stack(strlen(exp), &stack) != OK) {
        return ERROR;
    }

    va_list args;
    va_start(args, res);

    for (int i = 0; exp[i]; i++) {
        if (exp[i] >= '0' && exp[i] <= '9') {
            int number = 0;
            while (isdigit(exp[i])) {
                number = number * 10 + (exp[i] - '0');
                i++;
            }
            push_stack(&stack, number);
        } else if (isOperator(exp[i])) {
            int val1 = pop_stack(&stack);
            int val2 = pop_stack(&stack);
            Operation* op = va_arg(args, Operation*);
            int tmp = 0;
            op->operation(val2, val1, &tmp);
            push_stack(&stack, tmp);
        }
    }
    int result = pop_stack(&stack);

    va_end(args);
    free(stack->array);
    free(stack);

    *res = result;

    return OK;
}

int main() {
    int res = 0;

    Operation add_op = { '+', add };
    Operation subtract_op = { '-', subtract };
    Operation mult_op = { '*', mult };

    evaluatePostfix("10 2 +", &res, &add_op);
    printf("Result: %d\n", res);

    res = 0; 

    evaluatePostfix("5 2 -", &res, &subtract_op);
    printf("Result: %d\n", res);

    res = 0;  

    evaluatePostfix("3 2 *", &res, &mult_op);
    printf("Result: %d\n", res);

    return 0;
}

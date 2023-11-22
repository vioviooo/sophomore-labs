#include "graph.h"

#include <stdbool.h>

#include "stack.h"
#include "stack_double.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("ERROR: TOO FEW ARGUMENTS");
        exit(1);
    }

    int i = 1;
    while (argv[i] != NULL) {
        printf("%d. %s\n", i, argv[i]);

        FILE *fptr = fopen(argv[i], "r");
        if (fptr == NULL) {
            printf("ERROR: CAN'T OPEN FILE");
            i++;
            continue;
        }

        char *infix_expression = NULL;
        int flag = 0, count = 1;
        while ((count = input(fptr, &infix_expression))) {
            if (!validateInfixExpression(infix_expression)) {
                flag = 1;
            }

            char *postfix_expression = (char *)malloc((count + 1) * sizeof(char));
            if (postfix_expression == NULL) {
                printf("ERROR: NO MEMORY\n");
                free(infix_expression);
                exit(1);
            }
            postfix_expression[count] = '\0';

            int div = 0;
            if (flag == 0) {
                infixToPostfix(infix_expression, postfix_expression);
                printf("%s\n", infix_expression);
                printf("%s\n", postfix_expression);
                double res = evaluatePostfix(postfix_expression, &div);
                if (div) {
                    printf("ERROR: DIVISION BY 0\n");
                } else {
                    printf("~Result: %.3f\n", res);
                }
            }

            free(postfix_expression);
            free(infix_expression);
            infix_expression = NULL;
        }
        fclose(fptr);
        i++;
    }

    return 0;
}

int validateInfixExpression(char *infix) {
    int i = 0;
    while (infix[i] != '\0') {
        if (isDigit(infix[i])) {
            if (isDigit(infix[i + 1]) ||
                (!isOperator(infix[i + 1]) && infix[i + 1] != ')' && infix[i + 1] != '\0')) {
                printf("ERROR: INCORRECT STATEMENT\n");
                return 0;
            }
        } else if (isOperator(infix[i])) {
            if ((!isDigit(infix[i + 1]) && infix[i + 1] != '(') || infix[i + 1] == '\0') {
                printf("ERROR: INCORRECT STATEMENT\n");
                return 0;
            }
        } else if (strchr("0123456789/+-*^()\n", infix[i]) == NULL && infix[i] != '%') {
            printf("ERROR: INCORRECT STATEMENT\n");
            return 0;
        }
        i++;
    }
    if (!areParenthesesBalanced(infix)) {
        printf("ERROR: UNBALANCED PARENTHESES\n");
        return 0;
    }
    return 1;
}

int input(FILE *fptr, char **infix_expression) {
    int i = 0, capacity = 2;
    *infix_expression = (char *)malloc(capacity * sizeof(char));
    if (*infix_expression == NULL) {
        printf("ERROR: NO MEMORY");
        return 0;
    }

    while (true) {
        if (i >= capacity - 1) {
            capacity *= 2;
            char *tmp = (char *)realloc(*infix_expression, capacity * sizeof(char));
            if (tmp == NULL) {
                free(*infix_expression);
                *infix_expression = NULL;
                printf("ERROR: NO MEMORY");
                return 0;
            }
            *infix_expression = tmp;
        }

        char ch = fgetc(fptr);
        if (ch == '\n' || ch == ' ' || ch == EOF) break;

        (*infix_expression)[i] = ch;

        i++;
    }

    (*infix_expression)[i] = '\0';

    return i;
}

int isOperator(char c) { return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%'); }

int getPrecedence(char c) {
    int flag = 0;
    if (c == '+' || c == '-')
        flag = 1;
    else if (c == '*' || c == '/' || c == '%')
        flag = 2;
    else if (c == '^')
        flag = 3;
    else if (c == '(' || c == ')')
        flag = 0;
    return flag;
}

void infixToPostfix(char *infix, char *postfix) {
    object *stack = NULL;
    int i = 0, j = 0;
    while (infix[i] != '\0') {
        if (infix[i] >= '0' && infix[i] <= '9') {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            stack = push(stack, '(');
        } else if (infix[i] == ')') {
            while (stack != NULL && stack->oper != '(') {
                postfix[j++] = stack->oper;
                stack = pop(stack);
            }
            if (stack != NULL && stack->oper == '(') {
                stack = pop(stack);
            }
        } else if (isOperator(infix[i])) {
            if (infix[i] == '-' && (i == 0 || isOperator(infix[i - 1]) || infix[i - 1] == '(')) {
                postfix[j++] = '0';
                stack = push(stack, '-');
            } else {
                while (stack != NULL && getPrecedence(stack->oper) >= getPrecedence(infix[i])) {
                    postfix[j++] = stack->oper;
                    stack = pop(stack);
                }
                stack = push(stack, infix[i]);
            }
        }
        i++;
    }
    while (stack != NULL) {
        postfix[j++] = stack->oper;
        stack = pop(stack);
    }
    postfix[j] = '\0';
    destroy(stack);
}

double evaluatePostfix(char *exp, int *div) {
    struct Stack_double *stack = initStackDouble(strlen(exp));
    double result = 0;
    if (!stack) {
        result = -1;
    }
    for (int i = 0; exp[i]; i++) {
        if (exp[i] >= '0' && exp[i] <= '9') {
            pushStackDouble(stack, (double)(exp[i] - '0'));
        } else {
            double val1 = popStackDouble(stack);
            double val2 = popStackDouble(stack);
            if (exp[i] == '+')
                pushStackDouble(stack, val2 + val1);
            else if (exp[i] == '-')
                pushStackDouble(stack, val2 - val1);
            else if (exp[i] == '*')
                pushStackDouble(stack, val2 * val1);
            else if (exp[i] == '/') {
                if (val1 == 0) {
                    *div = 1;
                    result = NAN;
                    break;
                } else {
                    pushStackDouble(stack, val2 / val1);
                }
            } else if (exp[i] == '^') {
                pushStackDouble(stack, pow(val2, val1));
            } else if (exp[i] == '%') {
                pushStackDouble(stack, (int)val2 % (int)val1);
            }
        }
    }

    if (!isnan(result)) {
        result = popStackDouble(stack);
    }

    free(stack->array);
    free(stack);
    return result;
}

int isDigit(char c) { return c >= '0' && c <= '9'; }

int areParenthesesBalanced(char *exp) {
    int flag = 1;
    object *stack = NULL;
    for (int i = 0; exp[i]; i++) {
        if (exp[i] == '(') {
            stack = push(stack, exp[i]);
        } else if (exp[i] == ')') {
            if (stack == NULL || stack->oper != '(') flag = 0;
            stack = pop(stack);
        }
    }
    if (stack != NULL) flag = 0;

    while (stack != NULL) {
        stack = pop(stack);
    }
    return flag;
}

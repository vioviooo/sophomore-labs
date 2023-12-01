#ifndef MAIN_H
#define MAIN_H
#include <math.h>
#include <stdio.h>
#include <string.h>

int validateInfixExpression(char *infix);
int input(FILE *fptr, char **infix_expression);
int isOperator(char c);
int getPrecedence(char c);
void infixToPostfix(char *infix, char *postfix);
double evaluatePostfix(char *exp, int *div);
int isDigit(char c);
int areParenthesesBalanced(char *exp);

#endif
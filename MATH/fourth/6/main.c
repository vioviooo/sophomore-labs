#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "stack.h"

// Structure for a tree node
typedef struct TreeNode {
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Function to check if a character is an operand
int isOperand(char c) { return (c == '0' || c == '1'); }

// Function to create a new tree node
TreeNode *createNode(char data) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        printf("ERROR: Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to build a binary expression tree from a postfix expression
TreeNode *buildExpressionTree(char postfix[]) {
    TreeNode *stack[100];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; ++i) {
        TreeNode *newNode = createNode(postfix[i]);

        if (isOperand(postfix[i])) {
            stack[++top] = newNode;
        } else {
            newNode->right = stack[top--];
            newNode->left = stack[top--];
            stack[++top] = newNode;
        }
    }

    return stack[top];
}

// Function to evaluate an expression tree
int evaluateExpressionTree(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    if (isOperand(root->data)) {
        return root->data - '0';
    }

    int leftValue = evaluateExpressionTree(root->left);
    int rightValue = evaluateExpressionTree(root->right);

    switch (root->data) {
        case '&':
            return leftValue && rightValue;  // good
        case '|':
            return leftValue || rightValue;  // good
        case '~':
            return !rightValue;  // good
        case '-':
            return !leftValue || rightValue;  // good
        case '+':
            return leftValue && !rightValue;  // good
        case '<':
            return leftValue ^ rightValue;  // good
        case '=':
            return leftValue == rightValue;  // good
        case '!':
            return !(leftValue && rightValue);  // good
        case '?':
            return !(leftValue || rightValue);  // good
        default:
            return false;
    }
}

void generateTruthTable(TreeNode* root, char* variables, int numVariables);

int isOperator(char c) { return (c == '+' || c == '-' || c == '<' || c == '=' || c == '|' || c == '~' || c == '!' || c == '?' || c == '&'); }

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

int getPrecedence(char c) {
    int flag = 0;
    if (c == '|' || c == '-' || c == '<' || c == '=')
        flag = 1;
    else if (c == '?' || c == '!' || c == '+' || c == '&')
        flag = 2;
    else if (c == '~')
        flag = 3;
    else if (c == '(' || c == ')')
        flag = 0;
    return flag;
}

void infixToPostfix(char *infix, char *postfix) {
    object *stack = NULL;
    int i = 0, j = 0;
    while (infix[i] != '\0') {
        if (infix[i] == '0' || infix[i] == '1' || isalpha(infix[i])) {
            postfix[j++] = infix[i];
        } else if (infix[i] == '-' && infix[i + 1] == '>') {
            stack = push(stack, '-');
            i += 2;
        } else if (infix[i] == '+' && infix[i + 1] == '>') {
            stack = push(stack, '+');
            i += 2;
        } else if (infix[i] == '<' && infix[i + 1] == '>') {
            stack = push(stack, '<');
            i += 2;
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
            if (infix[i] == '~' && (i == 0 || isOperator(infix[i - 1]) || infix[i - 1] == '(')) {
                postfix[j++] = '0';
                stack = push(stack, '~');
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

void freeTree(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

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
        count = input(fptr, &infix_expression);
        // if (!validateInfixExpression(infix_expression)) {
        //     flag = 1;
        // }

        char *postfix_expression = (char *)malloc((count + 1) * sizeof(char));
        if (postfix_expression == NULL) {
            printf("ERROR: NO MEMORY\n");
            free(infix_expression);
            exit(1);
        }
        postfix_expression[count] = '\0';

        if (flag == 0) {
            infixToPostfix(infix_expression, postfix_expression);
            printf("%s\n", infix_expression);
            printf("%s\n", postfix_expression);
            
            TreeNode* root = buildExpressionTree(postfix_expression);

            printf("Expression Tree built successfully!\n");

            int result = evaluateExpressionTree(root);

            printf("Result of the expression: %d\n", result);

            freeTree(root);
        }
        free(postfix_expression);
        free(infix_expression);
        fclose(fptr);
        i++;
    }

    return 0;
}
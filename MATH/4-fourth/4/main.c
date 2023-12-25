#include "main.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

#define ENG_ALPHABET 26

typedef struct Node {
    char data;
    struct Node *left;
    struct Node *right;
} Node;

enum status_codes {
    OK = 0,
    NO_MEMORY = -1,
    INVALID_INFIX = 2,
    UNBALANCED_BRACKETS = 3,
    EMPTY_FILE = -2,
    INVALID_INPUT = -3,
    FILE_NOT_OPEN = -4,
    INVALID_BASE = -5
};

char* return_scs(int choice) {
    switch (choice) {
        case INVALID_INFIX:
            return ("ERROR: INVALID INFIX EXPRESSION\n");
        case OK:
            return ("Project finished successfully!\n");
        case NO_MEMORY:
            return ("ERROR: NO MEMORY\n");
        case UNBALANCED_BRACKETS:
            return ("ERROR: UNBALANCED PARENTHESES\n");
        case EMPTY_FILE:
            return ("NOTICE: EMPTY FILE\n");
        case INVALID_INPUT:
            return ("ERROR: INVALID INPUT\n");
        case FILE_NOT_OPEN:
            return ("ERROR: FILE WAS NOT OPEN\n");
        case INVALID_BASE:
            return ("ERROR: INVALID BASE\n");
        default:
            break;
    }
    return NULL;
}

void print_scs(int choice) {
    switch (choice) {
        case INVALID_INFIX:
            printf("\nERROR: INVALID INFIX EXPRESSION\n");
            break;
        case OK:
            printf("\nProject finished successfully!\n");
            break;
        case NO_MEMORY:
            printf("\nERROR: NO MEMORY\n");
            break;
        case UNBALANCED_BRACKETS:
            printf("\nERROR: UNBALANCED PARENTHESES\n");
            break;
        case EMPTY_FILE:
            printf("\nNOTICE: EMPTY FILE\n");
            break;
        case INVALID_INPUT:
            printf("\nERROR: INVALID INPUT\n");
            break;
        case FILE_NOT_OPEN:
            printf("\nERROR: FILE WAS NOT OPEN\n");
            break;
        case INVALID_BASE:
            printf("\nERROR: INVALID BASE\n");
            break;
        default:
            break;
    }
}

int isOperand(char c) { return (c == '0' || c == '1'); }

Node *createNode(char data) {
    Node *newNode = (Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("ERROR: Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node *buildExpressionTree(char postfix[]) {
    Node *stack[BUFSIZ];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; ++i) {
        Node *newNode = createNode(postfix[i]);

        if (isOperand(postfix[i]) || isalpha(postfix[i])) {
            stack[++top] = newNode;
        } else {
            newNode->right = stack[top--];
            newNode->left = stack[top--];
            stack[++top] = newNode;
        }
    }

    return stack[top];
}

int evaluateExpressionTree(Node *root, int variables[]) {
    if (root == NULL) {
        return 0;
    }

    if (isOperand(root->data)) {
        return root->data - '0';
    }
    else if (isalpha(root->data)) {
        return variables[tolower(root->data) - 'a'];
    }

    int leftValue = evaluateExpressionTree(root->left, variables);
    int rightValue = evaluateExpressionTree(root->right, variables);

    switch (root->data) {
        case '&':
            return (leftValue & rightValue);
        case '|':
            return (leftValue | rightValue);
        case '~':
            return ~rightValue;
        case '-':
            return ~leftValue | rightValue;
        case '+':
            return (leftValue & ~rightValue);
        case '<':
            return (leftValue ^ rightValue);
        case '=':
            return (leftValue == rightValue);
        case '!':
            return ~leftValue & ~rightValue;
        case '?':
            return ~(leftValue | rightValue);
        default:
            return false;
    }
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '<' || c == '=' || c == '|' || c == '~' || c == '!' || c == '?' ||
            c == '&');
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
            i += 1;
        } else if (infix[i] == '+' && infix[i + 1] == '>') {
            stack = push(stack, '+');
            i += 1;
        } else if (infix[i] == '<' && infix[i + 1] == '>') {
            stack = push(stack, '<');
            i += 1;
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

void inorderTraversal(Node *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%c ", root->data);
        inorderTraversal(root->right);
    }
}

void freeTree(Node *root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

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

int validateInfixExpression(char *infix) {
    int i = 0;
    while (infix[i] != '\0') {
        if (isOperand(infix[i]) || isalpha(infix[i])) {
            if (isOperand(infix[i + 1]) ||
                (!isOperator(infix[i + 1]) && infix[i + 1] != ')' && infix[i + 1] != '\0')) {
                return INVALID_INFIX;
            }
        } else if (isOperator(infix[i])) {
            if ((infix[i] == '-' || infix[i] == '+' || infix[i] == '<') && infix[i + 1] != '>') {
                return INVALID_INFIX;
            } else if ((!(infix[i] == '-' || infix[i] == '+' || infix[i] == '<') &&
                        !isOperand(infix[i + 1]) && !isalpha(infix[i + 1]) && infix[i + 1] != '(') ||
                       infix[i + 1] == '\0') {
                return INVALID_INFIX;
            }
        } else if (strchr("01&|~-+><!?()\n", infix[i]) == NULL && !isalpha(infix[i])) {
            return INVALID_INFIX;
        }
        i++;
    }
    if (i == 0) {
        return EMPTY_FILE;
    }
    if (!areParenthesesBalanced(infix)) {
        return UNBALANCED_BRACKETS;
    }
    return OK;
}

int to_10(char *num_base, int base, int *res) {
	char *ptr = num_base - 1;
	int sign = 1;

	if (*num_base == '-') {
		ptr++;
		sign = -1;
	}

	while (*++ptr) {
		*res = *res * base + ((isdigit(*ptr)) ? (*ptr - '0') : (*ptr - 'A' + 10));
 	}

 	*res = sign * *res;

 	return OK;
}

int to_base(int num, int base, char **res) {
	char buff[BUFSIZ];
	char *ptr = buff + BUFSIZ - 1;
	int sign = 1;
	*ptr = 0;
	ptr--;

	if (num < 0) {
		num = abs(num);
		sign = -1;
	}

	while (num) {
		*ptr-- = num % base < 10 ? num % base + '0' : num % base + 'A' - 10;
		num /= base;
	}

	if (sign < 0) {
		*ptr = '-';
	} else {
		ptr++;
	}

	*res = (char*)malloc(sizeof(char) * (strlen(ptr) + 1));

	if (!*res) {
		return NO_MEMORY;
	}

	strcpy(*res, ptr);

	return OK;
}

int read_var(char* line, int variables[], char input[], char comment[]) {
    int i = 0;
    while (line[i] != '(') {
        i++;
    }
    i++;

    char c = line[i];

    i += 2;

    char ch[20];
    int j = 0;
    while (line[i] != ')') {
        ch[j] = line[i];
        i++;
        j++;
    }
    ch[j] = '\0';

    i += 2;

    if (strstr(line, "%") != NULL) {
        while (line[i] != '%') {
            if (line[i] != ' ') {
                return INVALID_INPUT;
            }
            i++;
        }
        j = 0;
        while (line[i] != '\n' && line[i] != '\0' && line[i] != EOF) {
            comment[j] = line[i];
            i++;
            j++;
        }
        comment[j] = '\0';   
    }

    while (line[i] != '\0' && line[i] != '\n') {
        if (line[i] != ' ') {
            return INVALID_INPUT;
        }
        i++;
    }

    int base = atoi(ch);
    if (base <= 0 || base > 36) {
        return INVALID_BASE;
    }

    int res = 0;
    to_10(input, base, &res);

    variables[(int)tolower(c) - 97] = res;

    return OK;
}

int write_var(char* line, int variables[], char* comment) {
    int i = 0;
    while (line[i] != '(') {
        i++;
    }
    i++;

    char c = line[i];

    i += 2;

    char ch[20];
    int j = 0;
    while (line[i] != ')') {
        ch[j] = line[i];
        i++;
        j++;
    }
    ch[j] = '\0';

    i += 2;

    if (strstr(line, "%") != NULL) {
        while (line[i] != '%') {
            if (line[i] != ' ') {
                return INVALID_INPUT;
            }
            i++;
        }
        j = 0;
        while (line[i] != '\n' && line[i] != '\0' && line[i] != EOF) {
            comment[j] = line[i];
            i++;
            j++;
        }
        comment[j] = '\0';   
    }

    while (line[i] != '\0' && line[i] != '\n') {
        if (line[i] != ' ') {
            return INVALID_INPUT;
        }
        i++;
    }

    int base = atoi(ch);
    if (base <= 0 || base > 36) {
        return INVALID_BASE;
    }

    char* res;
    to_base(variables[(int)tolower(c) - 97], base, &res);

    printf("Program output:: %c in base %d: %s\n", c, base, res);

    return OK;
}

int calc_var(char* line, int variables[], char* comment) {
    int i = 0;

    while (!isalpha(line[i])) {
        i++;
    }
    char c = line[i];

    i += 3;

    char infix_expression[BUFSIZ];
    int j = 0;
    while (line[i] != '\0' && line[i] != ';') {
        infix_expression[j] = line[i];
        i++;
        j++;
    }
    infix_expression[j] = '\0';

    if (strstr(line, "%") != NULL) {
        while (line[i] != '%') {
            i++;
        }
        int k = 0;
        while (line[i] != '\n' && line[i] != '\0' && line[i] != EOF) {
            comment[k] = line[i];
            i++;
            k++;
        }
        comment[k] = '\0';   
    }

    int status;
    if ((status = validateInfixExpression(infix_expression)) != OK) {
        return status;
    } else {
        char *postfix_expression = (char *)malloc((j + 1) * sizeof(char));
        if (postfix_expression == NULL) {
            return NO_MEMORY;
        }

        infixToPostfix(infix_expression, postfix_expression);
        // printf("Infix:   %s\n", infix_expression);
        // printf("Postfix: %s\n", postfix_expression);

        Node *root = buildExpressionTree(postfix_expression);

        int result = evaluateExpressionTree(root, variables);

        variables[(int)tolower(c) - 97] = result;

        freeTree(root);

        free(postfix_expression);
    }

    return OK;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("ERROR: TOO FEW ARGUMENTS");
        return 1;
    }

    int names[ENG_ALPHABET + 1];
    for (int j = 0; j < ENG_ALPHABET; j++) {
        names[j] = 0;
    }

    FILE *fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        print_scs(FILE_NOT_OPEN);
        return FILE_NOT_OPEN;
    }

    FILE *fptr_out = fopen("out.txt", "w");
    if (argc == 4 && strcmp(argv[2], "/trace") == 0) {
        fclose(fptr_out);
        fptr_out = fopen(argv[3], "w");
    }

    int status, cnt = 0;
    char line[BUFSIZ];
    while (fgets(line, sizeof(line), fptr) != NULL) {
        cnt++;
        char comment[BUFSIZ];
        comment[0] = '\0';
        if (strstr(line, "read") != NULL) {
            char input_val[BUFSIZ];
            char comm[BUFSIZ];
            comm[0] = '\0';
            fgets(input_val, sizeof(input_val), fptr);
            if (strstr(input_val, "%") == NULL) {
                input_val[strcspn(input_val, "\n")] = '\0';
                read_var(line, names, input_val, comment);
            } else {
                int i = 0;
                char input[BUFSIZ];
                while (input_val[i] != '%' && input_val[i] != ' ') {
                    input[i] = input_val[i];
                    i++;
                }
                input[i] = '\0';

                while (input_val[i] != '%') {
                    i++;
                }

                int k = 0;
                while (input_val[i] != '\0' && input_val[i] != '\n' && input_val[i] != EOF) {
                    comm[k] = input_val[i];
                    k++;
                    i++;
                }
                comm[k] = '\0';

                read_var(line, names, input, comment);
            }
            if (comment[0] != '\0') {
                fprintf(fptr_out, "line = %d, %s\n", cnt, comment);
            }
            cnt++;
            if (comm[0] != '\0') {
                fprintf(fptr_out, "line = %d, %s\n", cnt, comm);
            }
        }
        else if (strstr(line, "write") != NULL) {
            if ((status = write_var(line, names, comment)) != OK) {
                fprintf(fptr_out, "line = %d, %s", cnt, return_scs(status));
                print_scs(status);
            }
            if (comment[0] != '\0') {
                fprintf(fptr_out, "line = %d, %s\n", cnt, comment);
            }
        }
        else if (strstr(line, ":=") != NULL) {
            if ((status = calc_var(line, names, comment)) != OK) {
                fprintf(fptr_out, "line = %d, %s", cnt, return_scs(status));
                print_scs(status);
            }
            if (comment[0] != '\0') {
                fprintf(fptr_out, "line = %d, %s\n", cnt, comment);
            }
        }
        else if (strstr(line, "%") != NULL) {
            fprintf(fptr_out, "line = %d, %s", cnt, line);
        }
        else if (strstr(line, "{") != NULL) {
            fprintf(fptr_out, "line = %d, %s", cnt, line);
            cnt++;
            while (strstr(line, "}") == NULL) {
                fgets(line, sizeof(line), fptr);
                fprintf(fptr_out, "line = %d, %s", cnt, line);
                cnt++;
            }
        }
        else {
            fprintf(fptr_out, "line = %d, %s", cnt, return_scs(INVALID_INFIX));
        }
    }
    
    fclose(fptr);
    fclose(fptr_out);

    return OK;
}

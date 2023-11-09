#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(char data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode) {
        newNode->data = data;
        newNode->left = newNode->right = NULL;
    }
    return newNode;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

void buildExpressionTree(TreeNode** root, char* expression, int* index) {
    if (expression[*index] == '(') {
        (*index)++; // Skip the opening parenthesis
        *root = createNode(expression[*index]);
        (*index)++; // Move to the next character

        if (isOperator((*root)->data)) {
            buildExpressionTree(&(*root)->left, expression, index);
            buildExpressionTree(&(*root)->right, expression, index);
        }
    } else {
        // If it's not an opening parenthesis, it's an operand or a closing parenthesis
        while (expression[*index] != ',' && expression[*index] != ')' && expression[*index] != '\0') {
            (*index)++;
        }
    }

    if (expression[*index] == ',') {
        (*index)++;
    }

    if (expression[*index] == ')') {
        (*index)++; // Skip the closing parenthesis
    }
}

void printExpressionTree(TreeNode* root) {
    if (root) {
        if (isOperator(root->data)) {
            printf("(");
        }
        printExpressionTree(root->left);
        printf("%c", root->data);
        printExpressionTree(root->right);
        if (isOperator(root->data)) {
            printf(")");
        }
    }
}

void freeExpressionTree(TreeNode* root) {
    if (root) {
        freeExpressionTree(root->left);
        freeExpressionTree(root->right);
        free(root);
    }
}

int main() {
    char expression[] = "A (B (E (G, T, R (W, Z)), F (L, M)), C)";
    int index = 0;
    TreeNode* root = NULL;

    buildExpressionTree(&root, expression, &index);
    printf("Expression tree: ");
    printExpressionTree(root);
    printf("\n");

    freeExpressionTree(root);

    return 0;
}

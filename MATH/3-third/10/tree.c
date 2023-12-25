#include "header.h"

struct Node {
    char data;
    int child_cnt;
    struct Node** children; // there can be more than 2 children
};

struct Node* add_node(char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->child_cnt = 0;
    newNode->children = NULL;
    return newNode;
}

void add_child(struct Node* parent, struct Node* child) {
    struct Node** tmp = realloc(parent->children, (parent->child_cnt + 1) * sizeof(struct Node*));
    if (tmp == NULL) {
        free(parent->children);
        parent->children = NULL;
        return;
    }

    parent->children = tmp;
    parent->children[parent->child_cnt] = child;
    parent->child_cnt++;
}

void print_tree(struct Node* root, int level, FILE* fptr) {
    if (root != NULL) {
        for (int i = 0; i < level; i++) {
            fprintf(fptr, "   ");
        }
        fprintf(fptr, "|--%c\n", root->data);

        for (int i = 0; i < root->child_cnt; i++) {
            print_tree(root->children[i], level + 1, fptr);
        }
    }
}

void free_tree(struct Node* root) {
    if (root != NULL) {
        for (int i = 0; i < root->child_cnt; i++) {
            free_tree(root->children[i]);
        }
        free(root->children);
        free(root);
    }
}

struct Node* bracket_to_tree(char* sequence) {
    struct Node* root = add_node(sequence[0]);
    struct Node* node;
    struct Node* curr = root;
    struct Node** my_nodes = (struct Node**)malloc(strlen(sequence) * sizeof(struct Node*));
    if (*my_nodes == NULL) {
        return NULL;
    }
    int cnt_node = 0, len = strlen(sequence);
    for (int i = 0; i < len; i++) {
        if (sequence[i] == '(') {
            node = add_node(sequence[i + 1]);
            my_nodes[cnt_node] = curr;
            cnt_node++;
            add_child(curr, node);
            curr = node;
        } else if (sequence[i] == ',') {
            node = add_node(sequence[i + 1]);
            add_child(my_nodes[cnt_node - 1], node);
            curr = node;
        } else if (sequence[i] == ')') {
            my_nodes[cnt_node - 1] = NULL;
            cnt_node--;
        }
    }

    free(my_nodes);
    
    return root;
}
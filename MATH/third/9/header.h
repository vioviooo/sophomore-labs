#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>
#include <ncurses.h>
#include <complex.h>

typedef struct Node {
    char *word;
    int count;
    struct Node *left, *right;
} Node;

enum status_codes {
    OKAY = 1,
    ERROR = -2,
    INVALID_INPUT = 2,
    INVALID_INPUT_FILE = -6,
    NO_MEMORY = -1,
    OVERFLOW_ = -3,
    UNDEFINED = -4,
    FILE_NOT_OPEN = -5
};

Node* create_node(char* word);
Node* insert_word(Node* root, char* word);
Node* extract_tree(Node* root, char* word, int count);
void print_all_frequency(Node *root);
int cnt_frequency(Node* root, char* word);
void free_bst(Node* root);
void find_longest_word(Node *root, char **longest);
void find_shortest_word(Node *root, char **shortest);
void preorder_dfs(Node *root, FILE* fptr);
int is_valid_char(char ch[]);
bool is_valid_integer(char ch[]);

#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *word;
    int count;
    struct Node *left, *right;
} Node;

void print_all_frequency(Node *root) {
    if (root != NULL) {
        print_all_frequency(root->left);
        printf("String: %s ", root->word);
        printf(" Frequency: %d\n", root->count);
        print_all_frequency(root->right);
    }
}

Node* create_node(char* word);
Node* insert_word(Node* root, char* word);
int cnt_frequency(Node* root, char* word);
void free_bst(Node* root);
void find_longest_word(Node *root, char **longest);
void find_shortest_word(Node *root, char **shortest);
void preorder_dfs(Node *root);

// int main() {
//     Node* root = NULL;

//     // Insert words into the BST
//     root = insert_word(root, "ss");
//     root = insert_word(root, "paple");
//     root = insert_word(root, "banana");
//     root = insert_word(root, "apple");
//     root = insert_word(root, "oongaboonga");

//     // Find occurrences of words
//     printf("Occurrences of 'apple': %d\n", cnt_frequency(root, "app"));
//     printf("Occurrences of 'orange': %d\n", cnt_frequency(root, "orange"));
//     printf("Occurrences of 'banana': %d\n", cnt_frequency(root, "banana"));
//     printf("Occurrences of 'grape': %d\n", cnt_frequency(root, "grape"));

//     char* shortest = "";
//     char* longest = "";
//     find_longest_word(root, &longest);

//     printf("ll: %s sh: %s", longest, shortest);

//     free_bst(root);

//     return 0;
// }
void find_shortest_word(Node *root, char **shortest) {
    if (root == NULL) {
        return;
    }

    find_shortest_word(root->left, shortest);

    // Check if the current word is shorter than the previously found shortest word
    if (*shortest == NULL || strlen(root->word) < strlen(*shortest)) {
        *shortest = root->word;
    }

    find_shortest_word(root->right, shortest);
}


void find_longest_word(Node *root, char **longest) {
    if (root == NULL) {
        return;
    }

    // Traverse the right subtree first
    find_longest_word(root->right, longest);

    // Check if the current word is longer than the previously found longest word
    if (strlen(root->word) > strlen(*longest)) {
        *longest = root->word;
    }

    // Traverse the left subtree
    find_longest_word(root->left, longest);
}

Node* create_node(char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->word = strdup(word);
    newNode->count = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert_word(Node* root, char* word) {
    if (root == NULL) {
        return create_node(word);
    }

    int cmp = strcmp(word, root->word);

    if (cmp < 0) {
        root->left = insert_word(root->left, word);
    } else if (cmp > 0) {
        root->right = insert_word(root->right, word);
    } else {
        root->count++; // word exists => increase cnt
    }

    return root;
}

void free_bst(Node* root) {
    if (root == NULL) {
        return;
    }

    free_bst(root->left);
    free_bst(root->right);

    free(root->word);
    free(root);
}

int cnt_frequency(Node* root, char* word) {
    if (root == NULL) {
        return 0;
    }

    int cmp = strcmp(word, root->word);

    if (cmp < 0) {
        return cnt_frequency(root->left, word);
    } else if (cmp > 0) {
        return cnt_frequency(root->right, word);
    } else {
        return root->count;
    }
}

void preorder_dfs(Node *root) {
    if (root != NULL) {
        // visit the current node
        printf("%s (%d)\n", root->word, root->count);

        // visit the left subtree
        preorder_dfs(root->left);

        // visit the right subtree
        preorder_dfs(root->right);
    }
}

/////////////////

#include "header.h"

void print_all_frequency(Node *root) {
    if (root != NULL) {
        print_all_frequency(root->left);
        printf("String: %s ", root->word);
        printf(" Frequency: %d\n", root->count);
        print_all_frequency(root->right);
    }
}

void find_shortest_word(Node *root, char **shortest) {
    if (root == NULL) {
        return;
    }

    find_shortest_word(root->left, shortest);

    if (*shortest == NULL || strlen(root->word) < strlen(*shortest)) {
        *shortest = root->word;
    }

    find_shortest_word(root->right, shortest);
}


void find_longest_word(Node *root, char **longest) {
    if (root == NULL) {
        return;
    }
    find_longest_word(root->right, longest);
    // is longer?
    if (strlen(root->word) > strlen(*longest)) {
        *longest = root->word;
    }
    find_longest_word(root->left, longest);
}

Node* create_node(char* word) {
    Node* new_node = (Node*)malloc(sizeof(Node));

    new_node->word = strdup(word);
    new_node->count = 1;
    new_node->left = new_node->right = NULL;

    return new_node;
}

Node* insert_word(Node* root, char* word) {
    if (root == NULL) {
        return create_node(word);
    }

    int cmp = strcmp(word, root->word);

    if (cmp < 0) {
        root->left = insert_word(root->left, word);
    } 
    else if (cmp > 0) {
        root->right = insert_word(root->right, word);
    } 
    else {
        root->count++; // word exists => increase cnt
    }

    return root;
}

Node* extract_tree(Node* root, char* word, int count) {
    if (root == NULL) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->word = strdup(word);
        new_node->count = count;
        new_node->left = new_node->right = NULL;
        return new_node;  // Return the newly created node
    }

    int cmp = strcmp(word, root->word);

    if (cmp < 0) {
        root->left = extract_tree(root->left, word, count);
    } 
    else if (cmp > 0) {
        root->right = extract_tree(root->right, word, count);
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
    } 
    else if (cmp > 0) {
        return cnt_frequency(root->right, word);
    } 
    else {
        return root->count;
    }
}

void preorder_dfs(Node *root, FILE* fptr) {
    if (root != NULL) {
        preorder_dfs(root->left, fptr);
        fprintf(fptr, "%s %d\n", root->word, root->count);
        preorder_dfs(root->right, fptr);
    }
}

int find_height(Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        int height_l = find_height(root->left);
        int height_r = find_height(root->right);

        return (height_l > height_r) ? (height_l + 1) : (height_r + 1);
    }
}

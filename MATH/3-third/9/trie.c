#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// since there are only 26 letters in the Eng alphabet
#define N 26

typedef struct TrieNode TrieNode;

struct TrieNode {
    char data;
    int is_leaf;
    int count;
    TrieNode* children[N];
};

TrieNode* make_trienode(char data) {
    TrieNode* node = (TrieNode*)calloc(1, sizeof(TrieNode));
    for (int i = 0; i < N; i++) {
        node->children[i] = NULL;
    }
    node->is_leaf = 0;
    node->data = data;
    node->count = 0;

    return node;
}

void free_trienode(TrieNode* node) {
    for(int i = 0; i < N; i++) {
        if (node->children[i] != NULL) {
            free_trienode(node->children[i]);
        }
        else {
            continue;
        }
    }
    free(node);
}

TrieNode* insert_trie(TrieNode* root, char* word) {

    TrieNode* temp = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int idx = (int)word[i] - 'a'; // only lowercase words!!!
        if (temp->children[idx] == NULL) {
            temp->children[idx] = make_trienode(word[i]);
        }
        temp = temp->children[idx];
    }
    temp->is_leaf = 1;
    temp->count++;

    return root;
}

int search_trie(TrieNode* root, char* word) {
    TrieNode* temp = root;

    for (int i = 0; word[i] != '\0'; i++) {
        int position = word[i] - 'a';
        if (temp->children[position] == NULL) {
            return 0;
        }
        temp = temp->children[position];
    }
    if (temp != NULL && temp->is_leaf == 1) {
        return 1;
    }
    return 0;
}

void print_trie(TrieNode* root) {
    if (!root) {
        return;
    }
    TrieNode* temp = root;
    printf("%c -> ", temp->data);
    for (int i = 0; i < N; i++) {
        print_trie(temp->children[i]); 
    }
}

void print_search(TrieNode* root, char* word) {
    printf("Searching for %s: ", word);
    if (search_trie(root, word) == 0) {
        printf("Not Found\n");
    }
    else {
        printf("Found!\n");
    }
}

int find_cnt_word(TrieNode* root, char* word) {
    int len = strlen(word);
    TrieNode* my_node = root;
    for (int i = 0; i < len; i++) {
        int ind = word[i] - 'a';
        if (!my_node->children[ind]) {
            return 0;
        }
        my_node = my_node->children[ind];
    }
    return my_node->count;
}
/*
int main() {
    // Driver program for the Trie Data Structure Operations
    TrieNode* root = make_trienode('\0');
    root = insert_trie(root, "hello");
    root = insert_trie(root, "hi");
    root = insert_trie(root, "teacan");
    root = insert_trie(root, "teabag");
    root = insert_trie(root, "teacan");
    root = insert_trie(root, "teacan");
    print_search(root, "tea");
    print_search(root, "teabag");
    print_search(root, "teacan");
    print_search(root, "hi");
    print_search(root, "hey");
    print_search(root, "hello");
    int cnt = find_cnt_word(root, "teacan");
    printf("cnt: %d\n", cnt);
    // print_trie(root);
    free_trienode(root);
    return 0;
}
*/
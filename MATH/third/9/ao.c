#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *word;
    int count;
    struct Node *left, *right;
} Node;

typedef struct {
    char *word;
    int count;
} WordCount;

typedef struct {
    WordCount *array;
    int size;
    int capacity;
} WordCountArray;

Node* insert(Node* root, char* word) {
    if (root == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->word = strdup(word);
        newNode->count = 1;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    int compareResult = strcmp(word, root->word);

    if (compareResult < 0) {
        root->left = insert(root->left, word);
    } else if (compareResult > 0) {
        root->right = insert(root->right, word);
    } else {
        root->count++;
    }

    return root;
}

WordCountArray* initializeWordCountArray(int capacity) {
    WordCountArray* wca = (WordCountArray*)malloc(sizeof(WordCountArray));
    wca->array = (WordCount*)malloc(capacity * sizeof(WordCount));
    wca->size = 0;
    wca->capacity = capacity;
    return wca;
}

void insertOrUpdateWord(WordCountArray* wca, char* word) {
    int i;
    for (i = 0; i < wca->size; i++) {
        if (strcmp(wca->array[i].word, word) == 0) {
            wca->array[i].count++;
            return;
        }
    }

    if (wca->size < wca->capacity) {
        wca->array[wca->size].word = strdup(word);
        wca->array[wca->size].count = 1;
        wca->size++;
    }
}

void inOrderTraversalAndUpdateArray(Node* node, WordCountArray* wca) {
    if (node != NULL) {
        inOrderTraversalAndUpdateArray(node->left, wca);
        insertOrUpdateWord(wca, node->word);
        inOrderTraversalAndUpdateArray(node->right, wca);
    }
}

void nMostFrequentWords(Node* root, int n) {
    WordCountArray* wca = initializeWordCountArray(n);

    inOrderTraversalAndUpdateArray(root, wca);

    // Output the n most frequent words
    printf("%d most frequent words:\n", n);
    for (int i = 0; i < wca->size; i++) {
        printf("%s - Count: %d\n", wca->array[i].word, wca->array[i].count);
    }

    // Free memory
    for (int i = 0; i < wca->size; i++) {
        free(wca->array[i].word);
    }
    free(wca->array);
    free(wca);
}

int main() {
    // Create a sample BST with words
    Node* root = NULL;
    root = insert(root, "apple");
    root = insert(root, "orange");
    root = insert(root, "banana");
    root = insert(root, "apple");
    root = insert(root, "grape");

    // Output the 2 most frequent words
    nMostFrequentWords(root, 2);

    // Free the memory allocated for the BST

    return 0;
}

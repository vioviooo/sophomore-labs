#include <stdio.h>
#include <stdlib.h>

// Node structure for the circular linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to create a new node with the given data
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed. Unable to create a new node.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new node at the beginning of the list
void insertAtBeginning(Node** head, int value) {
    Node* newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head;
    } else {
        Node* current = *head;
        while (current->next != *head) {
            current = current->next;
        }
        newNode->next = *head;
        current->next = newNode;
        *head = newNode;
    }
}

// Function to display the elements of the list
void displayList(Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node* current = head;
    do {
        printf("%d -> ", current->data);
        current = current->next;
    } while (current != head);

    printf("(head)\n");
}

// Function to free the memory allocated for the list
void freeList(Node** head) {
    if (*head == NULL) {
        return;
    }

    Node* current = *head;
    Node* nextNode;

    do {
        nextNode = current->next;
        free(current);
        current = nextNode;
    } while (current != *head);

    *head = NULL;
}

int main() {
    Node* myList = NULL;

    insertAtBeginning(&myList, 30);
    insertAtBeginning(&myList, 20);
    insertAtBeginning(&myList, 10);

    displayList(myList);

    insertAtBeginning(&myList, 40);
    insertAtBeginning(&myList, 50);

    displayList(myList);

    // Free the memory allocated for the list
    freeList(&myList);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { SUCCESS, MEMORY_ERROR } Result;

typedef struct Liver {
    char name[BUFSIZ];
    char middle_name[BUFSIZ];
    char last_name[BUFSIZ];
    int day;
    int month;
    int year;
    char gender;
    double salary;
    struct Liver* next;
} Liver;

Liver* insert_sorted(Liver* head, Liver* new_liver) {
    Liver* current = head;
    Liver* previous = NULL;

    while (current != NULL && current->year < new_liver->year) {
        previous = current;
        current = current->next;
    }

    if (previous == NULL) {
        new_liver->next = head;
        head = new_liver;
    } else {
        previous->next = new_liver;
        new_liver->next = current;
    }

    return head;
}

Result add_liver(Liver** head, Liver* prev_state) {
    Liver* new_liver = (Liver*)malloc(sizeof(Liver));
    if (new_liver == NULL) {
        return MEMORY_ERROR;
    }

    printf("Enter information about the new liver:\n");
    printf("Name: ");
    scanf("%s", new_liver->name);
    printf("Middle Name: ");
    scanf("%s", new_liver->middle_name);
    printf("Last Name: ");
    scanf("%s", new_liver->last_name);
    printf("Day of birth: ");
    scanf("%d", &new_liver->day);
    printf("Month of birth: ");
    scanf("%d", &new_liver->month);
    printf("Year of birth: ");
    scanf("%d", &new_liver->year);
    printf("Gender (M/F): ");
    scanf(" %c", &new_liver->gender);
    printf("Salary: ");
    scanf("%lf", &new_liver->salary);

    new_liver->next = NULL;
    *head = insert_sorted(*head, new_liver);

    // If we're adding a new liver, update the previous state
    if (prev_state != NULL) {
        *prev_state = **head;
    }

    return SUCCESS;
}

Liver* load_data(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    Liver* head = NULL;
    Liver* current = NULL;
    char line[BUFSIZ];

    while (fgets(line, sizeof(line), file) != NULL) {
        Liver* new_liver = (Liver*)malloc(sizeof(Liver));
        sscanf(line, "%s %s %s %d %d %d %c %lf", new_liver->name, new_liver->middle_name,
               new_liver->last_name, &new_liver->day, &new_liver->month, &new_liver->year, &new_liver->gender,
               &new_liver->salary);

        new_liver->next = NULL;
        head = insert_sorted(head, new_liver);
        current = new_liver;
    }

    fclose(file);
    return head;
}

void print_list(Liver* head) {
    Liver* current = head;
    while (current != NULL) {
        printf("%s %s %s %d %d %d %c %.2lf\n", current->name, current->middle_name, current->last_name,
               current->day, current->month, current->year, current->gender, current->salary);
        current = current->next;
    }
}

void save_data(const char* filename, Liver* head) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    Liver* current = head;
    while (current != NULL) {
        fprintf(file, "%s %s %s %d %d %d %c %.2lf\n", current->name, current->middle_name, current->last_name,
                current->day, current->month, current->year, current->gender, current->salary);
        current = current->next;
    }

    fclose(file);
}

Liver* undo(Liver* head, Liver* prev_state) {
    // Удаление текущего состояния и восстановление предыдущего
    while (head != prev_state) {
        Liver* temp = head;
        head = head->next;
        free(temp);
    }
    return prev_state;
}

Liver* find_liver(Liver* head, int year) {
    Liver* current = head;
    while (current != NULL && current->year != year) {
        current = current->next;
    }
    return current;
}

int main() {
    Liver* head = NULL;
    Liver* prev_state = NULL;

    char filename[BUFSIZ];
    printf("Enter the filename to load data: ");
    scanf("%s", filename);

    head = load_data(filename);
    if (head == NULL) {
        return 1;
    }

    char choice;
    do {
        printf("\nOptions:\n");
        printf("1. Print the list\n");
        printf("2. Add a new liver\n");
        printf("3. Find a liver by year\n");
        printf("4. Save data to a file\n");
        printf("5. Undo\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                print_list(head);
                break;
            case '2': {
                Result result = add_liver(&head, prev_state);
                if (result == MEMORY_ERROR) {
                    printf("Error: Memory allocation failed\n");
                } else {
                    prev_state = (Liver*)malloc(sizeof(Liver));
                    if (prev_state != NULL) {
                        *prev_state = *head;
                    } else {
                        printf("Error: Memory allocation failed for undo state\n");
                    }
                }
                break;
            }
            case '3': {
                int year;
                printf("Enter the year to search for: ");
                scanf("%d", &year);
                Liver* found = find_liver(head, year);
                if (found != NULL) {
                    printf("Liver found:\n");
                    printf("%s %s %s %d %d %d %c %.2lf\n", found->name, found->middle_name, found->last_name,
                           found->day, found->month, found->year, found->gender, found->salary);
                } else {
                    printf("Liver not found\n");
                }
                break;
            }
            case '4': {
                char save_filename[BUFSIZ];
                printf("Enter the filename to save data: ");
                scanf("%s", save_filename);
                save_data(save_filename, head);
                break;
            }
            case '5':
                if (prev_state != NULL) {
                    head = undo(head, prev_state);
                    free(prev_state);
                    prev_state = NULL;
                } else {
                    printf("Nothing to undo\n");
                }
                break;
            case '0':
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != '0');

    // Очистка памяти перед выходом
    while (head != NULL) {
        Liver* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

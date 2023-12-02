#include <complex.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <time.h>

enum status_codes {
    OK = 1,
    ERROR = -2,
    INVALID_INPUT = -3,
    INVALID_INPUT_FILE = -4,
    NO_MEMORY = -5,
    OVERFLOW_ = -6,
    UNDEFINED = -7,
    FILE_NOT_OPEN = -8,
    EMPTY = -9
};

void print_scs(int choice) {
    switch (choice) {
        case INVALID_INPUT:
            printf("\nInvalid input.\n");
            break;
        case OK:
            printf("\nProject finished successfully!\n");
            break;
        case NO_MEMORY:
            printf("\nNo memory left.\n");
            break;
        case OVERFLOW_:
            printf("\nOverflow!\n");
            break;
        case UNDEFINED:
            printf(
                "\nError! What you're trying to calculate IS UNDEFINED or uses "
                "complex numbers.\n");
            break;
        case FILE_NOT_OPEN:
            printf("\nCan't open file.\n");
            break;
        case INVALID_INPUT_FILE:
            printf("\nInvalid format of data in file.\n");
            break;
        case EMPTY:
            printf("\nEmpty list.\n");
            break;
        default:
            break;
    }
}

typedef struct Liver {
    char name[BUFSIZ];
    char middle_name[BUFSIZ]; // can be empty
    char last_name[BUFSIZ];
    int day;
    int month;
    int year;
    char gender;
    double salary;
    struct Liver *next;
} Liver;

Liver *insert_sorted(Liver *head, Liver *new_liver) {
    Liver *curr = head;
    Liver *previous = NULL;

    while (curr != NULL && curr->year < new_liver->year) {
        previous = curr;
        curr = curr->next;
    }

    if (previous == NULL) {
        new_liver->next = head;
        head = new_liver;
    } else {
        previous->next = new_liver;
        new_liver->next = curr;
    }

    return head;
}

int add_liver(Liver **head, Liver **prev_state) {
    char name[BUFSIZ];
    char sur[BUFSIZ];
    char mid[BUFSIZ];
    int d, m, y;
    char gen;
    double sal;
    if (scanf("%s %s %s %d %d %d %c %lf", name, sur, mid, &d, &m, &y, &gen, &sal) != 8 || m > 12 ||
        d > 31 || m < 1 || d < 1 || y < 1 || (tolower(gen) != 'w' && tolower(gen) != 'm') ||
        fabs(sal - 1e-6) < 0.0) {
        while (getchar() != '\n')
            ;
        return INVALID_INPUT;
    }

    Liver *new_liver = (Liver *)malloc(sizeof(Liver));
    if (new_liver == NULL) {
        return NO_MEMORY;
    }

    strcpy(new_liver->name, name);
    strcpy(new_liver->middle_name, mid);
    strcpy(new_liver->last_name, sur);
    new_liver->day = d;
    new_liver->month = m;
    new_liver->year = y;
    new_liver->gender = gen;
    new_liver->salary = sal;

    new_liver->next = NULL;
    *head = insert_sorted(*head, new_liver);

    // update previous state
    if (*prev_state != NULL) {
        *prev_state = (Liver *)malloc(sizeof(Liver));
        if (*prev_state == NULL) {
            printf("here!");
            free(new_liver);
            return NO_MEMORY;
        }
        memcpy(*prev_state, new_liver, sizeof(Liver));
    }

    return OK;
}

int load_data(const char *filename, Liver **head) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return FILE_NOT_OPEN;
    }

    *head = NULL;
    Liver *curr = NULL;

    char line[BUFSIZ];
    while (fgets(line, sizeof(line), file) != NULL) {
        Liver *new_liver = (Liver *)malloc(sizeof(Liver));
        if (new_liver == NULL) {
            fclose(file);
            return NO_MEMORY;
        }

        if (sscanf(line, "%s %s %s %d %d %d %c %lf", new_liver->last_name, new_liver->name,
                   new_liver->middle_name, &new_liver->day, &new_liver->month, &new_liver->year,
                   &new_liver->gender, &new_liver->salary) != 8 ||
            new_liver->salary < 1e-6 || new_liver->day < 1 || new_liver->day > 31 || new_liver->month < 1 ||
            new_liver->month > 12 ||
            (tolower(new_liver->gender) != 'w' && tolower(new_liver->gender) != 'm')) {
            fclose(file);
            free(new_liver);
            return INVALID_INPUT_FILE;
        }

        new_liver->next = NULL;
        *head = insert_sorted(*head, new_liver);
        curr = new_liver;
    }

    fclose(file);
    return OK;
}

void print_list(Liver *head) {
    Liver *curr = head;
    while (curr != NULL) {
        printf("%s %s %s %d %d %d %c %.2lf\n", curr->last_name, curr->name, curr->middle_name, curr->day,
               curr->month, curr->year, curr->gender, curr->salary);
        curr = curr->next;
    }
}

int find_liver(Liver *head) {
    char name[BUFSIZ];
    char sur[BUFSIZ];
    char mid[BUFSIZ];
    int d, m, y;
    char gen;
    double sal;
    if (scanf("%s %s %s %d %d %d %c %lf", sur, name, mid, &d, &m, &y, &gen, &sal) != 8) {
        while (getchar() != '\n')
            ;
        return INVALID_INPUT;
    }
    Liver *curr = head;
    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0 && strcmp(curr->middle_name, mid) == 0 &&
            strcmp(curr->last_name, sur) == 0 && curr->day == d && curr->month == m && curr->year == y &&
            curr->gender == gen && fabs(curr->salary - sal) < 1e-6) {  // TODO: eps
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

int delete_liver(Liver **head) {
    printf("Please, enter liver's parameters: ");

    char name[BUFSIZ];
    char sur[BUFSIZ];
    char mid[BUFSIZ];
    int d, m, y;
    char gen;
    double sal;

    if (scanf("%s %s %s %d %d %d %c %lf", sur, name, mid, &d, &m, &y, &gen, &sal) != 8) {
        while (getchar() != '\n')
            ;
        return INVALID_INPUT;
    }

    Liver *current = *head;
    Liver *previous = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && strcmp(current->middle_name, mid) == 0 &&
            strcmp(current->last_name, sur) == 0 && current->year == y && current->day == d &&
            current->month == m && fabs(current->salary - sal) < 1e-6) {
            if (previous == NULL) {
                *head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return 1;
        }
        previous = current;
        current = current->next;
    }

    return 0;
}

void print_menu() {
    printf("\nChoose your action:\n");
    printf("1. Print livers\n");  //
    printf("2. Add liver\n");     //
    printf("3. Find liver\n");    //
    printf("4. Save data to a file\n");
    printf("5. Undo\n");
    printf("6. Delete liver\n"); //
    printf("7. Change liver's info\n");
    printf("0. Exit\n");
}

int main(int argc, char *argv[]) {
    Liver *head = NULL;
    Liver *prev_state = NULL;

    int status;
    if ((status = load_data(argv[1], &head)) != OK) {
        print_scs(status);
        return status;
    }

    bool flag = true;
    int choice = -1;
    while (flag) {
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            choice = -1;
        }

        switch (choice) {
            case 1:
                if (head == NULL) {
                    print_scs(EMPTY);
                } else {
                    print_list(head);
                }
                break;
            case 2:
                prev_state = head;
                printf("Please, enter the liver info: ");
                if ((status = add_liver(&head, &prev_state)) != OK) {
                    print_scs(status);
                    prev_state = NULL;
                }
                break;
            case 3:
                if (head == NULL) {
                    print_scs(EMPTY);
                } else {
                    printf("Please, enter paramteres of a liver: ");
                    if ((status = find_liver(head)) < 0) {
                        print_scs(status);
                    } else {
                        printf("%s\n", (status == 1) ? "Found." : "Not found.");
                    }
                }
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:  // delete liver
                if (head == NULL) {
                    print_scs(EMPTY);
                } else {
                    if ((status = delete_liver(&head)) < 0) {
                        print_scs(status);
                    } else {
                        printf("%s\n", (status == 1) ? "Deleted." : "Liver not found.");
                    }
                }
                break;
            case 0:
                flag = false;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    if (prev_state != NULL) {
        free(prev_state);
    }

    while (head != NULL) {
        Liver *tmp = head;
        head = head->next;
        free(tmp);
    }

    return 0;
}

// поиск жителя с заданными параметрами
// изменение жителя
// выгрузка в файл с стдин
// отменить N/2 операций, N - колво операций с самого начала
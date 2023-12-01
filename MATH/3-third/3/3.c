#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>
#include <complex.h>

enum status_codes {
    OK = 1,
    ERROR = -2,
    INVALID_INPUT = 2,
    INVALID_INPUT_FILE = -6,
    NO_MEMORY = -1,
    OVERFLOW_ = -3,
    UNDEFINED = -4,
    FILE_NOT_OPEN = -5
};

void print_scs(int choice) {
    switch(choice) {
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
            printf("\nError! What you're trying to calculate IS UNDEFINED or uses complex numbers.\n");
            break;
        case FILE_NOT_OPEN:
            printf("\nCan't open file.\n");
            break;
        case INVALID_INPUT_FILE:
            printf("\nInvalid format of data in file.\n");
            break;
        default:
            break;
    }
}


bool is_valid_flag(char ch[]) {
    char commands[] = "ad";

    if ((ch[0] != '-' && ch[0] != '/') || ch[2] != '\0') {
        return false;
    }

    for (int i = 0; commands[i] != '\0'; i++) {
        if (ch[1] == commands[i]) {
            return true;
        }
    }

    return false;
}

typedef struct {
    int id;
    char name[BUFSIZ];
    char surname[BUFSIZ];
    double salary;
} Employee;

int cmp_decreasing(const void *a, const void *b) {
    const Employee *employeeA = (const Employee *)a;
    const Employee *employeeB = (const Employee *)b;

    // check salaries
    if (employeeA->salary < employeeB->salary) {
        return 1; // 'a' comes before 'b'
    } else if (employeeA->salary > employeeB->salary) {
        return -1; // 'a' comes after 'b'
    }

    // check surnames
    int surname_cmp = strcmp(employeeA->surname, employeeB->surname);
    if (surname_cmp != 0) {
        return -surname_cmp;
    }

    // check names
    int name_cmp = strcmp(employeeA->name, employeeB->name);
    if (name_cmp != 0) {
        return -name_cmp;
    }

    // check id
    if (employeeA->id < employeeB->id) {
        return 1; 
    } else if (employeeA->id > employeeB->id) {
        return -1;
    }

    return 0;  // 'a' and 'b' are "equal"
}

int cmp_increasing(const void *a, const void *b) {
    const Employee *employeeA = (const Employee*)a;
    const Employee *employeeB = (const Employee*)b;

    // check salaries
    if (employeeA->salary < employeeB->salary) {
        return -1;
    } else if (employeeA->salary > employeeB->salary) {
        return 1;
    }

    // check surnames
    int surname_cmp = strcmp(employeeA->surname, employeeB->surname);
    if (surname_cmp != 0) {
        return surname_cmp;
    }

    // check names
    int name_cmp = strcmp(employeeA->name, employeeB->name);
    if (name_cmp != 0) {
        return name_cmp;
    }

    // check id
    if (employeeA->id < employeeB->id) {
        return -1; 
    } else if (employeeA->id > employeeB->id) {
        return 1;
    }

    return 0;  // 'a' and 'b' are "equal"
}

int main(int argc, char* argv[]) {
    
    if (argc != 3) {
        print_scs(INVALID_INPUT);
        return INVALID_INPUT;
    }

    if (!is_valid_flag(argv[1])) {
        print_scs(INVALID_INPUT);
        return INVALID_INPUT;
    }

    // a -> increasing or d -> decreasing sorting order
    char choice = argv[1][1];

    char filename[BUFSIZ];
    strcpy(filename, argv[2]);

    FILE* fptr = fopen(filename, "r");

    if (fptr == NULL) {
        print_scs(FILE_NOT_OPEN);
        return FILE_NOT_OPEN;
    }

    int capacity = BUFSIZ;
    Employee* arr = (Employee*)calloc(capacity, sizeof(Employee));
    int cnt = -1;
    while (!feof(fptr)) {
        cnt++;
        if (cnt >= capacity) {
            Employee* tmp = (Employee*)realloc(arr, sizeof(Employee) * (2 * capacity));
            if (tmp == NULL) { // realloc freed arr memory if != NULL
                free(arr);
                print_scs(NO_MEMORY);
                return NO_MEMORY;
            }
            arr = tmp;
            capacity *= 2;
        }
        if (fscanf(fptr, "%d %s %s %lf", &arr[cnt].id, arr[cnt].name, arr[cnt].surname, &arr[cnt].salary) != 4) {
            print_scs(INVALID_INPUT_FILE);
            return INVALID_INPUT_FILE;
        }
    }

    fclose(fptr);

    fptr = fopen("res.txt", "w");
    if (fptr == NULL) {
        print_scs(FILE_NOT_OPEN);
        return FILE_NOT_OPEN;
    }

    if (choice == 'a') {
        qsort(arr, cnt + 1, sizeof(Employee), cmp_increasing);
    } else if (choice == 'd') {
        qsort(arr, cnt + 1, sizeof(Employee), cmp_decreasing);
    }
    
    for (int i = 0; i <= cnt; i++) {
        fprintf(fptr, "%d %s %s %lf\n", arr[i].id, arr[i].name, arr[i].surname, arr[i].salary);
    }

    free(arr);

    return 0;
}

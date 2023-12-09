#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum status_codes {
    OK = 0,
    NO_MEMORY = -1,
    INVALID_INFIX = 2,
    UNBALANCED_BRACKETS = 3,
    EMPTY_FILE = -2,
    INVALID_INPUT = -3,
    FILE_NOT_OPEN = -4
};

void print_scs(int choice) {
    switch (choice) {
        case INVALID_INFIX:
            printf("\nERROR: INVALID INFIX EXPRESSION\n");
            break;
        case OK:
            printf("\nProject finished successfully!\n");
            break;
        case NO_MEMORY:
            printf("\nERROR: NO MEMORY\n");
            break;
        case UNBALANCED_BRACKETS:
            printf("\nERROR: UNBALANCED PARENTHESES\n");
            break;
        case EMPTY_FILE:
            printf("\nNOTICE: EMPTY FILE\n");
            break;
        case INVALID_INPUT:
            printf("\nERROR: INVALID INPUT\n");
            break;
        case FILE_NOT_OPEN:
            printf("\nERROR: FILE WAS NOT OPEN\n");
            break;
        default:
            break;
    }
}

typedef struct {
    int val;
    char var[256];
} MemoryCell;

bool is_new(MemoryCell** arr, const int cnt, char curr_var[]) {
    for (int i = 0; i < cnt; i++) {
        if (strcmp((*arr)[i].var, curr_var) == 0) {
            return false;
        }
    }
    return true;
}

int find_val(MemoryCell** arr, const int cnt, char curr_var[]) {
    for (int i = 0; i < cnt; i++) {
        if (strcmp((*arr)[i].var, curr_var) == 0) {
            return (*arr)[i].val;
        }
    }
    return 0;
}

void change_val(MemoryCell** arr, const int cnt, char curr_var[], int new_val) {
    for (int i = 0; i < cnt; i++) {
        if (strcmp((*arr)[i].var, curr_var) == 0) {
            (*arr)[i].val = new_val;
        }
    }
}

bool isOperator(char c) { return (c == '/' || c == '*' || c == '+' || c == '-' || c == '%'); }

int extract_val(char line[], MemoryCell** arr, const int cnt) {
    int i = 0;
    while (line[i] != '=') {
        i++;
    }
    i++;

    int j = 0;
    char second_var[BUFSIZ];
    for (; isalnum(line[i]); i++) {
        second_var[j] = line[i];
        j++;
    }
    second_var[j] = '\0';

    int res = 0;
    if (isdigit(second_var[0])) {
        res = atoi(second_var);
    } else {
        res = find_val(arr, cnt, second_var);
    }

    if (line[i] == ';') {
        return res;
    }

    char oper = line[i];

    i++;

    int k = 0;
    char third_var[BUFSIZ];
    for (; line[i] != ';'; i++) {
        third_var[k] = line[i];
        k++;
    }
    third_var[k] = '\0';

    int res2;
    if (isdigit(third_var[0])) {
        res2 = atoi(third_var);
    } else {
        res2 = find_val(arr, cnt, third_var);
    }

    int fin;
    switch (oper) {
        case '*':
            fin = res * res2;
            break;
        case '-':
            fin = res - res2;
            break;
        case '+':
            fin = res + res2;
            break;
        case '%':
            fin = res % res2;
            break;
        case '/':
            fin = res / res2;
            break;
    }

    return fin;
}

int new_cell(char line[], MemoryCell** arr, int* capacity, int* cnt) {
    char var[BUFSIZ];
    int i = 0;
    for (; line[i] != '='; i++) {
        var[i] = line[i];
    }

    var[i] = '\0';

    i++;

    bool flag = is_new(arr, *cnt, var);
    if (flag) {
        (*cnt)++;
    }

    if (*cnt >= *capacity) {
        *capacity *= 2;
        MemoryCell* tmp = (MemoryCell*)realloc(*arr, *capacity * sizeof(MemoryCell));
        if (tmp == NULL) {
            return NO_MEMORY;
        }
        *arr = tmp;
    }

    int new_val = extract_val(line, arr, *cnt);

    if (flag) {
        strcpy((*arr)[*cnt - 1].var, var);
        (*arr)[*cnt - 1].val = new_val;
    } else {
        change_val(arr, *cnt, var, new_val);
    }

    return OK;
}

void print_cells(MemoryCell** arr, const int cnt) {
    for (int i = 0; i < cnt; i++) {
        printf("i = %d, %d %s\n", i, (*arr)[i].val, (*arr)[i].var);
    }
}

void print_cell(char line[], MemoryCell** arr, const int cnt) {
    char var[BUFSIZ];
    int i = 0;
    while (line[i] != ' ') {
        i++;
    }
    i++;

    int j = 0;
    for (; line[i] != ';'; i++, j++) {
        var[j] = line[i];
    }
    var[j] = '\0';

    for (int j = 0; j < cnt; j++) {
        if (strcmp((*arr)[j].var, var) == 0) {
            printf("i = %d, %s = %d\n", j, (*arr)[j].var, (*arr)[j].val);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        print_scs(INVALID_INPUT);
        return INVALID_INPUT;
    }

    FILE* fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        print_scs(FILE_NOT_OPEN);
        return FILE_NOT_OPEN;
    }

    MemoryCell* arr = NULL;
    int capacity = 1;

    char line[BUFSIZ];
    int status, cnt = 0;
    while (fgets(line, sizeof(line), fptr) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        if (strstr(line, "print;") != NULL) {
            print_cells(&arr, cnt);
        } else if (strstr(line, "print") != NULL) {
            print_cell(line, &arr, cnt);
        } else if (strstr(line, "=") != NULL) {
            if ((status = new_cell(line, &arr, &capacity, &cnt)) != OK) {
                print_scs(status);
            }
        }
    }

    fclose(fptr);

    free(arr);

    print_scs(OK);
    return OK;
}
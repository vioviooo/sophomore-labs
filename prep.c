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

int binary_search(int arr[], int target, int size) {
    int l = 0;
    int r = size - 1;

    while (l <= r) {
        int mid = (l + r) / 2;
        if (arr[mid] > target) {
            r = mid - 1;
        }
        else if (arr[mid] < target) {
            l = mid + 1;
        }
        else {
            return 1;
        }
    }
    return 0;
}

typedef struct {
    int age;
    char grade;
} Student;

int cmp(const void* a, const void* b) {
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;

    if (studentA->age > studentB->age) {
        return -1; // the first element goes first
    } else if (studentA->age < studentB->age) {
        return 1; // the second element goes first
    }
    else {
        if (studentA->grade > studentB->grade) {
            return -1;
        }
        else if (studentA->grade < studentB->grade) {
            return 1;
        }
        else {
            return 0; // equal
        }
    }
}

struct Point {
   int x;
   int y;
};

struct Node {
   char data;
   int child_cnt;
   struct Node** children; // there can be more than 2 children
};



int add_node(char data, struct Node** res) {
   struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
   if (newNode == NULL) {
       return NO_MEMORY;
   }
   newNode->data = data;
   newNode->child_cnt = 0;
   newNode->children = NULL;
   *res = newNode;
   return OK;
}


int add_child(struct Node* parent, struct Node* child) {
    struct Node** tmp = realloc(parent->children, (parent->child_cnt + 1) * sizeof(struct Node*));
    if (tmp == NULL) {
       free(parent->children);
       parent->children = NULL;
       return NO_MEMORY;
    
    }
    parent->children = tmp;
    parent->children[parent->child_cnt] = child;
    parent->child_cnt++;

    return OK;
}

void free_tree(struct Node* root) {
   if (root != NULL) {
        for (int i = 0; i < root->child_cnt; i++) {
           free_tree(root->children[i]);
        }
       free(root->children);
       free(root);
   }
}



int main(int argc, char* argv[]) {
    
    // int a = 5, b = 7, c;
    // c  = (a++, ++b);


    // // printf("%d %d %d", a, b, c);

    // int arr[] = {1, 2, 3, 3, 4, 5};
    // int target = 9;

    // int res = binary_search(arr, target, 6);

    // Student array[] = {{17, 'b'}, {19, 'c'}};

    // qsort(array, 2, sizeof(Student), cmp);
    // printf("%d %c, %d %c", array[0].age, array[0].grade, array[1].age, array[1].grade);
    // printf("here: %d", res);

    // const pointer to const
    // const int a = 10;
    // const int* const ptr1 = &a;

    // // const pointer to non-const
    // int b = 20;
    // int* const ptr2 = &b;

    // // non-const pointer to const
    // const int c = 30;
    // const int* ptr3 = &c;

    // // non-const to non-const
    // int d = 40;
    // int* ptr4 = &d;

    // printf("%d", *ptr4);

    #define TO_STRING(x) #x
    printf("%s\n", TO_STRING(hello)); // будет выведено "hello"


    print_scs(OK);
    return OK;
}
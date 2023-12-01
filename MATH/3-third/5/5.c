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

typedef unsigned char uch;

enum status_codes {
    OK = 1,
    ERROR = -2,
    INVALID_INPUT = -3,
    INVALID_INPUT_FILE = -4,
    NO_MEMORY = -5,
    OVERFLOW_ = -6,
    UNDEFINED = -7,
    FILE_NOT_OPEN = -8
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
    char group[BUFSIZ];
    uch* grades;
} Student;

enum choices {
    ID = 1,
    SURNAME = 2,
    NAME = 3,
    GROUP = 4
};

////////////////////////////////////////////////////////////////////////////////

int cmp_id(const void *a, const void *b) {
    const Student *studA = (const Student*)a;
    const Student *studB = (const Student*)b;
    
    if (studA->id < studB->id) {
        return -1;
    } 
    else if (studA->id > studB->id) {
        return 1;
    }

    return 0;
}

int cmp_name(const void *a, const void *b) {
    const Student *studA = (const Student*)a;
    const Student *studB = (const Student*)b;
    
    int name_cmp = strcmp(studA->name, studB->name);
    if (name_cmp != 0) {
        return name_cmp;
    }
    
    return 0;
}

int cmp_surname(const void *a, const void *b) {
    const Student *studA = (const Student*)a;
    const Student *studB = (const Student*)b;
    
    int surname_cmp = strcmp(studA->surname, studB->surname);
    if (surname_cmp != 0) {
        return surname_cmp;
    }
    
    return 0;
}

int cmp_group(const void *a, const void *b) {
    const Student *studA = (const Student*)a;
    const Student *studB = (const Student*)b;
    
    int group_cmp = strcmp(studA->surname, studB->surname);
    if (group_cmp != 0) {
        return -group_cmp;
    }
    
    return 0;
}

///////////////////////////////////////////////////////////////////////

int find_by_id(Student* arr, int size, int id, Student*** res) {
    int ind = 0, capacity = 1;    

    *res = (Student**)malloc(capacity * sizeof(Student*));
    if (*res == NULL) {
        return NO_MEMORY;
    }

    for (int i = 0; i < size; i++) {
        if (arr[i].id == id) {
            if (ind >= capacity) {
                capacity *= 2;

                Student** tmp = (Student**)realloc(*res, capacity * sizeof(Student*));
                if (tmp == NULL) {
                    return NO_MEMORY;
                }
                *res = tmp;
            }

            (*res)[ind] = (Student*)malloc(sizeof(Student));
            if ((*res)[ind] == NULL) {
                return NO_MEMORY;
            }

            (*res)[ind]->id = arr[i].id;
            (*res)[ind]->grades = arr[i].grades;
            strcpy((*res)[ind]->name, arr[i].name);
            strcpy((*res)[ind]->surname, arr[i].surname);
            strcpy((*res)[ind]->group, arr[i].group);

            ind++;
        }
    }
    return ind;
}

int find_by_name(Student* arr, int size, char name[], Student*** res) {
    int ind = 0, capacity = 1;    

    *res = (Student**)malloc(capacity * sizeof(Student*));
    if (*res == NULL) {
        return NO_MEMORY;
    }

    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i].name, name) == 0) {
            if (ind >= capacity) {
                capacity *= 2;

                Student** tmp = (Student**)realloc(*res, capacity * sizeof(Student*));
                if (tmp == NULL) {
                    return NO_MEMORY;
                }
                *res = tmp;
            }

            (*res)[ind] = (Student*)malloc(sizeof(Student));
            if ((*res)[ind] == NULL) {
                return NO_MEMORY;
            }

            (*res)[ind]->id = arr[i].id;
            (*res)[ind]->grades = arr[i].grades;
            strcpy((*res)[ind]->name, arr[i].name);
            strcpy((*res)[ind]->surname, arr[i].surname);
            strcpy((*res)[ind]->group, arr[i].group);

            ind++;
        }
    }

    return ind;
}

int find_by_surname(Student* arr, int size, char surname[], Student*** res) { // TODO:
    int ind = 0, capacity = 1;    

    *res = (Student**)malloc(capacity * sizeof(Student*));
    if (*res == NULL) {
        return NO_MEMORY;
    }

    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i].surname, surname) == 0) {
            if (ind >= capacity) {
                capacity *= 2;

                Student** tmp = (Student**)realloc(*res, capacity * sizeof(Student*));
                if (tmp == NULL) {
                    return NO_MEMORY;
                }
                *res = tmp;
            }

            (*res)[ind] = (Student*)malloc(sizeof(Student));
            if ((*res)[ind] == NULL) {
                return NO_MEMORY;
            }

            (*res)[ind]->id = arr[i].id;
            (*res)[ind]->grades = arr[i].grades;
            strcpy((*res)[ind]->name, arr[i].name);
            strcpy((*res)[ind]->surname, arr[i].surname);
            strcpy((*res)[ind]->group, arr[i].group);

            ind++;
        }
    }

    return ind;
}

int find_by_group(Student* arr, int size, char group[], Student*** res) { // TODO: 
    int ind = 0, capacity = 1;    

    *res = (Student**)malloc(capacity * sizeof(Student*));
    if (*res == NULL) {
        return NO_MEMORY;
    }
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i].group, group) == 0) {
            if (ind >= capacity) {
                capacity *= 2;

                Student** tmp = (Student**)realloc(*res, capacity * sizeof(Student*));
                if (tmp == NULL) {
                    return NO_MEMORY;
                }
                *res = tmp;
            }

            (*res)[ind] = (Student*)malloc(sizeof(Student));
            if ((*res)[ind] == NULL) {
                return NO_MEMORY;
            }

            (*res)[ind]->id = arr[i].id;
            (*res)[ind]->grades = arr[i].grades;
            strcpy((*res)[ind]->name, arr[i].name);
            strcpy((*res)[ind]->surname, arr[i].surname);
            strcpy((*res)[ind]->group, arr[i].group);

            ind++;
        }
    }
    return ind;
}

double find_mean(uch* arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    double res = sum / (double)size;
    return res;
}

int find_by_id_1(Student* arr, int size, int id, Student** res) {
    for (int i = 0; i < size; i++) {
        if (arr[i].id == id) {
            (*res)->id = arr[i].id;
            (*res)->grades = arr[i].grades;
            strcpy((*res)->name, arr[i].name);
            strcpy((*res)->surname, arr[i].surname);
            strcpy((*res)->group, arr[i].group);
            return 1;
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

void print_default_menu() {
    printf("\nChoose your action:\n1. Sort the students.\n");
    printf("2. Find a student.\n3. Output info about a student in a file.\n");
    printf("4. Output students who have higher grade than mean in a file.\n");
    printf("5. Exit\n");
    printf("Please, enter your choice: ");
}

void choose_type() {
    printf("1. ID\n2. Surname\n3. Name\n4. Group\nPlease, enter your choice: ");
}

void clean_me(FILE* fptr, Student* arr, int size) {
    for (int i = 0; i < size; i++) {
        free(arr[i].grades);
    }
    free(arr);
    fclose(fptr);
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {

    const int num_exam = 5;
    
    if (argc < 2) {
        print_scs(INVALID_INPUT);
        return INVALID_INPUT;
    }

    int capacity = 2;
    Student* arr = (Student*)calloc(capacity, sizeof(Student));
    if (arr == NULL) {
        print_scs(NO_MEMORY);
        return NO_MEMORY;
    }

    char* filename = argv[1];
    FILE* fptr = fopen(filename, "r");

    double all_mean;
    int cnt = 0;
    while (fscanf(fptr, "%d %s %s %s", &arr[cnt].id, arr[cnt].surname, arr[cnt].name, arr[cnt].group) == 4) {
        uch* grades = (uch*)malloc(num_exam * sizeof(uch));
        int sum_grades = 0;
        for (int i = 0; i < num_exam; i++) {
            if (fscanf(fptr, "%hhu", &grades[i]) != 1) { 
                free(grades);
                clean_me(fptr, arr, cnt);
                print_scs(INVALID_INPUT_FILE);
                return INVALID_INPUT_FILE;
            }
            sum_grades += grades[i];
        }
        all_mean += find_mean(grades, num_exam);// each student's mean

        arr[cnt].grades = grades;
        cnt++; // add cnt for the next student
        if (cnt >= capacity - 1) {
            capacity *= 2;
            Student* tmp = (Student*)realloc(arr, capacity * sizeof(Student));
            if (tmp == NULL) {
                free(grades);
                clean_me(fptr, arr, cnt);
                print_scs(NO_MEMORY);
                return NO_MEMORY;
            }
            arr = tmp;
        }
    }

    all_mean /= (double)cnt;

    int choice;
    while (true) {
        print_default_menu();

        if (scanf("%d", &choice) != 1) {
            print_scs(INVALID_INPUT);
            return INVALID_INPUT;
        }

        if (choice == 1) {
            choose_type();

            int type = 0;
            if (scanf("%d", &type) != 1) {
                printf("\nInvalid command.\n");
                continue;
            }

            if (argc != 3) {
                print_scs(INVALID_INPUT);
                clean_me(fptr, arr, cnt);
                return INVALID_INPUT;
            }
            
            FILE* fptr_out = fopen(argv[2], "w");
            if (fptr_out == NULL) {
                print_scs(FILE_NOT_OPEN);
                return FILE_NOT_OPEN;
            }

            if (type == ID) {
                qsort(arr, cnt, sizeof(Student), cmp_id);
            }
            else if (type == SURNAME) {
                qsort(arr, cnt, sizeof(Student), cmp_surname);
            }
            else if (type == NAME) {
                qsort(arr, cnt, sizeof(Student), cmp_name);
            }
            else if (type == GROUP) {
                qsort(arr, cnt, sizeof(Student), cmp_group);
            }
            else {
                printf("\nInvalid command.\n");
                continue;
            }

            if (cnt == 0) {
                printf("\nEmpty array of students.\n");
                continue;
            }

            for (int i = 0; i < cnt; i++) {
                fprintf(fptr_out, "%d %s %s %s ", arr[i].id, arr[i].surname, arr[i].name, arr[i].group);
                for (int j = 0; j < num_exam; j++) {
                    fprintf(fptr_out, "%hhu ", arr[i].grades[j]);
                }
                fprintf(fptr_out, "\n");
            }

            fclose(fptr_out);
        }
        else if (choice == 2) {
            choose_type();
            
            int type = 0;
            if (scanf("%d", &type) != 1) {
                printf("\nInvalid command.\n");
                break;
            }

            printf("Enter the parameter: ");
            if (type == ID) {
                int num;
                if (scanf("%d", &num) != 1) {
                    printf("\nInvalid command.\n");
                    break;
                }

                Student** found_students = NULL;
                int ind = 0;
                if ((ind = find_by_id(arr, cnt, num, &found_students)) > 0) {
                    printf("Found!\nStudents info: ");
                    for (int i = 0; i < ind; i++) {
                        printf("%d %s %s %s ", found_students[i]->id, found_students[i]->surname, found_students[i]->name, found_students[i]->group);
                        for (int j = 0; j < num_exam; j++) {
                            printf("%hhu ", found_students[i]->grades[j]);
                        }
                        printf("\n");
                    }
                } else if (ind == 0) {
                    printf("Not found.");
                } else {
                    print_scs(ind);
                }
                for (int i = 0; i < ind; i++) {
                    free(found_students[i]);
                }
                free(found_students);
            }
            else if (type == SURNAME) {
                char buf[BUFSIZ];
                if (scanf("%s", buf) != 1) {
                    printf("\nInvalid command.");
                    break;
                }

                Student** found_students = NULL;
                int ind = 0;
                if ((ind = find_by_surname(arr, cnt, buf, &found_students)) > 0) {
                    printf("Found!\nStudents info: ");
                    for (int i = 0; i < ind; i++) {
                        printf("%d %s %s %s ", found_students[i]->id, found_students[i]->surname, found_students[i]->name, found_students[i]->group);
                        for (int j = 0; j < num_exam; j++) {
                            printf("%hhu ", found_students[i]->grades[j]);
                        }
                        printf("\n");
                    }
                } else if (ind == 0) {
                    printf("Not found.");
                } else {
                    print_scs(ind);
                }
                for (int i = 0; i < ind; i++) {
                    free(found_students[i]);
                }
                free(found_students);
            }
            else if (type == NAME) {
                char buf[BUFSIZ];
                if (scanf("%s", buf) != 1) {
                    printf("\nInvalid command.");
                    break;
                }

                Student** found_students = NULL;
                int ind = 0;
                if ((ind = find_by_name(arr, cnt, buf, &found_students)) > 0) {
                    printf("Found!\nStudents info: ");
                    for (int i = 0; i < ind; i++) {
                        printf("%d %s %s %s ", found_students[i]->id, found_students[i]->surname, found_students[i]->name, found_students[i]->group);
                        for (int j = 0; j < num_exam; j++) {
                            printf("%hhu ", found_students[i]->grades[j]);
                        }
                        printf("\n");
                    }
                } else if (ind == 0) {
                    printf("Not found.");
                } else {
                    print_scs(ind);
                }
                for (int i = 0; i < ind; i++) {
                    free(found_students[i]);
                }
                free(found_students);
            }
            else if (type == GROUP) {
                char buf[BUFSIZ];
                if (scanf("%s", buf) != 1) {
                    printf("\nInvalid command.");
                    break;
                }

                Student** found_students = NULL;
                int ind = 0;
                if ((ind = find_by_group(arr, cnt, buf, &found_students)) > 0) {
                    printf("Found!\nStudents info: ");
                    for (int i = 0; i < ind; i++) {
                        printf("%d %s %s %s ", found_students[i]->id, found_students[i]->surname, found_students[i]->name, found_students[i]->group);
                        for (int j = 0; j < num_exam; j++) {
                            printf("%hhu ", found_students[i]->grades[j]);
                        }
                        printf("\n");
                    }
                } else if (ind == 0) {
                    printf("Not found.");
                } else {
                    print_scs(ind);
                }
                for (int i = 0; i < ind; i++) {
                    free(found_students[i]);
                }
                free(found_students);
            }
            else {
                printf("\nInvalid command.\n");
                continue;
            }
        }
        else if (choice == 3) {
            printf("Enter student's ID: ");
            int num;
            if (scanf("%d", &num) != 1) {
                printf("\nInvalid command.");
                break;
            }

            if (argc != 3) {
                print_scs(INVALID_INPUT);
                clean_me(fptr, arr, cnt);
                return INVALID_INPUT;
            }

            FILE* fptr_out = fopen(argv[2], "w");
            if (fptr_out == NULL) {
                print_scs(FILE_NOT_OPEN);
                clean_me(fptr, arr, cnt);
                return FILE_NOT_OPEN;
            }

            Student* found_student = (Student*)malloc(sizeof(Student));
            if (find_by_id_1(arr, cnt, num, &found_student)) {
                printf("Found!");
                fprintf(fptr_out, "%s %s %s ", found_student[0].surname, found_student[0].name, found_student[0].group);
                int sum = 0;
                for (int i = 0; i < num_exam; i++) {
                    uch c = found_student[0].grades[i];
                    sum += c;
                }
                double res = sum / (double)num_exam;
                fprintf(fptr_out, "%f\n", res);
            }
            else {
                printf("Not found.");
            }
            free(found_student);
            fclose(fptr_out);
        }
        else if (choice == 4) {
            if (cnt == 0) {
                printf("\nEmpty array of students.\n");
            }

            if (argc != 3) {
                print_scs(INVALID_INPUT);
                clean_me(fptr, arr, cnt);
                return INVALID_INPUT;
            }

            FILE* fptr_out = fopen(argv[2], "w");
            if (fptr_out == NULL) {
                print_scs(FILE_NOT_OPEN);
                clean_me(fptr, arr, cnt);
                return FILE_NOT_OPEN;
            }

            for (int i = 0; i < cnt; i++) {
                double res = find_mean(arr[i].grades, num_exam);
                if (res - all_mean > 1e-6) {
                    fprintf(fptr_out, "%s %s\n", arr[i].surname, arr[i].name);
                }
            }

            fclose(fptr_out);
        }
        else if (choice == 5) {
            break;
        }
        else {
            printf("\nInvalid command.\n");
        }
    }

    clean_me(fptr, arr, cnt);

    return 0;
}

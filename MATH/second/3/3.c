#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>

typedef long long ll;

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

typedef struct {
    int row;
    int column;
} Data;

enum status_codes {
    OK = 1,
    INVALID_INPUT = 2,
    NO_MEMORY = -5,
    INVALID = -2,
    OVERFLOW_ = -3,
    UNDEFINED = -4,
    WARNING_UNUSED = 3,
    WARNING_SMALL = 4,
    FILE_NOT_OPEN = -1
};

void print_scs(int choice) {
    switch(choice) {
        case INVALID_INPUT:
            printf("Invalid input.\n");
            break;
        case OK:
            printf("Project finished successfully\n");
            break;
        case NO_MEMORY:
            printf("No memory left.\n");
            break;
        case INVALID: 
            printf("Invalid something.\n");
            break;
        case OVERFLOW_:
            printf("Overflow!\n");
            break;
        case UNDEFINED:
            printf("Error! What you're trying to calculate IS UNDEFINED or uses complex numbers.\n");
            break;
        case WARNING_UNUSED:
            printf("Warning! Not all input data was used.\n");
            break;
        case WARNING_SMALL:
            printf("Warning! Small values may result in near zero results.\n");
            break;
        case FILE_NOT_OPEN:
            printf("Couldn't open the file.\n");
            break;
        default:
            break;
    }
}

int count_next_line(const char* pattern) {
    int cnt = 0;
    for (int i = 0; pattern[i] != '\0'; i++) {
        if (pattern[i] == '\n') {
            cnt++;
        }
    }
    return cnt;
}

int count_pattern_in_files(Data** info, int** res, const char* pattern, int cnt, ...) {
    va_list args;
    va_start(args, cnt);

    int capacity = 1;
    *info = (Data*)malloc(sizeof(Data) * capacity);
    if (*info == NULL) {
        return NO_MEMORY;
    }

    *res = (int*)malloc(sizeof(int) * cnt);
    if (*res == NULL) {
        return NO_MEMORY;
    }

    int id_info = 0;
    for (int i = 0; i < cnt; i++) {
        const char* ptr = va_arg(args, const char*);

        FILE* fptr = fopen(ptr, "r");

        if (fptr == NULL) {
            (*res)[i] = FILE_NOT_OPEN;
            continue;
        }
        
        char* line = NULL;
        size_t len = 0;
        int cnt_all = 0, cnt = 0;
        int line_number = 1;

        while (getline(&line, &len, fptr) != -1) {
            char* line_ptr = line;
            int line_len = strlen(line);
            int pattern_len = strlen(pattern);

            for (int i = 0; i < line_len; i++) {
                if (line_ptr[i] == pattern[0]) {
                    bool match = 1;
                    
                    for (int j = 1; j < pattern_len && match; j++) {
                        if (i + j >= line_len || line_ptr[i + j] != pattern[j]) {
                            match = 0;
                        }
                    }

                    if (match) {
                        id_info++;
                        cnt_all++;
                        cnt++;

                        if (id_info > capacity) {
                            capacity *= 2;
                            *info = (Data*)realloc(*info, sizeof(Data) * capacity);
                            if (*info == NULL) {
                                return NO_MEMORY;
                            }
                        }

                        // printf("ZEROPROBLEM: id:%d %d %d\n", id_info, line_number, i + 1);

                        (*info)[id_info - 1].row = line_number;
                        (*info)[id_info - 1].column = i + 1;

                        // printf("EQUAL:%s", line_ptr);
                    }
                }
            }

            line_number++;
        }

        fclose(fptr);

        (*res)[i] = cnt;
    }

    va_end(args);

    return OK;
}

int main() {

    const char* pattern = "\n";
    int file_cnt = 3;

    Data* info;

    int* res;

    int status = count_pattern_in_files(&info, &res, pattern, file_cnt, "1.txt", "2.txt", "blank.txt");
    if (status != OK) {
        print_scs(status);
        return status;
    }
    // count_pattern_in_files(pattern, file_cnt, "space.txt");
    // count_pattern_in_files(pattern, file_cnt, "tab.txt");
    // count_pattern_in_files(pattern, file_cnt, "next_line.txt");

    int last = 0;
    for (int i = 0; i < file_cnt; i++) {
        printf("Number of occurences in the file №%d: %d\n", i + 1, res[i]);
        if (res[i] != FILE_NOT_OPEN) {
            for (int j = last; j < last + res[i]; j++) {
                printf("%d %d\n", info[j].row, info[j].column);
            }
            last += res[i];
        }
        else {
            print_scs(FILE_NOT_OPEN);
        }
    }

    free(res);
    free(info);

    return 0;
}

/* TASK 
Реализуйте функцию с переменным числом аргументов, принимающую в качестве входных параметров подстроку и пути к файлам. 
Необходимо чтобы для каждого файла функция производила поиск всех вхождений переданной подстроки в содержимом этого файла. 
При реализации запрещается использование функций strstr и strncmp из заголовочного файла string.h. 

Продемонстрируйте работу функции,
также организуйте наглядный вывод результатов работы функции: для каждого файла, путь к которому передан как параметр Вашей функции,
для каждого вхождения подстроки в содержимое файла необходимо вывести номер строки (индексируется с 1) и номер символа в строке файла,
начиная с которого найдено вхождение подстроки. В подстроку могут входить любые символы (обратите внимание, что в подстроку также могут
входить символы пробела, табуляций, переноса строки, в неограниченном количестве).
*/
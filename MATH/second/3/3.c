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

enum status_codes {
    OK = 1,
    INVALID_INPUT = -1,
    NO_MEMORY = -2,
    INVALID = -3,
    OVERFLOW_ = -4
};

void print_scs(int choice) {
    switch(choice) {
        case 2:
            printf("Invalid input.\n");
            break;
        case 1:
            printf("Project finished successfully\n");
            break;
        case -1:
            printf("No memory left.\n");
            break;
        case -2: 
            printf("Invalid something.\n");
            break;
        case -3:
            printf("Overflow!\n");
            break;
        default:
            break;
    }
}

/////////////////////// validations ///////////////////////////

////////////////////main functions////////////////////////


int count_next_line(const char* pattern) {
    int cnt = 0;
    for (int i = 0; pattern[i] != '\0'; i++) {
        if (pattern[i] == '\n') {
            cnt++;
        }
    }
    return cnt;
}

int* count_pattern_in_files(const char* pattern, int cnt, ...) {
    va_list args;
    va_start(args, cnt);

    int* res = (int*)malloc(sizeof(int) * cnt);

    for (int i = 0; i < cnt; i++) {
        const char* ptr = va_arg(args, const char*);

        FILE* fptr = fopen(ptr, "r");

        if (fptr == NULL) {
            printf("lol didnt read: %s \n", ptr);
            res[i] = INVALID_INPUT;
            continue;
        }

        printf("Occurences in file %s:\n", ptr);

        char ch;
        int cnt = 0, ind = 0, pattern_len = strlen(pattern), row = 1, col = 1;
        while ((ch = fgetc(fptr)) != EOF) {
            col++;
            if (ch == '\n') {
                row++;
                col = 1;
            }
            if (ch == pattern[ind]) {
                ind++;
                if (ind == pattern_len) {
                    cnt++;
                    ind = 0;
                    printf("%d %d\n", row, col - pattern_len + count_next_line(pattern));
                }
            } 
            else {
                ind = 0;
            }
        }

        fclose(fptr);

        res[i] = cnt;
    }

    va_end(args);

    return res;
}

int main() {

    const char* pattern = "kawaii";
    int file_cnt = 3;

    int* res = count_pattern_in_files(pattern, file_cnt, "1.txt", "2.txt", "3.txt");
    // int* res = count_pattern_in_files(pattern, file_cnt, "space.txt");
    // int* res = count_pattern_in_files(pattern, file_cnt, "tab.txt");
    // int* res = count_pattern_in_files(pattern, file_cnt, "next_line.txt");

    for (int i = 0; i < file_cnt; i++) {
        printf("Number of occurences of pattern \"%s\" in file #%d: ", pattern, i + 1);
        if (res[i] != -1) {
            printf("%d\n", res[i]);
        }
        else {
            printf("- \n");
        }
    }

    free(res);

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
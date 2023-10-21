#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>
#include <string.h>

typedef long long ll;

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

enum status_codes {
    OK = 1,
    INVALID_INPUT = 2,
    NO_MEMORY = -1,
    INVALID = -2,
    OVERFLOW_ = -3
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

bool is_valid_flag(char ch[]) {
    int command_cnt = 5;
    char commands[5] = {'l', 'r', 'u', 'n', 'c'};

    int ind = -1;
    if (ch[0] == '-') {
        for (ll i = 0; i < command_cnt; i++) {
            if (ch[1] == commands[i]) {
                ind = i; // keep the index of the command we need to execute
                break; // Exit the loop when a valid command is found
            }
        }
    }

    if (ind == -1) {
        return false;
    }

    return true;
}

bool is_valid_integer(char ch[]) {
    // тк unsigned int
    if (ch[0] == '-') {
        return 0;
    }
    
    int i = 0;

    while (ch[i] == '0') {
        i++;
    }

    int prev = i;
    if (strlen(ch) - i > 9) {
        return 0;
    }

    for (; ch[i] != '\0'; i++) {
        if (!isdigit(ch[i])) {
            return 0;
        }
    }

    return 1;
}   

bool is_alpha(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? 1 : 0;
}

bool is_lower(char c) {
    return (c >= 'a' && c <= 'z') ? 1 : 0;
}

bool is_digit(char c) {
    return (c >= '0' && c <= '9') ? 1 : 0;
}

////////////////////main functions////////////////////////

void find_length(int* res, char ch[]) {
    for (int i = 0; ch[i] != '\0'; i++) {
        (*res)++;
    }
}

void reverse_string(int len, char ch[]) {
    int begin = 0, end = len - 1;
    while (begin < end) {
        char tmp = ch[begin];
        ch[begin] = ch[end];
        ch[end] = tmp;
        begin++;
        end--;
    }
}

void to_upper(char* ptr) {
    *ptr = (char)((int)*ptr - 32);
}

void even_to_upper(char ch[]) {
    for (int i = 0; ch[i] != '\0'; i++) {
        if ((i & 1) && is_lower(ch[i])) {
            to_upper(&ch[i]);
        }
    }
}

void custom_string_sort(char* res, char *input) {
    int len = 0;
    find_length(&len, input);

    int digit_cnt = 0;
    int letter_cnt = 0;
    int other_cnt = 0;

    // calc amount of occurences of letters, digits, other symbols
    for (int i = 0; i < len; i++) {
        char c = input[i];
        if (is_digit(c)) {
            digit_cnt++;
        } else if (is_alpha(c)) {
            letter_cnt++;
        } else {
            other_cnt++;
        }
    }

    // find positions of each starting point in the array
    int fi = 0;
    int se = digit_cnt;
    int th = se + letter_cnt;

    // sort it out (kinda)
    for (int i = 0; i < len; i++) {
        char c = input[i];
        if (is_digit(c)) {
            res[fi] = c;
            fi++;
        } else if (is_alpha(c)) {
            res[se] = c;
            se++;
        } else {
            res[th] = c;
            th++;
        }
    }
    res[len] = '\0';
}

int order(int* arr, int seed, int size) {

    if (size < 1) {
        return INVALID_INPUT;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }

    srand(seed);

    // тасование фишера-йетса
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    return OK;
}

void concat_string(int* last, char st[], char ch[]) {
    for (int i = 0; st[i] != '\0'; i++) {
        ch[(*last)++] = st[i]; 
    }
}

/////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {

    if (!is_valid_flag(argv[1])) {
        print_scs(INVALID_INPUT);
        return INVALID_INPUT;
    }

    char choice = argv[1][1];

    if (choice != 'c') {
        if (argc != 3) {
            print_scs(INVALID_INPUT);
            return INVALID_INPUT;
        }
    }

    switch(choice) {
        case 'l': {
            int len = 0;
            find_length(&len, argv[2]);

            printf("Length: %d\n", len);

            break;
        }
        case 'r': {
            int len = 0;
            find_length(&len, argv[2]);

            char* reversed = argv[2];

            reverse_string(len, reversed);

            printf("Reversed: %s\n", reversed);

            break;
        }
        case 'u': {
            char* ch = argv[2];
            
            even_to_upper(ch);
            
            printf("Result: %s\n", ch);

            break;
        }
        case 'n': {
            int len = 0;
            find_length(&len, argv[2]);
  
            char res[len + 1]; // Create a result string with enough space
            custom_string_sort(res, argv[2]);

            printf("Initial: %s\nResult: %s\n", argv[2], res);

            break;
        }
        case 'c': {
            // ./a.out -c seed num st_1 … st_num

            if (!is_valid_integer(argv[2]) || !is_valid_integer(argv[3])) {
                print_scs(INVALID_INPUT);
                return INVALID_INPUT;
            }

            int num = atoi(argv[3]); // кол-во строк для конкатенации

            if (argc != num + 4) {
                print_scs(INVALID_INPUT);
                return INVALID_INPUT;
            }

            int seed = atoi(argv[2]);

            int* arr_order = (int*)malloc(sizeof(int) * num);
            if (arr_order == NULL) {
                print_scs(NO_MEMORY);
                return NO_MEMORY;
            }

            // arr_order содержит сгенеренный порядок строк            
            order(arr_order, seed, num);

            // находим полную длину = сумму длин строк
            int full_len = 0;
            for (int i = 0; i < num; i++) {
                int l = 0;
                find_length(&l, argv[i + 4]);
                full_len += l;
            }

            // выделяем память под сконкатенированную строку на длину full_length
            char* concat = (char*)malloc(sizeof(char) * full_len);
            if (concat == NULL) {
                print_scs(NO_MEMORY);
                return NO_MEMORY;
            }

            // argv[arr_order[i] + 4] , arr_order[i] содержит номер позиции рандомной строки
            int last = 0;
            for (int i = 0; i < num; i++) {
                concat_string(&last, argv[arr_order[i] + 4], concat);
            }

            printf("Res: %s\n", concat);

            free(arr_order);
            free(concat);

            break;
        }
    } 

    return 0;
}

/* TASK 

*/
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))

bool is_digit(char ch) {
    return (ch >= '0' && ch <= '9') ? 1 : 0;
}

bool is_letter(char ch) {
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) ? 1 : 0;
}

bool is_number(char st[]) {
    
    for (int i = 0; st[i] != '\0'; i++) {
        if (!is_digit(st[i]) && !is_letter(st[i])) {
            return 0;
        }
    }

    if (strlen(st) > 19) {
        return 0;
    }

    return 1;
}

bool is_uppercase(char ch) {
    return (ch >= 'a' && ch <= 'z') ? 1 : 0;
}

int find_min_base(char st[]) {
    char ch_num = '-', ch_letter = '-';
    for (int i = 0; st[i] != '\0'; i++) {
        if (st[i] > ch_num && is_digit(st[i])) {
            ch_num = st[i];
        }
        else if (st[i] > ch_letter && is_letter(st[i])) {
            ch_letter = st[i];
        }
    }

    if (ch_letter != '-' && !is_uppercase(ch_letter)) {
        ch_letter = (char)((int)ch_letter + 32); // to_lowercase
    }

    char alpha[] = "abcdefghijklmnopqrstuvwxyz";

    int res = 0;

    if (ch_letter != '-' && ch_num == '-') {
        for (int i = 0; alpha[i] != '\0'; i++) {
            if (ch_letter == alpha[i]) {
                res = i + 11;
            }
        }
    }
    else if (ch_num != '-' && ch_letter == '-') {
        res = (ch_num - '0') + 1;
    }
    else if (ch_num != '-' && ch_letter != '-') {
        int res1 = 0;
        for (int i = 0; alpha[i] != '\0'; i++) {
            if (ch_letter == alpha[i]) {
                res1 = i + 11;
            }
        }
        int res2 = (ch_num - '0') + 1;

        res = MAX(res1, res2);
    }
    return res;
}

int to_decimal(char ch[], int base) {

    int MAX_INT = INT_MAX;

    char alpha[] = "abcdefghijklmnopqrstuvwxyz";

    int size = 0;
    for (int i = 0; ch[i] != '\0'; i++) {
        size++;
    }

    int decimal = 0;
    int i, j, mn = 1;
    for (i = size - 1, j = 0; i >= 0; i--, j++) {
        int a = decimal, b = (ch[j] - '0') * pow(base, i);
        decimal += (ch[j] - '0') * pow(base, i);
        int result = decimal;
        if (__builtin_add_overflow(a, b, &result)) {
            return -1;
        }
    }

    return decimal;
}

bool is_valid_lexeme(char st[]) {

    for (int i = 0; st[i] != '\0'; i++) {
        if (!is_digit(st[i]) && !is_letter(st[i])) {
            return 0;
        }
    }

    if (strlen(st) > 19) {
        return 0;
    }

    return 1;
}

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("Invalid amount of arguments. Usage: %s <file_route> \n", argv[0]);
        return 1;
    }

    char input_file[257];
    char output_file[257];

    strcpy(input_file, argv[1]);
    strcpy(output_file, argv[2]);

    FILE* fptr = fopen(input_file, "r");
    FILE* fptr_out = fopen(output_file, "w");

    if (fptr == NULL || fptr_out == NULL) {
        printf("Can't open the file. \n");
        return 1;
    }

    char ch[BUFSIZ];

    while (fscanf(fptr, "%s", ch) != EOF) {
        if (is_valid_lexeme(ch)) {
            int base = find_min_base(ch); 

            int i = 0;
            for (; ch[i] == '0'; i++) {
                continue;
            }

            while (ch[i] != '\0') {
                fprintf(fptr_out, "%c", ch[i]);
                i++;
            }
            fprintf(fptr_out, " ");

            fprintf(fptr_out, "%d ", base);

            // fprintf(fptr_out, "\n");

            int dec_num = to_decimal(ch, base);

            if (dec_num < 0) {
                printf("Error! Integer overflow.\n");
                return 1;
            }

            fprintf(fptr_out, "%d \n", dec_num);
        }
        else {
            for (int i = 0; ch[i] != '\0'; i++) {
                fprintf(fptr_out, "%c", ch[i]);
            }
            fprintf(fptr_out, " = Not a number.\n");
        }

    }

    fclose(fptr);
    fclose(fptr_out);

    return 0;
}

/*
найти максимальную цифру или букву - это составит минимальную систему счисления

*/
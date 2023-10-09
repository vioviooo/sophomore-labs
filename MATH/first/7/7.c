#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

bool is_letter(char ch) {
    return (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z') ? 1 : 0;
}

bool is_valid_lexeme(char ch) {
    return (ch == ' ' || ch == '\n') ? 0 : 1;
}

bool is_uppercase(char ch) {
    return (ch >= 'A' && ch <= 'Z') ? 1 : 0;
}

int dec_to_eighth(int n) {
    int arr[10];
    int i = 0;

    while (n != 0) {
        arr[i] = n % 8;
        n /= 8;
        i++;
    }

    int num = 0, d = 1;
    for (int j = 0; j < i; j++) {
        num = arr[j] * d + num;
        d *= 10;
    }

    return num;
}

int dec_to_fourth(int n) {
    int arr[BUFSIZ];
    int i = 0;

    while (n != 0) {
        arr[i] = n % 4;
        n /= 4;
        i++;
    }

    int num = 0, d = 1;
    for (int j = 0; j < i; j++) {
        num = arr[j] * d + num;
        d *= 10;
    }

    return num;
}

int main(int argc, char* argv[]) {

    char choice = '0';
    if (argv[1][2] == '\0' && (argv[1][0] == '/' || argv[1][0] == '-')) {
        if (argv[1][1] == 'r') {
            choice = 'r';
        } else if (argv[1][1] == 'a') {
            choice = 'a';
        }
    }

    if (choice == '0') {
        printf("Invalid flag. \n");
        return 1;
    }

    if (choice == 'r') {

        if (argc != 5) {
            printf("Invalid amount of arguments. Usage: %s <flag> <file1_route> <file2_route> <route_out> \n", argv[0]);
            return 1;
        }

        char input_file1[257];
        strcpy(input_file1, argv[2]);

        char input_file2[257];
        strcpy(input_file2, argv[3]);

        char output_file[257];
        strcpy(output_file, argv[4]);

        FILE* fptr1 = fopen(input_file1, "r");
        FILE* fptr2 = fopen(input_file2, "r");
        FILE* fptr_out = fopen(output_file, "w");

        if (fptr1 == NULL || fptr2 == NULL || fptr_out == NULL) {
            printf("Error! File couldn't be opened.\n");
            return 1;
        }

        char word[100]; // longest english word consists of 45 letters
        bool parity = 1, flag1 = true, flag2 = true;
        while (flag1 && flag2) {
            if (parity) {
                if (fscanf(fptr1, "%s", word) == EOF) {
                    flag1 = false;
                } 
                else {
                    fprintf(fptr_out, "%s ", word);
                }   
            }
            else {
                if (fscanf(fptr2, "%s", word) == EOF) {
                    flag2 = false;
                } 
                else {
                    fprintf(fptr_out, "%s ", word);
                } 
            }
            parity = !parity;
        }

        while (fscanf(fptr1, "%s", word) != EOF) {
            fprintf(fptr_out, "%s ", word);
        }

        while (fscanf(fptr2, "%s", word) != EOF) {
            fprintf(fptr_out, "%s ", word);
        }

        fclose(fptr1);
        fclose(fptr2);
        fclose(fptr_out);
    }
    else {
        char input_file[257];
        char output_file[257];

        if (argc != 4) {
            printf("Invalid amount of arguments. Usage: %s <flag> <file_route> <route_out> \n", argv[0]);
            return 1;
        }

        strcpy(input_file, argv[2]);
        strcpy(output_file, argv[3]);

        FILE* fptr = fopen(input_file, "r");
        FILE* fptr_out = fopen(output_file, "w");

        if (fptr == NULL || fptr_out == NULL) {
            printf("Error! File couldn't be opened.\n");
        }

        char ch;
        int cnt = 0;
        while ((ch = fgetc(fptr)) != EOF) {
            cnt++;
            if (cnt % 10 == 0 && is_letter(ch)) {
                if (is_uppercase(ch)) {
                    ch = (char)((int)ch + 32);
                }
                int num = dec_to_fourth((int)ch);
                fprintf(fptr_out, "%d ", num);
            }
            else if (cnt % 2 == 0 && is_letter(ch)) {
                if (is_uppercase(ch)) {
                    ch = (char)((int)ch + 32);
                }
                fprintf(fptr_out, "%c ", ch);
            }
            else if (cnt % 5 == 0 && is_valid_lexeme(ch)) {
                int num = dec_to_eighth((int)ch);
                fprintf(fptr_out, "%d ", num);
            }
        }

        fclose(fptr);
        fclose(fptr_out);
    }

    return 0;
}
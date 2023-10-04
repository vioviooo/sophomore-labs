#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

bool is_digit(char ch) 
{
    return (ch >= '0' && ch <= '9') ? 1 : 0;
}

bool is_valid(char ch) 
{
    return ((ch == ' ') || is_digit(ch) || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) ? 0 : 1;
}

bool is_letter(char ch) 
{
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) ? 1 : 0;
}

int main(int argc, char* argv[]) 
{
    if (argc < 3 || argc > 4) 
    {
        printf("Invalid amount of arguments. Usage: %s <flag> <input_file> [output_file]\n", argv[0]);
        return 1;
    }

    int num_of_flags = 4;
    char* flags[] = {"d", "i", "s", "a"};

    int ind = -1;

    if (strlen(argv[1]) == 2) 
    {
        for (int i = 0; i < num_of_flags && argv[1][2] == '\0' && (argv[1][0] == '/' || argv[1][0] == '-'); i++) 
        {
            if (argv[1][1] == *flags[i]) // ??
            {
                ind = i;
            }
        }
    }
    else if (strlen(argv[1]) == 3)
    {
        for (int i = 0; i < num_of_flags && argv[1][1] == 'n' && argv[1][3] == '\0' && (argv[1][0] == '/' || argv[1][0] == '-'); i++) 
        {
            if (argv[1][2] == *flags[i]) // ??
            {
                ind = i;
            }
        }
    }
    
    if (ind == -1) 
    {
        printf("Invalid command. Try again.\n");
        return 1;
    }

    char input_file[256];
    char output_file[256];

    if (argc == 3) 
    {
        strcpy(output_file, "out_");
        strcat(output_file, argv[2]);
    } 
    else 
    {
        strcpy(output_file, argv[3]);
    }

    strcpy(input_file, argv[2]);

    FILE* fptr = fopen(input_file, "r");
    FILE* fptr_out = fopen(output_file, "w");

    if (fptr == NULL || fptr_out == NULL) 
    {
        printf("File couldn't be opened. \n");
        return 1;
    }

    char ch;
    int cnt = 0;

    switch(ind) 
    {
        case 0: 
        {
            while ((ch = fgetc(fptr)) != EOF) 
            {
                if (!is_digit(ch)) 
                {
                    fprintf(fptr_out, "%c", ch);
                }
            }
            fclose(fptr_out);
            fclose(fptr);

            break;
        }
        case 1:
        {
            while ((ch = fgetc(fptr)) != EOF) 
            {
                if (ch == '\n') 
                {
                    fprintf(fptr_out, "%d \n", cnt);
                    cnt = 0;
                }
                else 
                {
                    if (is_letter(ch)) 
                    {
                        cnt++;
                    }
                }
            }
            if (cnt != 0) {
                fprintf(fptr_out, "%d \n", cnt);
            }
            break;
        }
        case 2:
        {
            while ((ch = fgetc(fptr)) != EOF) 
            {
                if (ch == '\n') 
                {
                    fprintf(fptr_out, "%d \n", cnt);
                    cnt = 0;
                } 
                else if (is_valid(ch)) 
                {
                    cnt++;
                }
            }
            if (cnt != 0) { // condition for the very last line
                fprintf(fptr_out, "%d \n", cnt);
            }
            break;
        }
        case 3:
            while ((ch = fgetc(fptr)) != EOF) {
                if (!is_digit(ch)) {
                    fprintf(fptr_out, "%x ", (int)ch);
                }
                else 
                {
                    fprintf(fptr_out, "%c ", ch);
                }
            }
            break;
    }

    return 0;
}
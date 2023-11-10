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
#include "bst.c"
#include "interaction.c"

enum status_codes {
    OKAY = 1,
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
        case OKAY:
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

bool is_valid_integer(char ch[]) {
    int i = 0;

    if (ch[0] == '-' && ch[1] == '\0') {
        return 0;
    }
    else if (ch[0] == '-') {
        i = 1;
    }

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

// TODO
int is_valid_char(char ch[]) {
    // if (ch[0] == ' ' && ch[1] == '\0') {
    //     return 1;
    // }
    // if (ch[0] == '\n' && ch[1] == '\0') {
    //     return 2;
    // }
    // if (ch[0] == '\'' && ch[1] == 't' && ch[2] == '\0') {
    //     return 3;
    // }
    if (ch[1] != '\0') {
        return 0;
    }
    return 1;
}

int main(int argc, char* argv[]) {

    if (argc < 3) {
        print_scs(INVALID_INPUT);
        return INVALID_INPUT;
    }
    // !!! null termiante strings
    char* filename = argv[1];

    int capacity_sep = BUFSIZ;
    char* separators = (char*)calloc(capacity_sep + 1, sizeof(char));
    if (separators == NULL) {
        print_scs(NO_MEMORY);
        return NO_MEMORY;
    }

    for (int i = 0; i <= capacity_sep; i++) {
        separators[i] = '\0';
    }

    int cnt_sep = 0;
    for (int i = 2; argv[i] != NULL; i++) {
        int type;
        if ((type = is_valid_char(argv[i])) == 0) {
            print_scs(INVALID_INPUT);
            return 0;
        }
        separators[i - 2] = *argv[i]; // $'\n'
        if (i - 2 >= capacity_sep) {
            capacity_sep *= 2;
            char* tmp = (char*)realloc(separators, sizeof(char) * (capacity_sep + 1));
            if (tmp == NULL) {
                free(separators);
                print_scs(NO_MEMORY);
                return NO_MEMORY;
            }
            separators = tmp;
            separators[capacity_sep] = '\0';
        }
        cnt_sep++;
    }

    FILE* fptr = fopen(filename, "r");
    if (!fptr) {
        free(separators);
        print_scs(INVALID_INPUT_FILE);
        return INVALID_INPUT_FILE;
    }

    Node* root = NULL;

    int capacity_str = 2, cnt_str = 0;
    char* my_word = (char*)calloc(capacity_str, sizeof(char));
    if (my_word == NULL) {
        print_scs(NO_MEMORY);
        return NO_MEMORY;
    }

    char c;
    while ((c = fgetc(fptr)) != EOF) {
        bool flag = true;
        for (int i = 0; i < cnt_sep && flag; i++) {
            if (c == separators[i]) {
                flag = false;
            }
        }
        if (!flag) {
            if (strlen(my_word) != 0) {
                root = insert_word(root, my_word);
                printf("String: %s %d\n", my_word, cnt_str);
            }
            for (int i = 0; i < cnt_str; i++) {
                my_word[i] = '\0'; 
            }
            my_word[cnt_str] = '\0';
            cnt_str = 0;
        } else {
            if (cnt_str >= capacity_str - 1) { // Check if we need to reallocate
                capacity_str *= 2;
                char* tmp = (char*)realloc(my_word, capacity_str * sizeof(char));
                if (tmp == NULL) {
                    free(my_word);
                    print_scs(NO_MEMORY);
                    return NO_MEMORY;
                }
                my_word = tmp;
                tmp = NULL;
            }
            my_word[cnt_str] = c;
            cnt_str++;
        }
    }

    printf("String: %s %lu\n", my_word, strlen(my_word));
    if (strlen(my_word) != 0) {
        printf("HERE");
        root = insert_word(root, my_word);
    }
    
    // interactive part starts
    int option;
    while (true) {
        print_default_menu();
        if (scanf("%d", &option) != 1) {
            print_scs(INVALID_INPUT);
            return INVALID_INPUT;
        }
        printf("\n\n");
        if (option == 3) {
            char* longest = "";
            char* shortest = longest;
            find_longest_word(root, &longest);
            find_shortest_word(root, &shortest);
            printf("Longest: %s, shortest: %s\n", longest, shortest);
        } else if (option == 4) {
            printf("Please, enter the word you want to find: ");
            char user_word[BUFSIZ];
            if (scanf("%s", user_word) != 1) {
                return INVALID_INPUT;
            }
            int cnt_ocurr = cnt_frequency(root, user_word);
            if (cnt_ocurr == 0) {
                printf("The word isn't present in the file.\n");
            } else {
                printf("The word is present in the file.\n");
            }
        } else if (option == 1) {
            print_all_frequency(root);
        } else if (option == 2) {
            // TODO!!!!
        }

        if (option == 5) {
            break;
        }
    }

    // free the tree
    free_bst(root);

    // free strings
    free(my_word);
    free(separators);

    // close file
    fclose(fptr);

    return 0;
}

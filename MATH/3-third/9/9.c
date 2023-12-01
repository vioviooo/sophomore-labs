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
#include "header.h"
#include "interaction.c"

// enum status_codes {
//     OKAY = 1,
//     ERROR = -2,
//     INVALID_INPUT = 2,
//     INVALID_INPUT_FILE = -6,
//     NO_MEMORY = -1,
//     OVERFLOW_ = -3,
//     UNDEFINED = -4,
//     FILE_NOT_OPEN = -5
// };

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

int load_tree(Node** root, FILE* fptr) {
    char word[BUFSIZ];
    int count;
    
    while (fscanf(fptr, "%s %d", word, &count) == 2) {
        *root = extract_tree(*root, word, count);
    }

    if (!feof(fptr)) {
        return INVALID_INPUT_FILE;
    }

    return OKAY;
}

void get_maximum_count(Node* root, int * count) {
    if (!root) {
        return;
    }

    if (root->left) {
        get_maximum_count(root->left, count);
    }

    if (root->count > *count) {
        *count = root->count;
    }

    if (root->right) {
        get_maximum_count(root->right, count);
    }
}

void print_nodes(Node* root, int * quantity, int length) {
    if (!root) {
        return;
    }

    if (root->right) {
        print_nodes(root->right, quantity, length);
    }

    if (root->count == length && (*quantity)) {
        (*quantity)--;
        printf("%s Frequency = %d\n", root->word, root->count);
    }

    if (root->left) {
        print_nodes(root->left, quantity, length);
    }
}

void print_most_quantity(Node* root, int n) {
    int count = 0;
    get_maximum_count(root, &count);
    while (n != 0 && count != 0) {
        print_nodes(root, &n, count);
        count--;
    }
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

    strcpy(my_word, "");

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

    // printf("String: %s %lu\n", my_word, strlen(my_word));
    if (strlen(my_word) != 0) {
        root = insert_word(root, my_word);
    }
    
    // interactive part starts
    int option;
    while (true) {
        print_default_menu();
        if (scanf("%d", &option) != 1) {
            print_scs(INVALID_INPUT);
            break;
        }

        printf("\n\n");
        if (option == 3) {
            if (root == NULL) {
                printf("Empty tree.\n");
            } else {
                char* longest = "";
                char* shortest = NULL;

                find_longest_word(root, &longest);
                find_shortest_word(root, &shortest);

                printf("Longest: %s, shortest: %s\n", longest, shortest);
            }
        } 
        else if (option == 4) {
            printf("Please, enter the word you want to find: ");

            char user_word[BUFSIZ];
            if (scanf("%s", user_word) != 1) {
                print_scs(INVALID_INPUT);
                break;
            }

            int cnt_ocurr = cnt_frequency(root, user_word);
            if (cnt_ocurr == 0) {
                printf("The word isn't present in the file.\n");
            } 
            else {
                printf("The word is present in the file.\n");
            }
        } 
        else if (option == 1) {
            if (root == NULL) {
                printf("Empty tree.\n");
            }
            else {
                print_all_frequency(root);
            }
        } 
        else if (option == 6) { // save into file
            printf("Please, enter filename where to save: ");

            char file_save[BUFSIZ];
            if (scanf("%s", file_save) != 1) {
                print_scs(INVALID_INPUT);
                break;
            }

            if (strcmp(file_save, argv[1]) == 0) {
                printf("\nError! Files are the same\n");
                break;
            }
            else {
                FILE* fptr_w = fopen(file_save, "w");
                if (fptr_w == NULL) {
                    print_scs(FILE_NOT_OPEN);
                    break;
                }

                preorder_dfs(root, fptr_w);
                printf("I did it.");
                fclose(fptr_w);
            }
        } 
        else if (option == 7) {
            printf("Please, enter filename from where to extract: ");

            char file_extract[BUFSIZ];
            if (scanf("%s", file_extract) != 1) {
                print_scs(INVALID_INPUT);
                break;
            }

            if (strcmp(file_extract, argv[1]) == 0) {
                printf("\nError! Files are the same\n");
                break;
            }
            else {
                FILE* fptr = fopen(file_extract, "r");
                if (fptr == NULL) {
                    print_scs(FILE_NOT_OPEN);
                    break;
                }

                free_bst(root);

                root = NULL;

                load_tree(&root, fptr);

                fclose(fptr);
            }
        } else if (option == 5) {
            if (root == NULL) {
                printf("Empty tree.\n");
            } else {
                int height = find_height(root);
                printf("Height of the tree: %d\n", height);
                // preorder_dfs(root, stdout);
            }
        } else if (option == 2) { // find N most popular words in the bst
            if (root == NULL) {
                printf("Empty tree.\n");
            }
            else {
                char* words; // result
                // int res = find_most_frequent(root, 0);
                int n;
                printf("Please, enter how many words: ");
                if (scanf("%d", &n) != 1) {
                    print_scs(INVALID_INPUT);
                    break;
                }
                printf("\n");
                print_most_quantity(root, n);
            }
        } else if (option == 8) {
            printf("Exited the program.");
            break;
        } else {
            printf("Invalid command.\n");   
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

int is_valid_char(char ch[]) {
    if (ch[1] != '\0') {
        return 0;
    }
    return 1;
}

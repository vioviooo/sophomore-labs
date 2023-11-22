#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.c"
#include "header.h"

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("Invalid input.\n");
        return 1;
    }

    if (*argv[1] == *argv[2]) {
        printf("The files for input and output are the same.\n");
        return 1;
    }

    char* file_input = argv[1];
    FILE* fptr_in = fopen(file_input, "r");
    if (!fptr_in) {
        return 1;
    }

    char* file_output = argv[2];
    FILE* fptr_out = fopen(file_output, "w");
    if (!fptr_out) {
        fclose(fptr_in);
        return 1;
    }

    int capacity = 2, cnt_sym = 0;
    char* seq = (char*)calloc(capacity, sizeof(char));
    if (seq == NULL) {
        return NO_MEMORY;
    }

    struct Node* root = NULL;

    char c;
    while ((c = fgetc(fptr_in)) != EOF) {
        if (c == '\n') {
            if (strlen(seq) != 0) {
                root = bracket_to_tree(seq);
                print_tree(root, 0, fptr_out);
                fprintf(fptr_out, "\n\n");
            }
            for (int i = 0; i < capacity; i++) {
                seq[i] = '\0';
            }
            cnt_sym = 0;
        }
        else {
            if (cnt_sym >= capacity - 1) {
                capacity *= 2;
                char* tmp = (char*)realloc(seq, (capacity + 1) * sizeof(char));
                if (tmp == NULL) {
                    free(seq);
                    return NO_MEMORY;
                }
                seq = tmp;
                seq[cnt_sym] = '\0';
            }
            seq[cnt_sym] = c;
            cnt_sym++;
        }
    }

    if (strlen(seq) != 0) {
        root = bracket_to_tree(seq);
        print_tree(root, 0, fptr_out);
    }

    free_tree(root);

    fclose(fptr_in);
    fclose(fptr_out);

    return 0;
}
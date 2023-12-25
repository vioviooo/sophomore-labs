#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "functions.c"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Invalid input. Usage: %s <input_file>\n", argv[0]);
        return INVALID_INPUT;
    }

    FILE* fptr = fopen(argv[1], "r+");
    if (fptr == NULL) {
        print_scs(FILE_NOT_OPEN);
        return FILE_NOT_OPEN;
    }

    HashMap* mp;

    int status;
    if ((status = init_hashmap(HASHSIZE, &mp)) != OK) {
        print_scs(status);
        return status;
    }

    char word[MAX_WORD_LEN];
    char replace[MAX_WORD_LEN];
    int cnt_define = 0;
    char line[MAX_LINE_LEN];

    while (fgets(line, sizeof(line), fptr) != NULL) {
        if (line[0] == '#' && sscanf(line, "#define %s %s", word, replace) == 2) {
            if ((status = insert_word(mp, word, replace)) != OK) {
                print_scs(status);
                break;
            }
            cnt_define++;
        }
    }

    fseek(fptr, 0, SEEK_SET);

    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        fclose(fptr);
        free_hashmap(mp);
        print_scs(FILE_NOT_OPEN);
        return FILE_NOT_OPEN;
    }

    while (fgets(line, sizeof(line), fptr) != NULL) {
        replace_word(line, outputFile, mp);
    }

    fclose(outputFile);

    free_hashmap(mp);

    fclose(fptr);

    return 0;
}
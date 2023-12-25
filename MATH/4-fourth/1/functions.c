#include "libs.h"

enum status_codes {
    OK = -100,
    NO_MEMORY = -1,
    INVALID_INFIX = -2,
    UNBALANCED_BRACKETS = -3,
    EMPTY_FILE = -4,
    INVALID_INPUT = -5,
    FILE_NOT_OPEN = -6,
    INVALID_BASE = -7
};

void print_scs(int choice) {
    switch (choice) {
        case INVALID_INFIX:
            printf("\nERROR: INVALID INFIX EXPRESSION\n");
            break;
        case OK:
            printf("\nProject finished successfully!\n");
            break;
        case NO_MEMORY:
            printf("\nERROR: NO MEMORY\n");
            break;
        case UNBALANCED_BRACKETS:
            printf("\nERROR: UNBALANCED PARENTHESES\n");
            break;
        case EMPTY_FILE:
            printf("\nNOTICE: EMPTY FILE\n");
            break;
        case INVALID_INPUT:
            printf("\nERROR: INVALID INPUT\n");
            break;
        case FILE_NOT_OPEN:
            printf("\nERROR: FILE WAS NOT OPEN\n");
            break;
        case INVALID_BASE:
            printf("\nERROR: INVALID BASE\n");
            break;
        default:
            break;
    }
}

int insert_word(struct HashMap* mp, char* name, char* value) {
    int index = hash_function(mp, name);

    Macro* new_macro = (Macro*)malloc(sizeof(struct Macro));
    if (new_macro == NULL) {
        return NO_MEMORY;
    }
    new_macro->name = strdup(name);
    new_macro->value = strdup(value);
    new_macro->next = mp->table[index];
    mp->table[index] = new_macro;
    mp->size++;

    int status;
    if (mp->size > 2 * mp->capacity) {
        if ((status = rehash(mp)) != OK) {
            return status;
        }
    }

    return OK;
}

int rehash(struct HashMap* mp) {
    int new_cap = mp->capacity * 2;

    Macro** tmp_table = malloc(sizeof(Macro*) * HASHSIZE);
    if (tmp_table == NULL) {
        return NO_MEMORY;
    }

    memcpy(tmp_table, mp->table, sizeof(Macro*) * HASHSIZE);

    mp->capacity = new_cap;
    mp->size = 0;

    for (int i = 0; i < HASHSIZE; i++) {
        Macro* curr_macro = tmp_table[i];
        while (curr_macro != NULL) {
            Macro* next_macro = curr_macro->next;
            insert_word(mp, curr_macro->name, curr_macro->value);
            free(curr_macro->name);
            free(curr_macro->value);
            free(curr_macro);
            curr_macro = next_macro;
        }
    }
    free(tmp_table);
    return OK;
}

void free_hashmap(struct HashMap* mp) {
    for (int i = 0; i < HASHSIZE; i++) {
        Macro* curr_macro = mp->table[i];
        while (curr_macro != NULL) {
            Macro* next_macro = curr_macro->next;
            free(curr_macro->name);
            free(curr_macro->value);
            free(curr_macro);
            curr_macro = next_macro;
        }
        mp->table[i] = NULL;
    }
    free(mp);
}

int hash_function(struct HashMap* mp, char* key) {
    
    int res = 0, power = 1;
    char symbol;
    for (int i = 0; i < (int)strlen(key); i++) {
        int charValue;

        if (key[i] >= '0' && key[i] <= '9') {
            charValue = key[i] - '0';
        } else if ('A' <= key[i] && key[i] <= 'Z') {
            charValue = key[i] - 'A' + 10;
        } else if ('a' <= key[i] && key[i] <= 'z') {
            charValue = key[i] - 'a' + 36;
        }
        
        res += (charValue * power);
        power *= 62;
    }

    return res;
}

int init_hashmap(int capacity, HashMap** mp_) {
    struct HashMap* mp = (struct HashMap*)malloc(sizeof(struct HashMap));
    if (mp == NULL) {
        return NO_MEMORY;
    }
    mp->capacity = capacity;
    mp->size = 0;

    for (int i = 0; i < HASHSIZE; i++) {
        mp->table[i] = NULL;
    }

    *mp_ = mp;

    return OK;
}

Macro* find_word(HashMap* mp, char* name) {
    int index = hash_function(mp, name);
    Macro* macro = mp->table[index];

    while (macro != NULL && strcmp(name, macro->name) != 0) {
        macro = macro->next;
    }

    return macro;
}

void replace_word(char* input, FILE* outputFile, HashMap* mp) {
    char *pos = input;
    char modified_line[MAX_LINE_LEN] = "";
    char word[MAX_WORD_LEN] = "";

    char tmp[8];
    strncpy(tmp, input, 7);
    tmp[7] = '\0';

    if (strcmp("#define", tmp) == 0) {
        fputs(input, outputFile);
    }
    else {
        while (*pos != '\0') {
            if (isalnum(*pos)) {
                int i = 0;
                while (isalnum(*pos)) {
                    word[i++] = *pos++;
                }
                word[i] = '\0';
                Macro* res = find_word(mp, word);
                if (res != NULL) {
                    fprintf(outputFile, "%s", res->value);
                }
                else {
                    fprintf(outputFile, "%s", word);
                }
            } else {
                fprintf(outputFile, "%c", *pos);
                pos++;
            }
        }
    }
}

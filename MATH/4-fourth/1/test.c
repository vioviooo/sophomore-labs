#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define HASHSIZE 128
#define MAX_LINE_LEN 200
#define MAX_WORD_LEN 200

typedef struct Macro {
    char *name;
    char *value;
    struct Macro *next;
} Macro;

typedef struct HashMap {
    int capacity;
    int size; // number of elements in a hash table
    struct Macro *table[HASHSIZE];
} HashMap;

int hash_function(struct HashMap* mp, char* key);
void insert_word(struct HashMap* mp, char* name, char* value);
void rehash(struct HashMap* mp);
void free_hashmap(struct HashMap* mp);

HashMap* init_hashmap(int capacity) {
    struct HashMap* mp = (struct HashMap*)malloc(sizeof(struct HashMap));
    mp->capacity = capacity;
    mp->size = 0;

    for (int i = 0; i < HASHSIZE; i++) {
        mp->table[i] = NULL;
    }

    return mp;
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
        // printf("yeye\n");
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



int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("invalid");
        return 1;
    }

    FILE* fptr = fopen(argv[1], "r+");
    if (fptr == NULL) {
        printf("file not open");
        return 1;
    }

    HashMap* mp = init_hashmap(HASHSIZE);

    char line[200];
    char word[100];
    char replace[100];
    int cnt_define = 0;
    while (fgets(line, sizeof(line), fptr) != NULL) {
        if (line[0] == '#' && sscanf(line, "#define %s %s", word, replace) == 2) {
            insert_word(mp, word, replace);
            cnt_define++;
        } else {
            break;
        }
    }

    fseek(fptr, 0, SEEK_SET);

    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(fptr);
        return 1;
    }

    while (fgets(line, sizeof(line), fptr) != NULL) {
        replace_word(line, outputFile, mp);
    }

    free_hashmap(mp);

    return 0;
}

void insert_word(struct HashMap* mp, char* name, char* value) {
    int index = hash_function(mp, name);

    Macro* newMacro = (Macro*)malloc(sizeof(struct Macro));
    newMacro->name = strdup(name);
    newMacro->value = strdup(value);
    newMacro->next = mp->table[index];
    mp->table[index] = newMacro;
    mp->size++;

    // Check if rehashing is needed
    if (mp->size > 2 * mp->capacity) {
        rehash(mp);
    }
}

void rehash(struct HashMap* mp) {
    int newCapacity = mp->capacity * 2; // Double the capacity

    Macro* tempTable[HASHSIZE];
    memcpy(tempTable, mp->table, sizeof(mp->table));

    mp->capacity = newCapacity;
    mp->size = 0;

    for (int i = 0; i < HASHSIZE; i++) {
        Macro* currentMacro = tempTable[i];
        while (currentMacro != NULL) {
            Macro* nextMacro = currentMacro->next;
            insert_word(mp, currentMacro->name, currentMacro->value);
            free(currentMacro->name);
            free(currentMacro->value);
            free(currentMacro);
            currentMacro = nextMacro;
        }
    }
}

void free_hashmap(struct HashMap* mp) {
    for (int i = 0; i < HASHSIZE; i++) {
        Macro* currentMacro = mp->table[i];
        while (currentMacro != NULL) {
            Macro* nextMacro = currentMacro->next;
            free(currentMacro->name);
            free(currentMacro->value);
            free(currentMacro);
            currentMacro = nextMacro;
        }
        mp->table[i] = NULL;
    }
    free(mp);
}

int hash_function(struct HashMap* mp, char* key) {
    
    int ind, sum = 0;
    for (int i = 0; i < (int)strlen(key); i++) {
        int charValue;

        if ('0' <= key[i] && key[i] <= '9') {
            charValue = key[i] - '0';
        } else if ('A' <= key[i] && key[i] <= 'Z') {
            charValue = key[i] - 'A' + 10;
        } else if ('a' <= key[i] && key[i] <= 'z') {
            charValue = key[i] - 'a' + 36;
        } else {
            fprintf(stderr, "Invalid character in <def_name>: %c\n", key[i]);
            exit(EXIT_FAILURE);
        }
        
        sum = ((sum * 62) + charValue) % mp->capacity;
    }

    ind = sum;
    printf("sum : %d", sum);

    return ind;
}
#ifndef LIBS_H
#define LIBS_H

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
    int size;
    struct Macro *table[HASHSIZE];
} HashMap;

int hash_function(struct HashMap* mp, char* key);
int insert_word(struct HashMap* mp, char* name, char* value);
int rehash(struct HashMap* mp);
void free_hashmap(struct HashMap* mp);

#endif
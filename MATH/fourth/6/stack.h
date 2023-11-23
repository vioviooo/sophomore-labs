#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack_object {
    char oper;
    struct stack_object *next;
} object;

object *push(object *last_node, char oper);
object *pop(object *del_node);
void destroy(object *node);

#endif
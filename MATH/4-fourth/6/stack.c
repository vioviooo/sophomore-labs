#include "stack.h"

object *push(object *last_node, char oper) {
    object *new_node = (object *)malloc(sizeof(object));
    if (new_node == NULL) return last_node;
    new_node->oper = oper;
    new_node->next = last_node;
    return new_node;
}

object *pop(object *del_node) {
    if (del_node == NULL) return NULL;
    object *last_node = del_node->next;
    free(del_node);
    return last_node;
}

void destroy(object *node) {
    while (node) {
        node = pop(node);
    }
}

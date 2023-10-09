enum... join_symb(char **src, char symb, int *capacity) {
    if (*capacity == strlen(src) + 1) {
        *capacity *= 2;

        char *temp = (char*)realloc(*src, sizeof(char) * capacity);

        if (temp == NULL) {
            return error;
        }

        *src = temp;
    }

    (*src)[strlen(*src) + 1] = 0;
    (*src)[strlen(*src)] = symb;
}

//realloc со сложностью армотизированной константы

int get_str(char **src, FILE*) {
    *src = NULL;
    int capacity = 2;

    *src = (char*)malloc(sizeof(char) * capacity);

    while ('\n') {
        join_symb(src, fgetc(stream), &capacity);
    }
}
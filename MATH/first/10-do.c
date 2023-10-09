#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

typedef long long ll;

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

bool is_digit(char ch) {
    return (ch >= '0' && ch <= '9') ? 1 : 0;
}

bool is_valid_num(char st[]) {
    for (int i = 0; st[i] != '\0'; i++) {
        if (!is_digit(st[i])) {
            return 0;
        }
    }

    if (strlen(st) > 19) {
        return 0;
    }

    return 1;
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Invalid amount of arguments.\n");
        return 1;
    }

    char arr[40];
    while (strcmp(arr, "stop") != 0) {
        scanf("%s", arr);
        // printf("%d ", 9);
    }

    

    return 0;
}
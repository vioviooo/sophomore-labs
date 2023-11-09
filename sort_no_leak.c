#include <stdio.h>
#include <stdlib.h>

enum status_codes { OK = -1, ERROR = -2 };

int input(int **a, int *n);
void output(int *a, int n);
void sort(int *a, int n);
// no line breaker in the end
int main() {
    int n;
    int* data;

    int status = input(&data, &n);
    if (status != OK) {
        printf("n/a");
        return 0;
    }

    sort(data, n);

    output(data, n);

    free(data);

    return 0;
}

int input(int **a, int *n) {
    if (scanf("%d", n) != 1 || getchar() != '\n') {
        return ERROR;
    }

    if (*n <= 0) {
        return ERROR;
    }

    *a = (int*)malloc(sizeof(int) * *n);
    if (*a == NULL) { // no memory
        return ERROR;
    }

    for (int *p = *a; p - *a < *n; p++) {
        scanf("%d", p);
    }

    if (getchar() != '\n') {
        return ERROR;
    }

    return OK;
}

void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        printf("%d ", *p);
    }
}

void sort(int *a, int n) {
    int elem;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                elem = a[j];
                a[j] = a[j + 1];
                a[j + 1] = elem;
            }
        }
    }
}
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

    if (st[0] == '-' && st[1] == '\0') {
        return 0;
    }
    
    for (int i = 0; st[i] != '\0'; i++) {
        if (!is_digit(st[i]) && st[i] != '-') {
            return 0;
        }
        if (st[i] == '-' && i != 0) {
            return 0;
        }
    }

    if (strlen(st) > 19) {
        return 0;
    }

    return 1;
}

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("Invalid amount of arguments.\n");
        return 1;
    }

    if (!is_valid_num(argv[1]) || !is_valid_num(argv[2])) {
        printf("Invalid numbers.\n");
        return 1;
    }

    ll a, b;
    a = MIN(atoll(argv[1]), atoll(argv[2]));
    b = MAX(atoll(argv[2]), atoll(argv[1]));

    // printf("%lld %lld \n", a, b);

    ll arr[10];

    srand(time(NULL)); // seeding the generator with current time

    for (int i = 0; i < 10; i++) {
        arr[i] = a + rand() % (b - a + 1);
    }

    printf("Initial array: \n");
    for (int i = 0; i < 10; i++) {
        printf("%lld ", arr[i]);
    }

    ll mi = 1e18, ind_mi = -1, ma = -1e18, ind_ma = -1;
    for (int i = 0; i < 10; i++) {
        if (arr[i] > ma) {
            ma = arr[i];
            ind_ma = i;
        }
        if (arr[i] < mi) {
            mi = arr[i];
            ind_mi = i;
        }
    }

    ll tmp = arr[ind_mi];
    arr[ind_mi] = ma;
    arr[ind_ma] = tmp;

    printf("\n\nFinal array: \n");
    for (int i = 0; i < 10; i++) {
        printf("%lld ", arr[i]);
    }

    int size_begin = 10, size_end = 1e4;
    int size_a = size_begin + rand() % (size_end - size_begin + 1), 
        size_b = size_begin + rand() % (size_end - size_begin + 1);

    // size_a = 10;
    // size_b = 10;

    int* arr_a = (int*)malloc(size_a * sizeof(int));
    int* arr_b = (int*)malloc(size_b * sizeof(int));

    int elem_begin = -1000, elem_end = 1000;

    for (int i = 0; i < size_a; i++) {
        arr_a[i] = elem_begin + rand() % (elem_end - elem_begin + 1);
    }

    for (int i = 0; i < size_b; i++) {
        arr_b[i] = elem_begin + rand() % (elem_end - elem_begin + 1);
    }

    int* arr_c = (int*)malloc(size_a * sizeof(int));

    printf("\n\nInitial array A: \n");
    for (int i = 0; i < size_a; i++) {
        printf("%d ", arr_a[i]);
    }

    printf("\n\nInitial array B: \n");
    for (int i = 0; i < size_b; i++) {
        printf("%d ", arr_b[i]);
    }

    for (int i = 0; i < size_a; i++) {
        int min = 1e5, closest = 0;
        for (int j = 0; j < size_b; j++) {
            if (abs(MAX(arr_a[i], arr_b[j]) - MIN(arr_a[i], arr_b[j])) < min) {
                min = abs(MAX(arr_a[i], arr_b[j]) - MIN(arr_a[i], arr_b[j]));
                closest = arr_b[j];
            }
        }
        arr_c[i] = arr_a[i] + closest;
    } 

    printf("\n\nFinal array C: \n");
    for (int i = 0; i < size_a; i++) {
        printf("%d ", arr_c[i]);
    }
    printf("\n");

    free(arr_a);
    free(arr_b);
    free(arr_c);

    return 0;
}
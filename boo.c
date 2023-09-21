#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    int arr[3] = {1, 2, 3};

    int n = 3, end = 3 - 1, tmp;
    for (int i = 0; i <= n / 2 && end >= i; i++, end--) {
        tmp = arr[i];
        arr[i] = arr[end];
        arr[end] = tmp;
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}

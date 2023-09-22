#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef long long ll;
typedef long double ld;

ld eLimit() {
    ld res = 0;
    return res;
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Invalid amount of arguments. Usage: %s <integer> \n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    printf("Choose number: \n 1. Euler's number \n 2. Pi \n 3. Natural logarithm of 2 \n 4. Squareroot of 2 \n 5. Y \n");

    int choice;
    scanf("%d", &choice);

    printf("%d", choice);

    printf("\n");

    return 0;
}
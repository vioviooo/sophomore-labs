#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

typedef long long ll;

int dec_to_eighth(int n) {
    int arr[10];
    int i = 0;

    while (n != 0) {
        arr[i] = n % 8;
        n /= 8;
        i++;
    }

    printf("%d %d\n", arr[0], arr[1]);

    int num = 0, d = 1;
    for (int j = 0; j < i; j++) {
        num = arr[j] * d + num;
        d *= 10;
    }

    return num;
}

int main(int argc, char* argv[]) 
{

    int num = 143;

    printf("%d \n", dec_to_eighth(num));

    return 0;
}
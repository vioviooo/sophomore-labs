#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

typedef long long ll;

long long MAX_LL = LLONG_MAX;

ll charToNum(char* ch) {
    ll num = atoll(ch);
    return num;
}

int main(int argc, char *argv[]) {

    // for (int i = 0; argv[1][i] != '\0'; i++) {
    //     if (i > 19) {
    //         printf("Error! Integer overflow!");
    //         return 1;
    //     }
    // }

    // ll num = -109223372036854775808;

    // printf("%lld", num);
    
    // // double eps = 1.0, res = 1;

    // // for (int i = 0; i < 100; i++) {

    // //     printf("%f", exp())
    // // }

    printf("%lld", charToNum(argv[1]));

    return 0;
}

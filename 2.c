#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

typedef long long ll;
typedef long double ld;

ld eLimit(ld eps) {
    int k = 1e4;
    ld final;
    bool flag = true;
    for (int n = 1; n < k && flag; n++) {
        ld res = 1.0, prev = res, diff = eps + 1;
        for (int i = 1; i <= n && flag; i++) {
            res *= (1.0 + 1.0 / n);

            if (eps > 1.0 / n) {
                flag = false;
            }

            final = fmax(final, res);

            // printf("%Lf %Lf %d \n", res, diff, n);
        }
        // printf("%Lf %Lf %d \n", res, diff, n);
    }
    // printf("Final: %Lf \n", final);
    return final;

    // ld res = 1.0, final = 1.0;
    // int n = 1;
    
    // while (1) {
    //     res *= (1.0 + 1.0 / n);
    //     final = fmax(final, res);
        
    //     if (1.0 / n <= eps) {
    //         break;
    //     }
    //     n++;
    // }
    
    // return final;
}

ld eQuation(ld eps) {
    ld x = 1.0, n = 0;
    while (fabsl(log(x) - 1.0) > eps) {
        x = x - (log(x) - 1.0) / (1.0 / x);
    }
    return x;
}

ld eSeries(ld eps) {
    int k = 1000;
    ld res = 2.0, diff = eps + 1.0;
    ll fact = 1;
    for (int x = 2; x < k && eps < diff; x++) {
        fact *= x; // CHECK OVERFLOW
        res += (1.0 / fact);
        diff = 1.0 / fact;
        // printf("%Lf \n", res);
    }
    return res;
    // ld res = 2.0;
    // ll fact = 2; // Start with 2! = 2

    // while (eps < 1.0 / fact) {
    //     res += 1.0 / fact;
    //     fact *= (fact + 1);
    // }

    // return res;
}

int main() {

    ld eps;
    scanf("%Lf", &eps);

    int l; // how many decimal places 
    scanf("%d", &l);
    
    // ld res = eQuation(eps);

    // printf("%.*Lf", l, res);

    // int n = atoi(argv[1]);

    printf("Choose a number: \n 1. Euler's number \n 2. Pi \n 3. Natural logarithm of 2 \n 4. Square root of 2 \n 5. Y \n");

    int number;
    scanf("%d", &number);

    // printf("%d", number);

    switch(number) {
        case 1:
            printf("%.*Lf \n%.*Lf \n%.*Lf \n", l, eLimit(eps), l, eQuation(eps), l, eSeries(eps));
            break;
        case 2:
            break;
        case 3: 
            break;
        case 4:
            break;
        case 5: 
            break;
    }

    printf("\n");

    return 0;
}
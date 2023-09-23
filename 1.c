#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef long long ll;

long long MAX_LL = LLONG_MAX;

// enum statusCodes {
//     sc_ok, 
//     sc_overflow,
//     sc_inv_arg
// };

ll charToInteger(char* ch) {
    ll num = atoll(ch);
    return num;
}

ll factorial(ll n) {
    ll res = 1;
    for (ll i = 2; i <= n; i++) {
        res *= i;
        if (res > MAX_LL) {
            return -1;
        }
    }
    return res;
}

ll sumOfNums(ll n) {
    ll sum = n * (n + 1) / 2;
    if (sum > MAX_LL) {
        return -1;
    }
    return sum;
}

ll lengthOfNum(ll n) {
    ll len = 0, tmp = llabs(n); // len = legth of the number
    do {
        tmp /= 10;
        len++;
    } while (tmp != 0);

    return len;
}

bool isPrime(ll n) {
    for (ll i = 2; i * i < n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("Invalid amount of arguments. Usage: %s <integer> <\"flag\"> \n", argv[0]);
        return 1;
    }

    for (int i = 0; argv[1][i] != '\0'; i++) {
        if (argv[1][i] < '0' || argv[1][i] > '9') {
            printf("The first argument is not an integer. Try again.");
            return 1;
        }
    }

    ll numOfCommands = 6;
    char *commands[6] = {"h", "p", "s", "e", "a", "f"};

    // printf("%c \n", argv[2][0]);

    ll ind = -1;
    for (ll i = 0; i < numOfCommands; i++) {
        if ((argv[2][0] == '-' || argv[2][0] == '/') && strcmp(&argv[2][1], commands[i]) == 0) {
            ind = i; // keep the index of the command we need to execute
        }
    }

    // printf("%c \n", argv[2][1]);

    if (ind == -1) {
        printf("Invalid command. Try again. \n");
        return 1;
    }

    for (int i = 0; argv[1][i] != '\0'; i++) {
        if (i > 19 && ind != 2) { // не более 19 знаков у самого большого числа
            printf("Integer overflow! \n");
            return 1;
        } 
    }

    switch (ind) {
        case 0: {
            ll num = charToInteger(argv[1]);

            if (num == 0) {
                printf("Can't divide by 0! \n");
                return 1;
            }

            if (num > 100) {
                printf("No such numbers found. \n");
                return 0;
            }

            for (int i = num; i <= 100; i += num) {
                printf("%d ", i);
            }

            break;
        }
        case 1: {
            ll num = charToInteger(argv[1]);

            if (num == 1 || num == 0 || num < 0) {
                printf("Neither prime, nor composite. \n");
                return 0;
            }

            bool check = isPrime(num);

            if (check) {
                printf("Prime.");
            }
            else {
                printf("Composite.");
            }

            break;
        }

        case 2: { // works with numbers >> max_ll
            bool leadingZero = true;
            for (int i = 0; argv[1][i] != '\0'; i++) {
                if (argv[1][i] == '0' && leadingZero == true) {
                    continue;
                }
                else {
                    leadingZero = false;
                }
                if (!leadingZero) {
                    printf("%c ", argv[1][i]);
                }
            }

            break;
        }

        case 3: { 

            int num = atoi(argv[1]);

            printf("+----+");

            for (int i = 1; i <= 140; i++) {
                if (i % 14 == 0) {
                    printf("+");
                }
                else {
                    printf("-");
                }
            }
            printf("\n");

            for (int i = 1; i <= 10; i++) {
                ll res = i; // Initialize 'res' to 1 for the base
                printf("|%3d |", i);
                printf(" %11lld |", res);
                for (int j = 1; j < num && i > 0; j++) {
                    if (i != 1) {
                        res *= i; 
                    }
                    printf(" %11lld |", res);
                }

                printf("\n");

                printf("+----+");

                for (int j = 1; j <= 140; j++) {
                    if (j % 14 == 0) {
                        printf("+");
                    }
                    else {
                        printf("-");
                    }
                }
                printf("\n");
            }
            break;
        }

        case 4: {
            ll num = charToInteger(argv[1]);

            if (num < 1) {
                printf("The sum is undefined: entered number is less than 1. \n");
                return 0;
            }

            ll sum = sumOfNums(num);

            if (sum < 0) {
                printf("Integer overflow! \n");
                return 1;
            }

            printf("%lld", sum);

            break;
        }
        case 5: {
            ll num = charToInteger(argv[1]);

            if (num < 0) {
                printf("The factorial of this integer is undefined. The number is less than 0. \n");
                return 0;
            }

            ll fact = factorial(num);

            if (fact < 0) {
                printf("Integer overflow! \n");
                return 1;
            }

            printf("The factorial of %lld is %lld", num, fact);

            break;
        }
    }

    printf("\n");

    return 0;
}
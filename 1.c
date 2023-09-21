#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef long long ll;

ll factorial(ll n) {
    ll res = 1;
    for (ll i = 2; i <= n; i++) {
        res *= i;
    }
    return res;
}

ll sumOfNums(ll n) {
    ll sum = 0;
    for (ll i = 1; i <= n; i++) {
        sum += i;
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

    for (int i = 0; i < argv[1][i] != '\0'; i++) {
        if (argv[1][i] < '0' || argv[1][i] > '9') {
            printf("The first argument is not an integer. Try again.");
            return 1;
        }
    }

    // !! check for integer overflow

    ll numOfCommands = 6;
    char *commands[6] = {"h", "p", "s", "e", "a", "f"};

    ll num = atoll(argv[1]);

    ll ind = -1;
    for (ll i = 0; i < numOfCommands; i++) {
        if (strcmp(&argv[2][1], commands[i]) == 0) {
            ind = i; // keep the index of the command we need to execute
        }
    }

    if (ind == -1) {
        printf("Invalid command. Try again. \n");
        return 1;
    }

    switch (ind) {
        case 0: {
            if (ind == 0) {
                printf("Can't divide by 0! \n");
                return 1;
            }

            if (num > 100) {
                printf("No such numbers found. \n");
                return 0;
            }

            for (ll i = 1; i <= 100; i++) {
                if (i % num == 0) {
                    printf("%lld", i);
                }
            }

            break;
        }
        case 1: {
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

        case 2: {
            
            ll len = lengthOfNum(num);
            
            char *arr = (char*)malloc(len + 1); // allocating memory for an array that will store number's digits
            if (arr == (void*)0) {
                printf("Memory allocation failed! \n");
                return 1;
            }

            ll i = 0, tmp = num;

            do { // getting digits and putting them into our array
                arr[i] = tmp % 10;
                tmp /= 10;
                i++;
            } while (tmp != 0);

            ll end = len - 1; // index of the last digit in the array
            for (i = 0; i <= len / 2 && end >= i; i++, end--) {
                tmp = arr[i];
                arr[i] = arr[end];
                arr[end] = tmp;
            }

            for (i = 0; i < len; i++) {
                printf("%d ", arr[i]);
            }
            
            free(arr); // freeing up the memory that we used

            break;
        }

        case 3: {
            if (num > 10 || num < 0) {
                printf("Entered number is out of range! \n");
                return 1;
            }
            for (ll i = 1; i <= 10; i++) {
                ll res = i; // result for each base for each power
                printf("%lld ", res);
                for (ll j = 2; j <= num; j++) {
                    res *= res;
                    printf("%lld ", res);
                }
            }
            break;
        }
        case 4:
            if (num < 1) {
                printf("The sum is undefined: entered number is less than 1. \n");
                return 0;
            }

            ll sum = sumOfNums(num);

            printf("%lld \n", sum);

            break;
        case 5:
            if (num < 0) {
                printf("The factorial of this integer is undefined. The number is less than 0. \n");
                return 0;
            }

            ll fact = factorial(num);

            printf("%s %lld %s %lld \n", "The factorial of", num, "is", fact);

            break;
    }

    printf("\n");

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main(long long argc, char* argv[]) {

    if (argc != 3) {
        printf("Invalid amount of arguments. Usage: %s <integer> <\"flag\"> \n", argv[0]);
        return 1;
    }

    // !! check for long long overflow

    long long numOfCommands = 6;
    char *commands[6] = {"h", "p", "s", "e", "a", "f"};

    // 2 "-p" 2

    long long num = atoi(argv[1]);

    // check num
    // printf("%d \n", num);

    long long ind = -1;
    for (long long i = 0; i < numOfCommands; i++) {
        if (strcmp(&argv[2][1], commands[i]) == 0) {
            ind = i;
        }
    }

    if (ind == -1) {
        printf("Invalid command. \n");
        return 1;
    }

    // char flag[3];
    // strncpy(flag, argv[2], sizeof(flag));

    // printf("%s \n", flag);

    switch (ind) {
        case 0: 
            if (ind == 0) {
                printf("Can't divide by 0! \n");
                return 1;
            }

            if (num > 100) {
                printf("No such numbers found. \n");
                return 0;
            }

            for (long long i = 1; i <= 100; i++) {
                if (i % num == 0) {
                    printf("%d", i);
                }
            }

            break;
        case 1: {

            if (num == 1 || num == 0 || num < 0) {
                printf("Neither prime nor composite. \n");
                return 0;
            }

            bool check = true;
            for (long long i = 2; i * i < num && check; i++) {
                if (num % i == 0) {
                    check = false;
                }
            }

            if (check) {
                printf("Composite.");
            }
            else {
                printf("Prime.");
            }

            break;
        }
        case 2: {
            if (num < 0) {
                printf("wtfffff \n");
                return 0;
            }
            
            long long len = 0, tmp = num; // len = legth of the number
            do {
                tmp /= 10;
                len++;
            } while (tmp != 0);
            
            char *arr = (char*)malloc(len + 1); // allocating memory for an array that will store number's digits
            if (arr == (void*)0) {
                printf("Memory allocation failed! \n");
                return 1;
            }
            long long i = 0;
            tmp = num;

            do { // getting digits and putting them into our array
                arr[i] = tmp % 10;
                tmp /= 10;
                i++;
            } while (tmp != 0);

            long long end = len - 1; // index of the last digit in the array
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
        case 3:
            if (num > 10 || num < 0) {
                printf("Entered number is out of range! \n");
                return 1;
            }
            for (long long i = 1; i <= 10; i++) {
                long long res = i; // result for each base for each power
                printf("%lld ", res);
                for (long long j = 2; j <= num; j++) {
                    res *= res;
                    printf("%lld ", res);
                }
            }
            break;
        case 4:
            if (num < 1) {
                printf("The sum is undefined: entered number is less than 1. \n");
                return 0;
            }
            long long sum = 0;
            for (long long i = 1; i <= num; i++) {
                sum += i;
            }
            printf("%lld \n", sum);

            break;
        case 5:
            if (num < 0) {
                printf("The factorial of this integer is undefined. The number is less than 0. \n");
                return 0;
            }
            long long factorial = 1;
            for (long long i = 2; i <= num; i++) {
                factorial *= i;
            }
            printf("%s %d %s %lld \n", "The factorial of", num, "is", factorial);
            break;
    }

    printf("\n");

    return 0;
}

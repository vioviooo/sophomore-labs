#include <stdio.h>

int main() {

    // printf("Character \n ASCII Value");

    // for (int i = 0; i < 128; i++) {
    //     printf("%c %d \n", i, i);
    // }

    // char a = '-', A = 'A';
    // // int anum = (int)a, Anum = (int)A;
    // // char ch_lower = (char)((int)A + 32);

    char ch[] = "sdjfkdsjfjksdhfjksdfhjksdhkjf";

    for (int i = 0; ch[i] != '\0'; i++) {
        ch[i] = (char)((int)ch[i] - 32);
        printf("%c", ch[i]);
    }

    // printf("%d \n", (int)a);

   return 0;
}
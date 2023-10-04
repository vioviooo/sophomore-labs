#include <stdio.h>

int main() {

    printf("Character \n ASCII Value");

    for (int i = 0; i < 128; i++) {
        printf("%c %d \n", i, i);
    }

   return 0;
}
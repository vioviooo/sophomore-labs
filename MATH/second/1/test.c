#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_random_array(int n, int array[]) {
    if (n < 1) {
        return;
    }

    // Initialize the array with numbers from 1 to n
    for (int i = 0; i < n; i++) {
        array[i] = i + 1;
    }

    // Seed the random number generator
    srand(time(NULL));

    // Fisher-Yates shuffle
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        printf("HERE: %d ", j);
        // Swap array[i] and array[j]
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

int main() {
    int n = 10;  // Change this to your desired value
    int random_array[n];
    generate_random_array(n, random_array);

    printf("Random Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", random_array[i]);
    }
    printf("\n");

    return 0;
}

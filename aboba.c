#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    // Cast the elements to integers and compare them
    return (*(int*)a - *(int*)b);
}

int main() {
    int rows, cols;

    printf("Enter the number of rows: ");
    scanf("%d", &rows);
    printf("Enter the number of columns: ");
    scanf("%d", &cols);

    // Create a 2D matrix
    int matrix[rows][cols];

    // Input the elements of the matrix
    printf("Enter the elements of the matrix row by row:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Sort each row of the matrix
    for (int i = 0; i < rows; i++) {
        qsort(matrix[i], cols, sizeof(int), compare);
    }

    // Print the sorted matrix
    printf("Sorted matrix row by row:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}

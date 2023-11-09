#include <stdio.h>
#include <stdlib.h>

enum allocation_type {
    DYNAMIC_ROW = 1,
    DYNAMIC_COL = 2,
    DYNAMIC_FLAT = 3,
};

int** alloc_dynamic_row(int rows, int cols);
int** alloc_dynamic_column(int rows, int cols);
int** alloc_dynamic_flat(int rows, int cols);
void free_matrix(int** matrix, int rows);
void input_matrix(int** matrix, int rows, int cols);
void output_matrix(int** matrix, int rows, int cols);
int row_sum(int* row, int cols);
void sortMatrix(int** matrix, int rows, int cols);
void swap(int *a, int *b);

int main() {
    int rows, cols;
    int allocation_type;

    if (scanf("%d", &allocation_type) != 1 || getchar() != '\n') {
        printf("n/a");
        return 1;
    }

    if (scanf("%d %d", &rows, &cols) != 2 || getchar() != '\n') {
        printf("n/a");
        return 1;
    }

    if (rows <= 0 || cols <= 0) {
        printf("n/a");
        return 1;
    }

    int** matrix;

    switch (allocation_type) {
        case DYNAMIC_ROW:
            matrix = alloc_dynamic_row(rows, cols);
            break;
        case DYNAMIC_COL:
            matrix = alloc_dynamic_column(rows, cols);
            break;
        case DYNAMIC_FLAT:
            matrix = alloc_dynamic_flat(rows, cols);
            break;
        default:
            printf("n/a");
            return 1;
    }

    if (matrix == NULL) {
        printf("n/a");
        return 1;
    }

    input_matrix(matrix, rows, cols);
    // output_matrix(matrix, rows, cols);

    sortMatrix(matrix, rows, cols);
    
    output_matrix(matrix, rows, cols);

    free_matrix(matrix, rows);

    return 0;
}

int** alloc_dynamic_row(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            free_matrix(matrix, i);
            return NULL;
        }
    }

    return matrix;
}

int** alloc_dynamic_column(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        return NULL;
    }

    matrix[0] = (int*)malloc(rows * cols * sizeof(int));
    if (matrix[0] == NULL) {
        free(matrix);
        return NULL;
    }

    for (int i = 1; i < rows; i++) {
        matrix[i] = matrix[i - 1] + cols;
    }

    return matrix;
}

int** alloc_dynamic_flat(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        return NULL;
    }

    matrix[0] = (int*)malloc(rows * cols * sizeof(int));
    if (matrix[0] == NULL) {
        free(matrix);
        return NULL;
    }

    for (int i = 1; i < rows; i++) {
        matrix[i] = matrix[0] + i * cols;
    }

    return matrix;
}

void free_matrix(int** matrix, int rows) {
    if (matrix == NULL) {
        return;
    }

    free(matrix[0]);
    free(matrix);
}

void input_matrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                free_matrix(matrix, rows);
                exit(1);
            }
        }
    }
}

// no unneeded spaces or line breaks
void output_matrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", matrix[i][j]);

            if (j < cols - 1) {
                printf(" ");
            }
        }

        if (i < rows - 1) {
            printf("\n");
        }
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sortMatrix(int** matrix, int rows, int cols) {
    int* sums = (int*)malloc(rows * sizeof(int));

    if (sums == NULL) {
        printf("n/a");
        free_matrix(matrix, rows);
        exit(1);
    }

    for (int i = 0; i < rows; i++) {
        sums[i] = row_sum(matrix[i], cols);
    }

    int m = rows, n = cols;
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - i - 1; j++) {
            if (sums[j] > sums[j + 1]) {
                for (int k = 0; k < n; k++) {
                    swap(&matrix[j][k], &matrix[j + 1][k]);
                }
                swap(&sums[j], &sums[j + 1]);
            }
        }
    }

    free(sums);
}

int row_sum(int* row, int cols) {
    int sum = 0;
    for (int i = 0; i < cols; i++) {
        sum += row[i];
    }
    return sum;
}
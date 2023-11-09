#include <stdio.h>
#include <stdlib.h>

enum allocation_type {
    STATIC = 1,
    DYNAMIC_ROW = 2,
    DYNAMIC_COL = 3,
    DYNAMIC_FLAT = 4,
};

int** alloc_static(int rows, int cols);
int** alloc_dynamic_row(int rows, int cols);
int** alloc_dynamic_column(int rows, int cols);
int** alloc_dynamic_flat(int rows, int cols);
void free_matrix(int** matrix, int rows);
void input_matrix(int** matrix, int rows, int cols);
void output_matrix(int** matrix, int rows, int cols);

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
        case STATIC:
            matrix = alloc_static(rows, cols);
            break;
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
    output_matrix(matrix, rows, cols);

    free_matrix(matrix, rows);

    return 0;
}

int** alloc_static(int rows, int cols) {
    if (rows > 100 || cols > 100) {
        return NULL;
    }

    static int matrix[100][100];
    return (int**)matrix;
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

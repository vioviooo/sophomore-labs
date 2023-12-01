#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.c"

int main(int argc, char *argv[]) {
    
    // change accordingly
    int size = 3, vec_cnt = 3;

    double **matrix = (double **)malloc(size * sizeof(double *));
    if (matrix == NULL) {
        print_scs(NO_MEMORY);
        return NO_MEMORY;
    }

    for (int i = 0; i < size; i++) {
        matrix[i] = (double *)malloc(size * sizeof(double));
        if (matrix[i] == NULL) {
            print_scs(NO_MEMORY);
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NO_MEMORY;
        }
    }

    matrix[1][0] = matrix[2][0] = matrix[0][1] = matrix[2][1] = matrix[0][2] = matrix[1][2] = 0;
    matrix[0][0] = 0;
    matrix[1][1] = 0;
    matrix[2][2] = 0;

    Vector vec1;
    vec1.coordinate = (double[]){1.0, 2.0, 3.0};

    vec1.size = size;

    Vector vec2;
    vec2.coordinate = (double[]){1.0, 6.0, 8.0};

    vec2.size = size;

    Vector vec3;
    vec3.coordinate = (double[]){5.0, -8.0, 9.0};

    vec3.size = size;

    Vector *max_norm = (Vector *)malloc(10 * sizeof(Vector));
    Vector *max_pow_norm = (Vector *)malloc(10 * sizeof(Vector));
    Vector *max_A_norm = (Vector *)malloc(10 * sizeof(Vector));

    int cnt = 0, cnt_p = 0, cnt_m = 0, p = 2;

    int status = find_norm(vec_cnt, &max_norm, &cnt, &cnt_p, &cnt_m, &max_pow_norm, &max_A_norm, p, size,
                           matrix, get_norm, pow_norm, matrix_norm, vec1, vec2, vec3);

    if (status != OK) {
        print_scs(status);
        clean_me(matrix, max_pow_norm, max_norm, max_A_norm, size);
        return status;
    }

    printf("Max vec:\n");
    for (int i = 0; i < cnt; i++) {
        print_vector(&max_norm[i], i);
    }

    printf("Max p-norm:\n");
    for (int i = 0; i < cnt_p; i++) {
        print_vector(&max_pow_norm[i], i);
    }

    printf("Max matrix norm:\n");
    for (int i = 0; i < cnt_m; i++) {
        print_vector(&max_A_norm[i], i);
    }

    clean_me(matrix, max_pow_norm, max_norm, max_A_norm, size);

    return 0;
}
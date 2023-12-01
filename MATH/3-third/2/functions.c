#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "header.h"

void print_scs(int choice) {
    switch (choice) {
        case INVALID_INPUT:
            printf("\nInvalid input.\n");
            break;
        case OK:
            printf("\nProject finished successfully!\n");
            break;
        case NO_MEMORY:
            printf("\nError! No memory.\n");
            break;
        case OVERFLOW_:
            printf("\nError! Overflow.\n");
            break;
        case UNDEFINED:
            printf(
                "\nError! What you're trying to calculate IS UNDEFINED or uses "
                "complex numbers.\n");
            break;
        case FILE_NOT_OPEN:
            printf("\nCan't open file.\n");
            break;
        case INVALID_INPUT_FILE:
            printf("\nInvalid format of data in file.\n");
            break;
        default:
            break;
    }
}

int find_norm(int count, Vector **max_norm, int *cnt, int *cnt_p, int *cnt_m, Vector **max_pow_norm,
              Vector **max_matrix_norm, int p, int size, double **matrix, double (*get_norm)(Vector),
              double (*pow_norm)(Vector, double), double (*matrix_norm)(Vector, double **), ...) {
    double cur_norm, my_pow_norm, cur_matrix_norm;
    double cur_max_norm = -100.0, cur_max_pow_norm = -100.0, cur_max_matrix_norm = -100.0;
    int i_ = 10, j_ = 10, k_ = 10;

    va_list args;
    va_start(args, matrix_norm);

    Vector *tmp = NULL;

    for (int i = 0; i < count; i++) {
        Vector vector = va_arg(args, Vector);
        cur_norm = get_norm(vector);
        if (cur_norm > cur_max_norm) {
            *cnt = 0;
            free(*max_norm);
            *max_norm = (Vector *)malloc(10 * sizeof(Vector));
            cur_max_norm = cur_norm;
            (*max_norm)[*cnt] = vector;
            (*cnt)++;
        } else {
            if (*cnt == i) {
                tmp = (Vector *)realloc(*max_norm, 2 * (*cnt) * sizeof(Vector));
                if (tmp == NULL) {
                    return NO_MEMORY;
                }
                *max_norm = tmp;
                i *= 2;
            }
            (*max_norm)[*cnt] = vector;
            (*cnt)++;
        }

        my_pow_norm = pow_norm(vector, p);

        if (my_pow_norm > cur_max_pow_norm) {
            *cnt_p = 0;
            free(*max_pow_norm);
            *max_pow_norm = (Vector *)malloc(10 * sizeof(Vector));
            cur_max_pow_norm = my_pow_norm;
            (*max_pow_norm)[*cnt_p] = vector;
            (*cnt_p)++;
        } else {
            if (*cnt_p == i) {
                tmp = (Vector *)realloc(*max_pow_norm, 2 * (*cnt_p) * sizeof(Vector));
                if (tmp == NULL) {
                    return NO_MEMORY;
                }
                *max_pow_norm = tmp;
                i *= 2;
            }
            (*max_pow_norm)[*cnt_p] = vector;
            (*cnt_p)++;
        }

        cur_matrix_norm = matrix_norm(vector, matrix);

        if (cur_matrix_norm >= cur_max_matrix_norm) {
            if (cur_matrix_norm > cur_max_matrix_norm) {
                *cnt_m = 0;
                free(*max_matrix_norm);
                *max_matrix_norm = (Vector *)malloc(10 * sizeof(Vector));
                cur_max_matrix_norm = cur_matrix_norm;
                (*max_matrix_norm)[*cnt_m] = vector;
                (*cnt_m)++;
            } else {
                if (*cnt_m == i) {
                    tmp = (Vector *)realloc(*max_matrix_norm, 2 * (*cnt_m) * sizeof(Vector));
                    if (tmp == NULL) {
                        return NO_MEMORY;
                    }
                    *max_matrix_norm = tmp;
                    i *= 2;
                }
                (*max_matrix_norm)[*cnt_m] = vector;
                (*cnt_m)++;
            }
        }
    }
    va_end(args);
    return OK;
}

double get_norm(Vector vec) {
    double norm = 0.0;
    for (int i = 0; i < vec.size; i++) {
        norm += vec.coordinate[i] * vec.coordinate[i];
    }
    return sqrt(norm);
}

double pow_norm(Vector vec, double p) {
    double norm = 0.0;
    for (int i = 0; i < vec.size; i++) {
        norm += pow(fabs(vec.coordinate[i]), p);
    }
    return pow(norm, (1.0 / p));
}

double matrix_norm(Vector vec, double **matrix) {
    double norm = 0.0;
    for (int i = 0; i < vec.size; i++) {
        for (int j = 0; j < vec.size; j++) {
            norm += (matrix[i][j] * vec.coordinate[i] * vec.coordinate[j]);
        }
    }
    return sqrt(norm);
}

void clean_me(double **matrix, Vector *max_pow_norm, Vector *max_norm, Vector *max_A_norm, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(max_norm);
    free(max_pow_norm);
    free(max_A_norm);
}

void print_vector(Vector *vec, int index) {
    printf("Vector #%d: (", index + 1);
    for (int i = 0; i < vec->size; i++) {
        printf("%lf", vec->coordinate[i]);
        if (i < vec->size - 1) {
            printf(" ");
        }
    }
    printf(") \n");
}
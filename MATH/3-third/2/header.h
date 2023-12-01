#ifndef HEADER_H
#define HEADER_H

enum status_codes {
    OK = 1,
    ERROR = -2,
    INVALID_INPUT = 2,
    INVALID_INPUT_FILE = -6,
    NO_MEMORY = -1,
    OVERFLOW_ = -3,
    UNDEFINED = -4,
    FILE_NOT_OPEN = -5
};

typedef struct {
    int size;
    double *coordinate;
} Vector;

void print_scs(int choice);

int find_norm(int cnt_main, Vector **max_norm, int *cnt, int *cnt_p, int *cnt_m, Vector **max_pow_norm,
              Vector **max_matrix_norm, int p, int size, double **matrix, double (*get_norm)(Vector),
              double (*pow_norm)(Vector, double), double (*matrix_norm)(Vector, double **), ...);

double get_norm(Vector vec);
double pow_norm(Vector vec, double p);
double matrix_norm(Vector vec, double **matrix);

void clean_me(double **matrix, Vector *max_pow_norm, Vector *max_norm, Vector *max_A_norm, int size);

void print_vector(Vector *vec, int index);

#endif
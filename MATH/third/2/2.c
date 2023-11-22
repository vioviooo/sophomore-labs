#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void print_scs(int choice) {
  switch (choice) {
  case INVALID_INPUT:
    printf("\nInvalid input.\n");
    break;
  case OK:
    printf("\nProject finished OKAYfully!\n");
    break;
  case NO_MEMORY:
    printf("\nNo memory left.\n");
    break;
  case OVERFLOW_:
    printf("\nOverflow!\n");
    break;
  case UNDEFINED:
    printf("\nError! What you're trying to calculate IS UNDEFINED or uses "
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

typedef struct {
  int size;
  double *coordinate;
} Vector;

int find_norm(int count, Vector **max_norm, int *cnt, int *cnt_p,
              int *cnt_m, Vector **max_p_norm, Vector **max_matrix_norm,
              int p, int size, double **matrix, double (*get_norm)(Vector),
              double (*p_norm)(Vector, double),
              double (*get_matrix_norm)(Vector, double **), ...) {

  double cur_norm, my_p_norm, cur_matrix_norm;
  double cur_max_norm = -1.0, cur_max_p_norm = -1.0, cur_max_matrix_norm = -1.0;
  int i_ = 10, j_ = 10, k_ = 10;

  va_list args;
  va_start(args, get_matrix_norm);

  Vector *temp = NULL;

  for (int i = 0; i < count; i++) {
    Vector vector = va_arg(args, Vector);
    cur_norm = get_norm(vector);
    if (cur_norm >= cur_max_norm) {
      if (cur_norm > cur_max_norm) {
        *cnt = 0;
        free(*max_norm);
        *max_norm = (Vector *)malloc(10 * sizeof(Vector));
        cur_max_norm = cur_norm;
        (*max_norm)[*cnt] = vector;
        (*cnt)++;
      } else {
        if (*cnt == i) {
          temp = (Vector *)realloc(*max_norm, 2 * (*cnt) * sizeof(Vector));
          if (temp == NULL) {
            return NO_MEMORY;
          }
          *max_norm = temp;
          i *= 2;
        }
        (*max_norm)[*cnt] = vector;
        (*cnt)++;
      }
    }
    my_p_norm = p_norm(vector, p);
    if (my_p_norm >= cur_max_p_norm) {
      if (my_p_norm > cur_max_p_norm) {
        *cnt_p = 0;
        free(*max_p_norm);
        *max_p_norm = (Vector *)malloc(10 * sizeof(Vector));
        cur_max_p_norm = my_p_norm;
        (*max_p_norm)[*cnt_p] = vector;
        (*cnt_p)++;
      } else {
        if (*cnt_p == i) {
          temp =
              (Vector *)realloc(*max_p_norm, 2 * (*cnt_p) * sizeof(Vector));
          if (temp == NULL) {
            return NO_MEMORY;
          }
          *max_p_norm = temp;
          i *= 2;
        }
        (*max_p_norm)[*cnt_p] = vector;
        (*cnt_p)++;
      }
    }
    cur_matrix_norm = get_matrix_norm(vector, matrix);

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
          temp = (Vector *)realloc(*max_matrix_norm,
                                   2 * (*cnt_m) * sizeof(Vector));
          if (temp == NULL) {
            return NO_MEMORY;
          }
          *max_matrix_norm = temp;
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

double get_norm(Vector v) {
  double norm = 0.0;
  for (int i = 0; i < v.size; i++) {
    norm += v.coordinate[i] * v.coordinate[i];
  }
  return sqrt(norm);
}

double p_norm(Vector v, double p) {
  double norm = 0.0;
  for (int i = 0; i < v.size; i++) {
    norm += pow(fabs(v.coordinate[i]), p);
  }
  return pow(norm, 1.0 / p);
}

double get_matrix_norm(Vector vec, double **matrix) {
  double norm = 0.0;
  for (int i = 0; i < vec.size; i++) {
    for (int j = 0; j < vec.size; j++) {
      norm += (matrix[i][j] * vec.coordinate[i] * vec.coordinate[j]);
    }
  }
  return sqrt(norm);
}

void clean_me(double **matrix, Vector *max_p_norm, Vector *max_norm,
              Vector *max_A_norm, int size) {
  for (int i = 0; i < size; i++) {
    free(matrix[i]);
  }
  free(matrix);
  free(max_norm);
  free(max_p_norm);
  free(max_A_norm);
}

int main(int argc, char *argv[]) {

  // change accordingly
  int size = 3, vec_cnt = 3;

  double **matrix = (double **)malloc(size * sizeof(double*));
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
  vec1.coordinate = (double[]){1.0, 2.0, 3.0}; // sqrt(14)

  vec1.size = size;

  Vector vec2;
  vec2.coordinate = (double[]){1.0, 6.0, 8.0};
  
  vec2.size = size;

  Vector vec3;
  vec3.coordinate = (double[]){5.0, 8.0, 9.0};

  vec3.size = size;

  Vector *max_norm = (Vector *)malloc(10 * sizeof(Vector));
  Vector *max_p_norm = (Vector *)malloc(10 * sizeof(Vector));
  Vector *max_A_norm = (Vector *)malloc(10 * sizeof(Vector));

  int cnt = 0, cnt_p = 0, cnt_m = 0, p = 2;
  int result = find_norm(vec_cnt, &max_norm, &cnt, &cnt_p, &cnt_m,
                         &max_p_norm, &max_A_norm, p, size, matrix, get_norm, p_norm,
                         get_matrix_norm, vec1, vec2, vec3);
  
  if (result == NO_MEMORY) {
    for (int i = 0; i < size; i++) {
      free(matrix[i]);
    }
    free(matrix);
    free(max_norm);
    free(max_p_norm);
    free(max_A_norm);
    return NO_MEMORY;
  }

  printf("Max vec:\n");
  for (int i = 0; i < cnt; i++) {
    printf("Vector #%d: (", i + 1);
    for (int j = 0; j < max_norm[i].size; j++) {
      printf("%lf", max_norm[i].coordinate[j]);
      if (j < max_norm[i].size - 1) {
        printf(" ");
      }
    }
    printf(") \n");
  }
  printf("Max p-norm:\n");
  for (int i = 0; i < cnt_p; i++) {
    printf("Vector #%d: (", i + 1);
    for (int j = 0; j < max_p_norm[i].size; j++) {
      printf("%lf", max_p_norm[i].coordinate[j]);
      if (j < max_p_norm[i].size - 1) {
        printf(" ");
      }
    }
    printf(") \n");
  }

  printf("Max matrix norm:\n");

  for (int i = 0; i < cnt_m; i++) {
    printf("Vector #%d: (", i + 1);
    for (int j = 0; j < max_A_norm[i].size; j++) {
      printf("%lf", max_A_norm[i].coordinate[j]);
      if (j < max_A_norm[i].size - 1) {
        printf(" ");
      }
    }
    printf(") \n");
  }

  clean_me(matrix, max_p_norm, max_norm, max_A_norm, size);

  return 0;
}
#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>
#include <complex.h>

enum status_codes {
    OK = 1,
    ERROR = -2,
    INVALID_INPUT = 2,
    INVALID_INPUT_IN_FILE = -6,
    NO_MEMORY = -1,
    OVERFLOW_ = -3,
    UNDEFINED = -4,
    FILE_NOT_OPEN = -5,
    EMPTY = -7,
    STOP = 10
};

typedef struct {
    char *stop_time;
    char *start_time;
    char *number;
    char mark;
    double coord[2];
} Info;

typedef struct Node {
    Info stop;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;


void menu();
void default_menu();

int read_file(FILE *input, List *routes, double **coord, int *size, int *cnt);

int longest_path(List *routes, Node **max_stop, Node **min_stop);
int find_longest_route(List *routes, Node **max_stop, Node **min_stop);
int find_cnt_route(List *routes, Node **max_stop, Node **min_stop);
int find_longest_stop(List *routes, Node **max_stop);

int get_duration(const char *start, const char *stop);
int get_time(List *roots, Node **max_stop, Node **min_stop, double x, double y);

int swap_cmd(List *routes, double *coord, int cnt);

int add_stop(Info stop, Node** res);

int check_date(int day, int month, int year, int hour, int min, int sec);

void free_list(Node *head);
time_t convert_time(const char *time);
void insert(Node **head, Info stop);
int validate(int day_stop, int month_stop, int year_stop, int hour_stop, int min_stop, int sec_stop,
              int day_start, int month_start, int year_start, int hour_start, int min_start, int sec_start);

void print_routes(List *routes);
void print_scs(int state);

#endif
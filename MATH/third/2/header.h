#ifndef MYHEADER_H
#define MYHEADER_H

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

int subtract(int x, int y);
int add(int x, int y);
int decimal_to_base_2r(int num, int r, char** result);
int print_enter_menu(int* num, int* r);

#endif
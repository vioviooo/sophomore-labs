#ifndef LIBS_H
#define LIBS_H

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
    NO_MEMORY = -1,
    OVERFLOW_ = -3,
    UNDEFINED = -4
};



#endif
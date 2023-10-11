// enum... join_symb(char **src, char symb, int *capacity) {
//     if (*capacity == strlen(src) + 1) {
//         *capacity *= 2;

//         char *temp = (char*)realloc(*src, sizeof(char) * capacity);

//         if (temp == NULL) {
//             return error;
//         }

//         *src = temp;
//     }

//     (*src)[strlen(*src) + 1] = 0;
//     (*src)[strlen(*src)] = symb;
// }

// //realloc со сложностью армотизированной константы

// int get_str(char **src, FILE*) {
//     *src = NULL;
//     int capacity = 2;

//     *src = (char*)malloc(sizeof(char) * capacity);

//     while ('\n') {
//         join_symb(src, fgetc(stream), &capacity);
//     }
// }

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>

typedef long long ll;

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

enum status_codes {
    OK,
    NO_MEMORY,
    INVALID,
    VALID_POS, // positive num
    VALID_NEG, // negative num
    STOP
};

enum status_codes is_valid_base(char st[]) {
    for (int i = 0; st[i] != '\0'; i++) {
        if (!isdigit(st[i])) {
            return INVALID;
        }
    }

    int j = 0;
    while (st[j] == '0') {
        j++;
    }

    if (strlen(st) - j > 10) {
        return INVALID;
    }

    int num = atoi(st);

    if (num > 36 || num < 2) {
        return INVALID;
    }

    return OK;
}

enum status_codes is_valid_string(char* ptr) {
    bool flag = true;
    char* _ptr = ptr;
    while (*ptr != '\0') {
        if (*ptr == '-' && ptr == _ptr) {
            if (*(++_ptr) == '\0') {
                return INVALID;
            }
            if (flag) {
                flag = false;
            }
            else {
                return INVALID;
            }
        }
        else {
            if (!isalpha(*ptr) && !isdigit(*ptr)) {
                return INVALID;
            } 
        }
        ptr++;
    }
    if (flag) {
        _ptr--;
        ptr = _ptr;
        return VALID_POS;
    }
    else {
        ptr = _ptr;
        return VALID_NEG;
    }
}

// enum status_codes is_valid_string(char* ptr) {
//     bool flag = true;
//     char* _ptr = ptr;
//     while (*ptr != '\0') {
//         if (*ptr == '-' && ptr == _ptr) {
//             if (*(++_ptr) == '\0') {
//                 return INVALID;
//             }
//             if (flag) {
//                 flag = false;
//             }
//             else {
//                 return INVALID;
//             }
//         }
//         else {
//             if (!isalpha(*ptr) && !isdigit(*ptr)) {
//                 return INVALID;
//             } 
//         }
//         ptr++;
//     }
//     if (flag) {
//         _ptr--;
//         ptr = _ptr;
//         return VALID_POS;
//     }
//     else {
//         ptr = _ptr;
//         return VALID_NEG;
//     }
// }

// !!!
// enum status_codes is_valid_string(char** ptr) {
//     bool flag = true;
//     char* _ptr = *ptr;
//     while (*(*ptr) != '\0') {
//         if (*(*ptr) == '-' && (*ptr) == _ptr) {
//             if (*(++_ptr) == '\0') {
//                 return INVALID;
//             }
//             if (flag) {
//                 flag = false;
//             } else {
//                 return INVALID;
//             }
//         } else {
//             if (!isalpha(*(*ptr)) && !isdigit(*(*ptr))) {
//                 return INVALID;
//             }
//         }
//         (*ptr)++;
//     }
//     if (flag) {
//         _ptr--;
//         *ptr = _ptr;
//         return VALID_POS;
//     } else {
//         *ptr = _ptr;
//         return VALID_NEG;
//     }
// }

enum status_codes is_valid_num(char* ptr, int base) {
    while(*ptr != '\0') {
        if (isdigit(*ptr) && (*ptr - '0') >= base) {
            return INVALID;
        }
        if (isalpha(*ptr) && (*ptr - 'a' + 10) >= base) {
            return INVALID;
        }
        ptr++;
    }
    return OK;
}

///////////////////////////////////////////////////////////////////

int to_decimal(int base, char* ptr) {
    int res = 0;
    // char* ptr = num;

    while (*ptr) {
        res = res * base + (isdigit(*ptr) ? *ptr - '0' : *ptr - 'A' + 10);
        ptr++;
    }
    return res;
}

char* decimal_to_base(int base, int num) {
    char res[BUFSIZ];
    char* ptr = res + BUFSIZ - 1; // начинаем с конца
    *ptr = '\0'; // terminate
    while (num > 0) {
        int r = num % base;
        ptr--;
        *ptr = (r > 9) ? r + 'A' - 10 : r + '0';
        num /= base;
    }
    char* result = (char*)malloc(strlen(ptr) + 1);

    if (result != NULL) {
        strcpy(result, ptr);
    }
    
    return result;
}

////////////////////////////////////////////////////////////////////

enum status_codes join_symb(char symb, char **str, int *size) {
	if (*size == 0) {
		*size = 2;
		*str = (char*)malloc(sizeof(char) * *size);

		if (!*str) {
			return NO_MEMORY;
		}

		(*str)[0] = symb;
		(*str)[1] = 0;

		return OK;
	}

	int len = strlen(*str);

	if (len == *size - 1) {
		*size *= 2;
		char *temp = (char*)realloc(*str, sizeof(char) * *size);
		
		if (!temp) {
			return NO_MEMORY;
		}

		*str = temp;
	}

	(*str)[len + 1] = 0;
	(*str)[len] = symb;

	return OK;
}

enum status_codes get_str(char **str, FILE *read_file) {
	int size = 0;
	char symb = fgetc(read_file);
	enum status_codes exit_code = 0;

	if (*str) {
		free(*str);
		*str = NULL;
	}

	while (symb != '\n') {
		exit_code = join_symb(symb, str, &size);

		if (exit_code != OK) {
			return exit_code;
		}

		symb = fgetc(read_file);
	}

	if (*str) {
		char *temp = (char*)realloc(*str, sizeof(char) * (strlen(*str) + 1));

		if (!temp) {
			return NO_MEMORY;
		}

		*str = temp;
	}

    if (strcmp(*str, "Stop") == 0) {
        return STOP;
    }

	return OK;
}

////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {

    printf("%c ", (char)((int)'a' - 32));


    return 0;
}
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
            printf("\nProject finished successfully!\n");
            break;
        case NO_MEMORY:
            printf("\nNo memory left.\n");
            break;
        case OVERFLOW_:
            printf("\nOverflow!\n");
            break;
        case UNDEFINED:
            printf("\nError! What you're trying to calculate IS UNDEFINED or uses complex numbers.\n");
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
    char* data;
    int length;
} String;

int createString(const char* source, String* res) {
    String newString;
    newString.length = strlen(source);
    newString.data = (char*)malloc((newString.length + 1) * sizeof(char));
    if (newString.data == NULL) {
        return NO_MEMORY;
    }
    strcpy(newString.data, source); //!!!! 
    *res = newString;
    return OK;
}

void clearString(String* str) {
    free(str->data);
    str->data = NULL;
    str->length = 0;
}

int compareStrings(const String* str1, const String* str2) {
    if (str1->length < str2->length) {
        return -1;
    } else if (str1->length > str2->length) {
        return 1;
    }
    return strcmp(str1->data, str2->data);
}

int areStringsEqual(const String* str1, const String* str2) { return (compareStrings(str1, str2) == 0); }

int copyString(String* destination, const String* source) {
    clearString(destination);
    destination->length = source->length;
    destination->data = (char*)malloc((destination->length + 1) * sizeof(char));
    if (destination->data == NULL) {
        return NO_MEMORY;
    }
    strcpy(destination->data, source->data); //!!!!!!
    return OK;
}

int copyStringToNew(const String* source, String* dest) {
    String newString;
    newString.length = source->length;
    newString.data = (char*)malloc((newString.length + 1) * sizeof(char));
    if (newString.data == NULL) {
        return NO_MEMORY;
    }
    strcpy(newString.data, source->data);
    *dest = newString;
    return OK;
}

int concatenateStrings(String* str1, String* str2, String* res) {
    String result;
    result.length = str1->length + str2->length;
    result.data = (char*)malloc((result.length + 1) * sizeof(char));
    if (result.data == NULL) {
        return NO_MEMORY;
    }
    strcpy(result.data, str1->data);
    strcat(result.data, str2->data);
    *res = result;
    return OK;
}

int main() {
    int status;
    const char* source1 = "Hello";  // TODO: check valgrind
    const char* source2 = "World";  // TODO:

    String str1, str2;
    if ((status = createString(source1, &str1)) != OK) {
        print_scs(status);
    }
    if ((status = createString(source2, &str2)) != OK) {
        print_scs(status);
    }

    printf("String 1: %s\n", str1.data);
    printf("String 2: %s\n", str2.data);

    if (compareStrings(&str1, &str2) < 0) {
        printf("String 1 is shorter\n");
    } else if (compareStrings(&str1, &str2) > 0) {
        printf("String 2 is shorter\n");
    } else {
        printf("Strings are of equal length\n");
    }

    if (areStringsEqual(&str1, &str2)) {
        printf("Strings are equal\n");
    } else {
        printf("Strings are not equal\n");
    }

    String s;
    if ((status = concatenateStrings(&str1, &str2, &s)) != OK) {
        print_scs(status);
    }

    printf("Concatenated: %s\n", s.data);

    clearString(&s);
    clearString(&str1);
    clearString(&str2);

    return 0;
}

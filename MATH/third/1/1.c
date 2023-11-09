#include "functions.c"

int main() {
    int num, r;

    print_enter_menu(&num, &r);

    char* result;
    int status = decimal_to_base_2r(num, r, &result);

    if (status != OK) {
        print_scs(status);
        return status;
    } else {
        int base = pow(2, r);
        printf("Decimal: %d\nIn base %d: %s\n", num, base, result);
        free(result); // Don't forget to free the allocated memory
    }

    return 0;
}

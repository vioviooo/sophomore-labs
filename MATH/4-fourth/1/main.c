#include "functions.c"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("n/a\n");
        return 1;
    }

    char filename[256];
    strcpy(filename, argv[1]);

    printf("%s", filename);

    print_scs(INVALID_INPUT);

    return 0;
}

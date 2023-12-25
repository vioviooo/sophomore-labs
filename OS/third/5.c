#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <libgen.h>

enum status_codes {
    OK = 0,
    DIR_NOT_OPEN = -2,
    INVALID_INPUT = -3
};

// struct dirent {
//     ino_t d_ino;           // Inode number
//     off_t d_off;           // Offset to the next dirent
//     unsigned short d_reclen; // Length of this record
//     unsigned char d_type;   // Type of file
//     char d_name[256];       // Null-terminated filename
// };

typedef long long ll;

void ls(const char *dirPath) {
    DIR* dir = opendir(dirPath);

    if (dir == NULL) {
        perror("dir");
        return;
    }

    struct dirent *d;

    while ((d = readdir(dir)) != NULL) {
        char filepath[256];
        snprintf(filepath, sizeof(filepath), "%s", d->d_name);

        if (strcmp(d->d_name, ".") != 0 && strcmp(d->d_name, "..") != 0) {
            printf(" %s\n", ((char*)filepath));
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s dir_1 dir_2 ... dir_n\n", argv[0]);
        return INVALID_INPUT;
    }

    for (int i = 1; i < argc; i++) {
        printf("Files in the %s directory:\n", argv[i]);
        ls(argv[i]);
        printf("\n");
    }

    return OK;
}

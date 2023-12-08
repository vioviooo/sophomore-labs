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
    OK = -1,
    DIR_NOT_OPEN = -2
};

typedef long long ll;

void print_file_info(const char *filepath) {
    struct stat fileStat;
    if (stat(filepath, &fileStat) == -1) {
        perror("stat");
        return;
    }

    struct passwd *pwd = getpwuid(fileStat.st_uid);
    struct group *grp = getgrgid(fileStat.st_gid);

    if (pwd != NULL) {
        printf("%s ", pwd->pw_name);
    } else {
        printf("unknown ");
    }

    if (grp != NULL) {
        printf("%s", grp->gr_name);
    } else {
        printf("unknown");
    }

    printf(" %5lld", (ll)fileStat.st_size);

    char time_string[100];
    strftime(time_string, sizeof(time_string), "%b %d %H:%M", localtime(&fileStat.st_mtime));
    printf(" %s", time_string);

    printf(" %s\n", basename((char *)filepath));
}

void ls(const char *dirPath) {
    DIR *dir = opendir(dirPath);

    if (dir == NULL) {
        perror("dir");
        return;
    }

    struct dirent *d;

    while ((d = readdir(dir)) != NULL) {
        char filepath[256];
        snprintf(filepath, sizeof(filepath), "%s/%s", dirPath, d->d_name);

        if (strcmp(d->d_name, ".") != 0 && strcmp(d->d_name, "..") != 0) {
            print_file_info(filepath);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s dir_1 dir_2 ... dir_n\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        printf("Files in the %s directory:\n", argv[i]);
        ls(argv[i]);
        printf("\n");
    }

    return 0;
}

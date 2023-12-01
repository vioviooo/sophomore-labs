#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void printFileInfo(const char *filePath) {
    struct stat fileStat;

    if (stat(filePath, &fileStat) == -1) {
        perror("stat");
        return;
    }

    if (S_ISREG(fileStat.st_mode))
        printf("-");
    else if (S_ISDIR(fileStat.st_mode))
        printf("d");
    else if (S_ISCHR(fileStat.st_mode))
        printf("c");
    else if (S_ISBLK(fileStat.st_mode))
        printf("b");
    else if (S_ISFIFO(fileStat.st_mode))
        printf("f");
    else if (S_ISLNK(fileStat.st_mode))
        printf("l");
    else if (S_ISSOCK(fileStat.st_mode))
        printf("s");
    else
        printf("?");

    printf("%c%c%c%c%c%c%c%c%c",
           (fileStat.st_mode & S_IRUSR) ? 'r' : '-',
           (fileStat.st_mode & S_IWUSR) ? 'w' : '-',
           (fileStat.st_mode & S_IXUSR) ? 'x' : '-',
           (fileStat.st_mode & S_IRGRP) ? 'r' : '-',
           (fileStat.st_mode & S_IWGRP) ? 'w' : '-',
           (fileStat.st_mode & S_IXGRP) ? 'x' : '-',
           (fileStat.st_mode & S_IROTH) ? 'r' : '-',
           (fileStat.st_mode & S_IWOTH) ? 'w' : '-',
           (fileStat.st_mode & S_IXOTH) ? 'x' : '-');

    printf(" %2ld", (long)fileStat.st_nlink);

    struct passwd *pwd = getpwuid(fileStat.st_uid);
    struct group *grp = getgrgid(fileStat.st_gid);
    printf(" %s %s", (pwd != NULL) ? pwd->pw_name : "unknown", (grp != NULL) ? grp->gr_name : "unknown");

    printf(" %5lld", (long long)fileStat.st_size);

    char timeString[100];
    strftime(timeString, sizeof(timeString), "%b %d %H:%M", localtime(&fileStat.st_mtime));
    printf(" %s", timeString);

    printf(" %s\n", filePath);
}

void listFilesInDirectory(const char *dirPath) {
    DIR *dir = opendir(dirPath);

    if (dir == NULL) {
        perror("opendir");
        return;
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        char filePath[256];
        snprintf(filePath, sizeof(filePath), "%s/%s", dirPath, entry->d_name);

        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            printFileInfo(filePath);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s directory1 [directory2 ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        printf("Listing files in directory: %s\n", argv[i]);
        listFilesInDirectory(argv[i]);
        printf("\n");
    }

    return 0;
}

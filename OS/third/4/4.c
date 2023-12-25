#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void print_usage() {
    printf("Options:\n");
    printf("  -r  Set read-only attribute\n");
    printf("  -w  Set write-only attribute\n");
    printf("  -x  Set execute-only attribute\n");
}

// struct stat {
//     dev_t     st_dev;         // ID of device containing file
//     ino_t     st_ino;         // Inode number
//     mode_t    st_mode;        // File type and mode
//     nlink_t   st_nlink;       // Number of hard links
//     uid_t     st_uid;         // User ID of owner
//     gid_t     st_gid;         // Group ID of owner
//     off_t     st_size;        // Total size, in bytes
//     time_t    st_atime;       // Time of last access
//     time_t    st_mtime;       // Time of last modification
//     time_t    st_ctime;       // Time of last status change
//     blksize_t st_blksize;     // Optimal block size for I/O
//     blkcnt_t  st_blocks;      // Number of 512B blocks allocated
// };


int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Invalid input. Usage: ./a.out <file_path> [-r] [-w] [-x]\n");
        return EXIT_FAILURE;
    }

    const char *file_path = argv[1];
    for (int i = 2; i < argc; i++) {
        struct stat file_stat;

        if (stat(file_path, &file_stat) != 0) {
            printf("Error getting file attributes!\n");
            return EXIT_FAILURE;
        }

        if (argv[i][0] == '-' && argv[i][1] == 'r') {
            file_stat.st_mode &= ~S_IRWXU; // reverse bits for reading
        } else if (argv[i][0] == '-' && argv[i][1] == 'w') {
            file_stat.st_mode &= ~S_IRWXG; // reverse bits for writing
        } else if (argv[i][0] == '-' && argv[i][1] == 'x') {
            file_stat.st_mode &= ~S_IRWXO; // reverse bits for execution
        } else {
            printf("Invalid input: %s\n", argv[i]);
            print_usage();
            return EXIT_FAILURE;
        }

        // set new file attributes
        if (chmod(file_path, file_stat.st_mode) != 0) {
            printf("Error changing file attributes!\n");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

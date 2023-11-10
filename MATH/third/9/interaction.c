#include "header.h"
// #include <ncurses.h>

void print_default_menu() {
    printf("\nChoose your action:\n1. Output number of occurences of all words from the file.\n");
    printf("2. Output N most popular words (based on the number of occurences).\n3. Output the longest and the shortes words.\n");
    printf("4. Check if a certain word is present in the file.\n5. Exit.\n");
    printf("Please, enter your choice: ");
}
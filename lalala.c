#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>

#define ROWS 25
#define COLS 80

void initialize_board(char init_board_state, char cell_symbol, char (*blank_board)[COLS], char (*board)[COLS], const char* filename) {
    if (init_board_state == 'b') {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                blank_board[i][j] = ' ';
            }
        }
    } else if (init_board_state == 'r') {
        srand(time(NULL)); // seed the randomizer with curr time
        int x;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                x = rand() % 2;
                if (x == 1) {
                    board[i][j] = cell_symbol;
                } else {
                    board[i][j] = ' ';
                }
            }
        }
    } else if (init_board_state == 'f') {
        FILE* fptr;
        fptr = fopen(filename, "r");
        if (fptr == NULL) {
            endwin();
            printf("Error! Couldn't open the file.");
            exit(1);
        }  
        char ch;
        int i = 0, j = 0;
        while ((ch = fgetc(fptr)) != EOF) {
            if (ch == '\n') {
                i++;
                j = 0;
            } else if (ch == '1') {
                board[i][j] = cell_symbol;
            } else if (ch == '0') {
                board[i][j] = ' ';
            } else {
                endwin();
                printf("Error! Invalid character in the file.");
                exit(1);
            }
            j++;
            refresh();
        }
        fclose(fptr);
    }
}

int cnt_cell_neighbor(int i, int j, char (*board)[COLS], char cell_symbol) {
    int cnt = 0;
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if (x != 0 || y != 0) {
                int neighbor_i = (i + x + ROWS) % ROWS;
                int neighbor_j = (j + y + COLS) % COLS;

                if (board[neighbor_i][neighbor_j] == cell_symbol) {
                    cnt++;
                }
            }
        }
    }
    return cnt;
}

void next_gen_cell(int i, int j, int cnt, char (*board)[COLS], char (*blank_board)[COLS], char cell_symbol) {
    if (board[i][j] == cell_symbol) {
        if (cnt < 2) {
            blank_board[i][j] = ' ';
        } else if (cnt == 2 || cnt == 3) {
            blank_board[i][j] = cell_symbol;
        } else {
            blank_board[i][j] = ' ';
        }
    }
    else {
        if (cnt == 3) {
            blank_board[i][j] = cell_symbol;
        }
    }
}

void next_gen_board(char (*board)[COLS], char (*blank_board)[COLS], char cell_symbol) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int cnt = cnt_cell_neighbor(i, j, board, cell_symbol);
            next_gen_cell(i, j, cnt, board, blank_board, cell_symbol);
        }
    }
}

void update_prev_board(char (*board)[COLS], char (*blank_board)[COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = blank_board[i][j];
        }
    }
}

void print_curr_board(char (*board)[COLS], int evolution, int time_between_evo) {
    clear();

    // top border
    mvhline(0, 0, '+', COLS + 2);

    char* title = "GAME OF LIFE";
    int title_len = 12;
    int pos_x = (COLS - title_len) / 2;
    mvprintw(0, pos_x, title);

    // bottom border
    mvhline(ROWS + 1, 0, '+', COLS + 2);

    for (int i = 1; i <= ROWS; i++) {
        mvaddch(i, 0, '|'); // left border
        mvaddch(i, COLS + 1, '|'); // right border
    }

    // matrix display
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            mvaddch(i + 1, j + 1, board[i][j]);
        }
    }

    mvprintw(ROWS + 2, 0, "Generation = %d", evolution);

    refresh(); // refresh the screen
    usleep(time_between_evo); // delay
}

void display_default_menu() {
    printw("Welcome to the Game of Life!\n\n");
    printw("1. Start\n");
    printw("2. Exit\n");
    printw("Enter your choice: ");
}

int main() {
    int evolutions = 100;
    int time_between_evo = 20000;

    char cell_symbol = 'o';
    char filename[] = "1.txt";
    
    char blank_board[25][80];
    char board[25][80];

    initscr();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(1));

    int choice;
    while (true) {
        clear();
        display_default_menu();
        refresh();
        scanw("%d", &choice);

        if (choice == 1) {
            refresh();
            noecho();
            curs_set(FALSE);

            initialize_board('r', cell_symbol, blank_board, board, filename);

            for (int evo = 0; evo < evolutions; evo++) {
                initialize_board('b', cell_symbol, blank_board, board, filename);
                next_gen_board(board, blank_board, cell_symbol);
                update_prev_board(board, blank_board);
                print_curr_board(board, evo, time_between_evo);
            }

            endwin();
        } else if (choice == 2) {
            endwin();
            printf("You have exited the game.");
            exit(0);
        } else {
            endwin();
            printf("You have enterd an invalid command.");
            exit(1);
        }
    }

    return 0;
}

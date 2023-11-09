#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>

#define ROWS 25
#define COLS 80

int i, j;

char blank_board[25][80];
char board[25][80];

char init_board_state = 'r';
char cell_symbol = 'o';

char filename[] = "1.txt";

int evolutions = 10000;
int time_between_evo = 20000; // in microseconds, 1 sec = 1 000 000 microsec

void initialize_board(char init_board_state) {
    if (init_board_state == 'b') {
        for (i = 0; i < ROWS; i++) {
            for (j = 0; j < COLS; j++) {
                blank_board[i][j] = ' ';
            }
        }
    } else if (init_board_state == 'r') {
        srand(time(NULL));
        int x;
        for (i = 0; i < ROWS; i++) {
            for (j = 0; j < COLS; j++) {
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
            printf("Error! Couldn't open the file.");
            exit(1);
        }  
        char ch;
        i = 0, j = 0;
        while ((ch = fgetc(fptr)) != EOF) {
            if (ch == '\n') {
                i++;
                j = 0;
            } else if (ch == '1') {
                board[i][j] = cell_symbol;
            } else if (ch == '0') {
                board[i][j] = ' ';
            } else {
                printf("Error! Invalid character in the file.");
                exit(1);
            }
            j++;
            refresh();
        }
        fclose(fptr);
    }
}

int cnt_cell_neighbor(int i, int j) {
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

void next_gen_cell(int i, int j, int cnt) {
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

void next_gen_board() {
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            int cnt = cnt_cell_neighbor(i, j);
            next_gen_cell(i, j, cnt);
        }
    }
}

void update_prev_board() {
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            board[i][j] = blank_board[i][j];
        }
    }
}

void print_curr_board(int evolution) {

    clear();

    // top border
    mvhline(0, 0, '+', COLS + 2);

    char* title = "GAME OF LIFE";
    int title_len = 12;
    int pos_x = (COLS - title_len) / 2;
    mvprintw(0, pos_x, title);

    // bottom border
    mvhline(ROWS + 1, 0, '+', COLS + 2);

    for (i = 1; i <= ROWS; i++) {
        mvaddch(i, 0, '|'); // left border
        mvaddch(i, COLS + 1, '|'); // right border
    }

    // matrix display
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            mvaddch(i + 1, j + 1, board[i][j]);
        }
    }

    mvprintw(ROWS + 2, 0, "Generation = %d", evolution);

    refresh(); // refresh the screen
    usleep(time_between_evo); // delay
}

void displayMenu() {
    printw("Welcome to the Game of Life!\n\n");
    printw("1. Start\n");
    printw("2. Exit\n");
    printw("Enter your choice: ");
}

int main(int argc, char *argv[]) {

    if (argc > 1) {
        time_between_evo = atoi(argv[1]);
    }

    initscr(); // initialize ncurses
    start_color();

    init_pair(1, COLOR_YELLOW, COLOR_BLACK); // define color pair with yellow text on black background
    attron(COLOR_PAIR(1)); // turn on color attribute

    int choice;
    while (1) {
        clear();
        displayMenu();
        refresh();

        // Get user input for menu choice
        scanw("%d", &choice);

        if (choice == 1) {
            refresh();

            noecho(); // don't display user input
            curs_set(FALSE); // don't show the cursor

            initialize_board(init_board_state);

            for (int evo = 0; evo < 10000000; evo++) {
                initialize_board('b');
                next_gen_board();
                update_prev_board();
                print_curr_board(evo);
            }

            endwin();  // end lncurses
        } else if (choice == 2) {
            endwin();
            exit(0);
        }
    }

    return 0;
}

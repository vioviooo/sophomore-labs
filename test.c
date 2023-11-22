#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>

char boardInitState = 'r';
int i, j, cnt;
const int nRows = 25;
const int nCols = 80;
char board[25][80];
char blankBoard[25][80];
int evolutions = 10000;
int timeBetweenEvolutions = 20000;
char cell_symbol = 'o';

void initialize_board(char boardInitState) {
    if (boardInitState == 'b') {
        for (i = 0; i < nRows; i++) {
            for (j = 0; j < nCols; j++) {
                blankBoard[i][j] = ' ';
            }
        }
    } else if (boardInitState == 'r') {
        srand(time(NULL));
        int x;
        for (i = 0; i < nRows; i++) {
            for (j = 0; j < nCols; j++) {
                x = rand() % 2;
                if (x == 1) {
                    board[i][j] = cell_symbol;
                } else {
                    board[i][j] = ' ';
                }
            }
        }
    } else if (boardInitState == 'f') {
        FILE* fptr;
        char filename[] = "1.txt";
        fptr = fopen(filename, "r");
        
        if (fptr == NULL) {
            printf("Error! Couldn't open the file.");
            exit(1);
        }
        
        int i_ = 0, j_ = 0;
        char ch;
        while ((ch = fgetc(fptr)) != EOF) {
            if (ch == '\n') {
                i_++;
                j_ = 0;
            } else if (ch == '1') {
                board[i_][j_] = cell_symbol;
            } else if (ch == '0') {
                board[i_][j_] = ' ';
            } else {
                printf("Error! Invalid character in the file.");
                exit(1);
            }
            j_++;
            refresh();
        }

        fclose(fptr);
    }
}

int cnt_cell_neighbor(int i, int j) {
    int cnt = 0;

    if (i - 1 > 0) {
        if (board[i - 1][j] == cell_symbol) {
            cnt += 1;
        }
        if (j - 1 > 0) {
            if (board[i - 1][j - 1] == cell_symbol) {
                cnt += 1;
            }
        }
        if (j + 1 < nCols) {
            if (board[i - 1][j + 1] == cell_symbol) {
                cnt += 1;
            }
        }
    }

    if (i + 1 < nRows) {
        if (board[i + 1][j] == cell_symbol) {
            cnt += 1;
        }

        if (j - 1 > 0) {
            if (board[i + 1][j - 1] == cell_symbol) {
                cnt += 1;
            }
        }
        if (j + 1 < nCols) {
            if (board[i + 1][j + 1] == cell_symbol) {
                cnt += 1;
            }
        }
    }

    if (j + 1 < nCols) {
        if (board[i][j + 1] == cell_symbol) {
            cnt += 1;
        }
    }

    if (j - 1 > 0) {
        if (board[i][j - 1] == cell_symbol) {
            cnt += 1;
        }
    }

    return cnt;
}

void next_gen_cell(int i, int j, int cnt) {
    if (board[i][j] == cell_symbol) {
        if (cnt < 2) {
            blankBoard[i][j] = ' ';
        } else if (cnt == 2 || cnt == 3) {
            blankBoard[i][j] = cell_symbol;
        } else {
            blankBoard[i][j] = ' ';
        }
    }
    else {
        if (cnt == 3) {
            blankBoard[i][j] = cell_symbol;
        }
    }
}

void next_gen_board() {
    for (i = 0; i < nRows; i++) {
        for (j = 0; j < nCols; j++) {
            cnt = cnt_cell_neighbor(i, j);
            next_gen_cell(i, j, cnt);
        }
    }
}

void update_prev_board() {
    for (i = 0; i < nRows; i++) {
        for (j = 0; j < nCols; j++) {
            board[i][j] = blankBoard[i][j];
        }
    }
}

void print_curr_board(int evolution) {
    clear();  // Clear the screen

    // Display the top border
    mvhline(0, 0, '+', nCols + 2);

    char* title = "GAME OF LIFE";
    int titleLen = strlen(title);
    int titleX = (nCols - titleLen) / 2;  // Center the text horizontally
    mvprintw(0, titleX, title);

    // Display the bottom border
    mvhline(nRows + 1, 0, '+', nCols + 2);

    // Display the left and right borders for each row
    for (i = 1; i <= nRows; i++) {
        mvaddch(i, 0, '|');           // Left border
        mvaddch(i, nCols + 1, '|');       // Right border
    }

    // Display the matrix
    for (i = 0; i < nRows; i++) {
        for (j = 0; j < nCols; j++) {
            mvaddch(i + 1, j + 1, board[i][j]);  // Move to (i+1, j+1) to account for borders and print the character
        }
    }

    // Display the generation number at the bottom
    mvprintw(nRows + 2, 0, "Generation = %d", evolution);

    refresh();  // Refresh the screen
    usleep(timeBetweenEvolutions);  // Delay
}

int main(int argc, char *argv[]) {

    if (argc > 1) {
        timeBetweenEvolutions = atoi(argv[1]);
    }

    initscr();  // initialize ncurses
    noecho();   // don't display user input
    curs_set(FALSE);  // hide the cursor
    start_color();

    init_pair(1, COLOR_YELLOW, COLOR_BLACK); // define color pair with yellow text on black background
    attron(COLOR_PAIR(1)); // Turn on color attribute

    initialize_board(boardInitState);

    for (int e = 0; e < 100; e++) {
        initialize_board('b');
        next_gen_board();
        update_prev_board();
        print_curr_board(e);
    }

    endwin();  // End ncurses

    return 0;
}

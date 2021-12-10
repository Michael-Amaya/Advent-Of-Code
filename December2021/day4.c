#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"

#define MAX_COLUMNS 5
#define MAX_ROWS 5

typedef struct {
    int board[MAX_ROWS][MAX_COLUMNS];
    int matched[MAX_ROWS][MAX_COLUMNS];
    int filled;
} bingo_board;

typedef struct {
    int* arr;
    int size;
} array;

array* get_called_numbers();
bingo_board** get_bingo_boards();
int check_board_win(bingo_board* board);
int get_solution(bingo_board* winning_board, int last_called);

int main() {
    array* called_numbers = get_called_numbers();
    scanf("%*c"); // Ignore new line
    bingo_board** boards = get_bingo_boards();

    int just_called = 0;

    // for(int i = 0; boards[i]->board[0][0] != -1; i++) {
    //     printf("CHECKING board %d with [0][0]: %d!\n", i, boards[i]->board[0][0]);
    // }

    bingo_board* winning_board = NULL;

    for(int i = 0; i < called_numbers->size; i++) {
        just_called = called_numbers->arr[i];
        int breakout = 0;

        for (int j = 0; boards[j]->board[0][0] != -1; j++) {
            for (int k = 0; k < MAX_ROWS; k++) {
                for (int l = 0; l < MAX_COLUMNS; l++) {
                    if(called_numbers->arr[i] == boards[j]->board[k][l]) {
                        boards[j]->matched[k][l] = 1;
                    }

                    if (check_board_win(boards[j])) {
                        winning_board = boards[j];
                        breakout = 1;
                        break;
                    }
                }

                if (breakout) {
                    break;
                }
            }

            if (breakout) {
                break;
            }
        }

        if (breakout) {
            break;
        }
    }

    printf("The answer for part1 is %d\n", get_solution(winning_board, just_called));

    for (int i = 0; boards[i]->board[0][0] != -1; i++) {
        free(boards[i]);
    }
    free(boards);
    free(called_numbers);
    return 0;
}

array* get_called_numbers() {
    int size = 0;
    int* called_numbers = (int*) Calloc(0, sizeof(int));

    for(;;) {
        int buffer;
        char trailing_char;
        scanf("%d%c", &buffer, &trailing_char);
        
        called_numbers = (int*) Realloc(called_numbers, size + 1, sizeof(int));
        called_numbers[size++] = buffer;

        if (trailing_char == '\n') {
            break;
        }
    }

    array* arr = (array*) Calloc(1, sizeof(array));
    arr->arr = called_numbers;
    arr->size = size;

    return arr;
}

bingo_board** get_bingo_boards() {
    bingo_board** boards = (bingo_board**) Calloc(0, sizeof(bingo_board*));

    for(int board_num = 0; ; board_num++) {
        boards = (bingo_board**) Realloc(boards, board_num + 1, sizeof(bingo_board*));
        boards[board_num] = (bingo_board*) Calloc(1, sizeof(bingo_board));
        

        int breakout = 0;

        for(int i = 0; i < MAX_ROWS; i++) {
            for (int j = 0; j < MAX_COLUMNS; j++) {
                int buffer;
                scanf("%02d%*c", &buffer);
                // boards[board_num] = (bingo_board*) Realloc(boards[board_num], board_num + 1, sizeof(bingo_board));
                boards[board_num]->board[i][j] = buffer;
                boards[board_num]->matched[i][j] = 0;
                // printf("GOT %d\n", buffer);

                if (buffer == -1) {
                    breakout = 1;
                    break;
                }
            }

            boards[board_num]->filled = 1;
            if (breakout) {
                break;
            }
        }

        if (!boards[board_num]->filled) {
            free(boards[board_num]);
            boards[board_num] = NULL;
        }

        if(breakout) {
            break;
        }

        scanf("%*c");
    }

    return boards;
}

int check_board_win(bingo_board* board) {
    /* Check row win */
    int counter = 0;
    for(int i = 0; i < MAX_ROWS; i++) {
        counter = 0;
        for(int j = 0; j < MAX_COLUMNS; j++) {
            if (board->matched[i][j] == 1) {
                counter++;
            }
        }

        if (counter == MAX_ROWS) {
            return 1; // win!
        }
    }

    /* Check column win */
    for (int i = 0; i < MAX_COLUMNS; i++) {
        counter = 0;
        for (int j = 0; j < MAX_ROWS; j++) {
            if (board->matched[j][i] == 1) {
                counter++;
            }
        }

        if (counter == MAX_COLUMNS) {
            return 1; // win
        }
    }

    return 0;
}

int get_solution(bingo_board* winning_board, int last_called) {
    int solution = 0;
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLUMNS; j++) {
            if(winning_board->matched[i][j] == 0) {
                solution += winning_board->board[i][j];
            }
        }
    } 

    return solution * last_called;
}

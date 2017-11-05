
#include <stdlib.h>
#include <stdio.h>
#include "triangle_routines.h"

#define BOARD_DEPTH 5

/**
 * Transform the original index to the index in the transformed array
 * @param index original array index
 * @return the index in the transformed array
 */
int index_from_original(int index) {

    int count = 0;

    for (int i = 0; i < BOARD_DEPTH; i++) {
        for (int k = 0; k < BOARD_DEPTH; k++) {
            if (k <= i) {
                count++;
            }

            if (count == index + 1) {
                return i * 5 + k;
            }


        }
    }
    return -1;
}

/**
 * tranform the index of the transformed array to the original index
 * @param index in the transformed array
 * @return the index in the original array
 */
int index_to_original(int index) {
    int x = (index % BOARD_DEPTH);
    int y = (index / BOARD_DEPTH);

    int sum = 0;
    for (int i = 0; i < y; i++) {
        sum = sum + (i + 1);
    }

    return sum + x;
}

/**
 * Initialize empty board
 *
 * @param board
 * @param depth
 */
void initBoard(int board[], int depth) {
    for (int i = 0; i < depth * depth; i++) {
        int value;
        if (i % depth <= i / depth) {
            value = 1;
        } else {
            value = 2;
        }
        board[i] = value;

    }
}

/**
 * Return the number of entries on the board.
 * @param board the board
 * @return the number of entries on the board
 */
int nentries(int board[]) {
    int count = 0;
    for (int i = 0; i < BOARD_DEPTH * BOARD_DEPTH; i++) {
        if (board[i] == 1) {
            count++;
        }
    }

    return count;
}

/**
 * Determine if all of the move indices are on the board
 * @param board
 * @param move the move array
 * @return 1 if all move indices are on the board, 0 if not
 */
int isOnBoard(int board[], int move[]) {
    int result = 1;
    if (board[move[0]] == 2 || board[move[1]] == 2 || board[move[2]] == 2) {
        result = 0;
    }

    return result;
}

/**
 * Determine if only the end position is empty
 * @param board
 * @param move
 * @return 1 if only the end position is empty, 0 else
 */
int isEmptyOnlyAtEnd(int board[], int move[]) {
    int result = 0;
    if (board[move[0]] == 1 && board[move[1]] == 1 && board[move[2]] == 0) {
        result = 1;
    }

    return result;
}

/**
 * Get the x position of the index
 * @param position
 * @return
 */
int getX(int position) {
    return position % BOARD_DEPTH;
}

/**
 * Get the y position of the index
 * @param position
 * @return
 */
int getY(int position) {
    return position / BOARD_DEPTH;
}

/**
 * Determine if the move is horizonal aligned
 * @param board
 * @param move
 * @return
 */
int isHorizontalAligned(int board[], int move[]) {
    int startX = getX(move[0]);
    int overX = getX(move[1]);
    int endX = getX(move[2]);

    int startY = getY(move[0]);
    int overY = getY(move[1]);
    int endY = getY(move[2]);

    int dif1X = abs(startX - overX);

    int dif2X = abs(overX - endX);

    int dif3X = abs(startX - endX);

    int result = 0;
    if (dif1X == 1 && dif2X == 1 && dif3X == 2 && startY == overY && overY == endY) {
        result = 1;
    }

    return result;
}

/**
 * Determine if the move is diagonal aligned
 * @param board
 * @param move
 * @return
 */
int isDiagonalAligned(int board[], int move[]) {
    int startX = getX(move[0]);
    int startY = getY(move[0]);

    int overX = getX(move[1]);
    int overY = getY(move[1]);

    int endX = getX(move[2]);
    int endY = getY(move[2]);

    int dif1X = abs(startX - overX);
    int dif1Y = abs(startY - overY);

    int dif2X = abs(overX - endX);
    int dif2Y = abs(overY - endY);

    int dif3X = abs(startX - endX);
    int dif3Y = abs(startY - endY);

    int result = 0;


    if (dif1X <= 1 && dif2X <= 1 && dif1Y == 1 && dif2Y == 1 && dif3Y == 2) {
        if (dif3X == 2 && dif1X == 1 && dif2X == 1) {
            result = 1;
        }

        if (dif3X == 0 && dif1X == 0 && dif2X == 0) {
            result = 1;
        }
    }

    return result;
}

/**
 * Determine if the move is in some way horizontal or diagonal aligned
 * @param board
 * @param move
 * @return
 */
int isAligned(int board[], int move[]) {
    int result = 0;

    if (isDiagonalAligned(board, move) == 1 || isHorizontalAligned(board, move) == 1) {
        result = 1;
    }

    return result;
}

/* Return 1 if the move is valid on this board, otherwise return 0. */
int valid_move(int *board, int *move) {
    int result = 0;
    if (isOnBoard(board, move) == 1 && isEmptyOnlyAtEnd(board, move) == 1 && isAligned(board, move) == 1) {
        result = 1;
    }

    return result;
}

/* Make a move on this board. */
void make_move(int board[], int move[]) {
    if (valid_move(board, move) == 0) {
        printf("Not a valid move. \n");
        exit(EXIT_FAILURE);
    }

    board[move[0]] = 0;
    board[move[1]] = 0;
    board[move[2]] = 1;
}

/* Unmake this move on this board. */
void unmake_move(int board[], int move[]) {
    board[move[0]] = 1;
    board[move[1]] = 1;
    board[move[2]] = 0;
}


/**
 * Solve the game starting from this board. Return 1 if the game can
 * be solved; otherwise return 0. Do not permanently alter the board
 * passed in. Once a solution is found, print the boards making up  the
 * solution in reverse order.
 */
int solve(int board[]) {
    if (nentries(board) == 1) {
        return 1;
    }

    int board_size = BOARD_DEPTH * BOARD_DEPTH;
    for (int from = 0; from < board_size; from++) {
        for (int over = 0; over < board_size; over++) {
            for (int to = 0; to < board_size; to++) {
                int move[] = {from, over, to};

                if (valid_move(board, move)) {

                    make_move(board, move);

                    if (solve(board) == 1) {
                        printf("Move from %d over %d to %d. \n", index_to_original(from), index_to_original(over),
                               index_to_original(to));
                        return 1;
                    } else {
                        unmake_move(board, move);
                    }
                }
            }
        }
    }
    return 0;
}

int main(void) {
    int board[BOARD_DEPTH * BOARD_DEPTH];

    initBoard(board, BOARD_DEPTH);

    int orig_board[15];

    triangle_input(orig_board);

    printf("Import board .... \n");

    for (int i = 0; i < 15; i++) {
        int index = index_from_original(i);
        board[index] = orig_board[i];
    }

    printf("Board initialized. \n");
    printf("Try to solve .... \n");

    if (solve(board) == 0) {
        printf("No solution found. \n");
    } else {
        printf("Solved. \n");
    }
}
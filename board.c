#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"
#include "input.h"
#include "ships.h"
#include "stages.h"

/**
 * Creates board of size 10 by 10
 * @param none: none
 * @return struct of type board representing the board
 */
board create_board() {
    board boardStruct;
    boardStruct.squares = (char**)malloc(10 * sizeof(char*));
    for (int r = 0; r < 10; r++) {
        boardStruct.squares[r] = (char*)malloc(10 * sizeof(char));
    }
    for (int r = 0; r < 10; r++) {
        for (int c = 0; c < 10; c++) {
            boardStruct.squares[r][c] = '.';
        }
    }
    return boardStruct;
}   

/**
 * Prints the board requested
 * @param currentBoard: board struct representing the board to be printed
 * @return nothing
 */
void print_board(board currentBoard) {
    int y_axis_label = 9;
    for (int r = 0; r < 10; r++) {
        printf("    %d ", y_axis_label);
        y_axis_label--;
        for (int c = 0; c < 10; c++) {
            printf("%c ", currentBoard.squares[r][c]);
        }
        printf("\n");
    }
    printf("      ");
    for (int c = 0; c < 10; c++) {
        printf("%d ", c);
    }
}

/**
 * Frees memory associated with a board
 * @param currentBoard: pointer to board struct to deallocate memory for
 * @return nothing
 */
void delete_board(board* currentBoard) {
    for (int r = 0; r < 10; r++) {
            free(currentBoard->squares[r]);
        }
    free(currentBoard->squares);
}

/**
 * "Draws" ship onto board by modifying 2D array
 * @param currentBoard: pointer to board struct to "draw" ship onto
 * @param currentShip: ship struct containing coordinates for drawing ship
 * @return nothing
 * @modifies currentBoard
 */
void draw_ship(board* currentBoard, ship currentShip) {
    if (is_horizontal(currentShip.startRow, currentShip.endRow)) {
        currentBoard->squares[9 - currentShip.startRow][currentShip.startCol] = '<';
        for (int c = currentShip.startCol + 1; c < currentShip.endCol; c++) {
            currentBoard->squares[9 - currentShip.startRow][c] = '-';
        }
        currentBoard->squares[9 - currentShip.startRow][currentShip.endCol] = '>';
    }
    if (is_vertical(currentShip.startCol, currentShip.endCol)) {
        currentBoard->squares[9 - currentShip.startRow][currentShip.startCol] = 'v';
        for (int r = 9 - currentShip.startRow - 1; r > 9 - currentShip.endRow; r--) {
            currentBoard->squares[r][currentShip.startCol] = '|';
        }
        currentBoard->squares[9 - currentShip.endRow][currentShip.startCol] = '^';
    }
}

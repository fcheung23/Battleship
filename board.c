#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"
#include "input.h"
#include "ships.h"
#include "stages.h"

// creates board of size 10 x 10
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

// prints the board
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

// frees current board's memory
void delete_board(board* currentBoard) {
    for (int r = 0; r < 10; r++) {
            free(currentBoard->squares[r]);
        }
    free(currentBoard->squares);
}

// draws the ship on the board needed given the ship
void draw_ship(board* currentBoard, ship currentShip) {
    // if horizontal ship yeah draw that
    if (is_horizontal(currentShip.startRow, currentShip.endRow)) {
        currentBoard->squares[9 - currentShip.startRow][currentShip.startCol] = '<';
        for (int c = currentShip.startCol + 1; c < currentShip.endCol; c++) {
            currentBoard->squares[9 - currentShip.startRow][c] = '-';
        }
        currentBoard->squares[9 - currentShip.startRow][currentShip.endCol] = '>';
    }
    // if vertical ship draw that hell yeah
    if (is_vertical(currentShip.startCol, currentShip.endCol)) {
        currentBoard->squares[9 - currentShip.startRow][currentShip.startCol] = 'v';
        for (int r = 9 - currentShip.startRow - 1; r > 9 - currentShip.endRow; r--) {
            currentBoard->squares[r][currentShip.startCol] = '|';
        }
        currentBoard->squares[9 - currentShip.endRow][currentShip.startCol] = '^';
    }
}
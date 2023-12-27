#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "ships.h"

#ifndef BOARD_H
#define BOARD_H

typedef struct board_struct{
    char** squares;
} board;
board create_board();
void print_board(board currentBoard);
void delete_board(board* currentBoard);
void draw_ship(board* currentBoard, ship currentShip); 

#endif
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "board.h"

#ifndef INPUT_H
#define INPUT_H

bool isValidFormat(const int num_args_needed, const int num_args_read,
    bool should_be_last_value_on_line);
int getValidInt(const bool isLastElementOnLine);
int getPosInt(const bool isLastElementOnLine);
bool is_horizontal(int startRow, int endRow);
bool is_vertical(int startCol, int endCol);
bool is_correct_length(int length, int startRow, int startCol, int endRow, int endCol);
bool is_ship_overlapping(board pShips, int startRow, int startCol, int endRow, int endCol);
bool is_valid_ship(int length, board pShips, int startRow, int startCol, int endRow, int endCol);
void get_valid_hull(int* startRow, int* startCol, int* endRow, int* endCol);
void get_valid_target(int* targetRow, int* targetCol);
bool is_valid_target(board attackBoard, int targetRow, int targetCol);
bool is_hit(board* attackBoard, board* pShips, ship* p_carrier, ship* p_battleship, ship* p_destroyer, 
    ship* p_submarine, ship* p_patrol_boat, int targetRow, int targetCol);

#endif
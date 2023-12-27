#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "board.h"
#include "input.h"
#include "ships.h"
#include "stages.h"

// usual bullshit
bool isValidFormat(const int num_args_needed, const int num_args_read,
    bool should_be_last_value_on_line) {
    bool format_is_correct = num_args_read == num_args_needed;
    char last_value;
    if (should_be_last_value_on_line) {
        while (isspace(last_value = getchar()) && last_value != '\n');
        format_is_correct = format_is_correct && (last_value == '\n' || last_value == EOF);
    }
    return format_is_correct;
}

int getValidInt(const bool isLastElementOnLine) {
    const int numArgsNeeded = 1;
    int numArgsRead;
    int num;

    numArgsRead = scanf(" %d", &num);
  
    if (isValidFormat(numArgsNeeded, numArgsRead, isLastElementOnLine)) {
        return num;
    } else {
        return -1; 
    }
}

int getPosInt(const bool isLastElementOnLine) {
    int num = getValidInt(isLastElementOnLine);
    if (num >= 0) {
        return num;
    }
    else {
        if (isLastElementOnLine) while (getchar() != '\n');
        return -1;
    }
}

// checks if ship entered is horizontal
bool is_horizontal(int startRow, int endRow) {
    if (startRow == endRow) return true;
    else return false;
}

// checks if ship entered is vertical
bool is_vertical(int startCol, int endCol) {
    if (startCol == endCol) return true;
    else return false;
}

// checks if ship entered is the correct length
bool is_correct_length(int length, int startRow, int startCol, int endRow, int endCol) {
   // making sure it can be from any direction
   if (endRow < startRow) {
        int temp = startRow;
        startRow = endRow;
        endRow = temp;
    }
    if (endCol < startCol) {
        int temp = startCol;
        startCol = endCol;
        endCol = temp;
    }
    // check if ship meets length requirement based on its orientation
    if (is_horizontal(startRow, endRow) && ((endCol - startCol + 1) != length)) return false;
    else if (is_vertical(startCol, endCol) && ((endRow - startRow + 1) != length)) return false;
    else return true;
}

// checks if the ship is overlapping another
bool is_ship_overlapping(board pShips, int startRow, int startCol, int endRow, int endCol) {
    bool result = false;
    // making sure it can be from any direction
   if (endRow < startRow) {
        int temp = startRow;
        startRow = endRow;
        endRow = temp;
    }
    if (endCol < startCol) {
        int temp = startCol;
        startCol = endCol;
        endCol = temp;
    }
    // checking for horizontal ship overlap
    if (is_horizontal(startRow, endRow)) {
        for (int c = startCol; c <= endCol; c++) {
            if (pShips.squares[9 - startRow][c] != '.') {
                result = true;
                break;
            }
        }
    }
    // checking for vertical ship overlap (9- because of the weird axis labels)
    if (is_vertical(startCol, endCol)) {
        for (int r = 9 - startRow; r >= 9 - endRow; r--) {
            if (pShips.squares[r][startCol] != '.') {
                result = true;
                break;
            }
        }
    }
    return result;
}

// checks if ship is horizontal or vertical or overlapping another and correct length
bool is_valid_ship(int length, board pShips, int startRow, int startCol, int endRow, int endCol) {
    // printf("\n dimensions entered: %d %d %d %d", startRow, startCol, endRow, endCol);
    if (!((is_horizontal(startRow, endRow)) || (is_vertical(startCol, endCol))) || !(is_correct_length(length, startRow, startCol, endRow, endCol)) || is_ship_overlapping(pShips, startRow, startCol, endRow, endCol)) return false;
    else return true;
}

// checks if target is a new square
bool is_valid_target(board attackBoard, int targetRow, int targetCol) {
    if (attackBoard.squares[9 - targetRow][targetCol] == '.') return true;
    else return false;
}

// modifies attackBoard with X, pShips with X, and decreases the corresponding ships health based on the target if hit and returns true for a hit 
bool is_hit(board* attackBoard, board* pShips, ship* p_carrier, ship* p_battleship, ship* p_destroyer, 
    ship* p_submarine, ship* p_patrol_boat, int targetRow, int targetCol) {
    bool result = false;
  
    // decrease the corresponding ships health if hit
    if (targetRow >= p_carrier->startRow && targetRow <= p_carrier->endRow && targetCol >= p_carrier->startCol && targetCol <= p_carrier->endCol) {
        p_carrier->health--;
        result = true;
    }
    else if (targetRow >= p_battleship->startRow && targetRow <= p_battleship->endRow && targetCol >= p_battleship->startCol && targetCol <= p_battleship->endCol) {
        p_battleship->health--;
        result = true;
    }
    else if (targetRow >= p_destroyer->startRow && targetRow <= p_destroyer->endRow && targetCol >= p_destroyer->startCol && targetCol <= p_destroyer->endCol) {
        p_destroyer->health--;
        result = true;
    }
    else if (targetRow >= p_submarine->startRow && targetRow <= p_submarine->endRow && targetCol >= p_submarine->startCol && targetCol <= p_submarine->endCol) {
        p_submarine->health--;
        result = true;
    }
    else if (targetRow >= p_patrol_boat->startRow && targetRow <= p_patrol_boat->endRow && targetCol >= p_patrol_boat->startCol && targetCol <= p_patrol_boat->endCol) {
        p_patrol_boat->health--;
        result = true;
    }
    // add the x to the screen for both attack board and the person being attacked's ships if hit
    if (result) {
        attackBoard->squares[9 - targetRow][targetCol] = 'X';
        pShips->squares[9 - targetRow][targetCol] = 'X';
    }
    else {
        attackBoard->squares[9 - targetRow][targetCol] = '?';
    }
    return result;
}
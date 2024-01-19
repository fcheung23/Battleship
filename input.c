#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "board.h"
#include "input.h"
#include "ships.h"
#include "stages.h"

/**
 * Checks if input is valid format (last value on line if needed) and correct num of arguments entered
 * @param num_args_needed: int representing number of arguments needed
 * @param num_args_read: int representing number of arguments actually read
 * @param should_be_last_value_on_line: bool representing if input needs to be last value on line
 * @return bool representing if valid format, true; false if not
 */
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

/**
 * Gets a valid int from user and checks for valid format or else returns error code
 * @param isLastElementOnLine: bool representing if input needs to be last value on line
 * @return the int value entered if valid, else error -1
 */
int getValidInt(const bool isLastElementOnLine) {
    const int numArgsNeeded = 1;
    int numArgsRead;
    int num;
    numArgsRead = scanf(" %d", &num);
    if (isValidFormat(numArgsNeeded, numArgsRead, isLastElementOnLine)) {
        return num;
    } else {
        if (isLastElementOnLine) while (getchar() != '\n');
        return -1; 
    }
}

/**
 * Gets a valid int from user and checks for positive and valid format or else returns error code
 * @param isLastElementOnLine: bool representing if input needs to be last value on line
 * @return the int value entered if valid, else error -1
 */
int getPosInt(const bool isLastElementOnLine) {
    int num = getValidInt(isLastElementOnLine);
    if (num >= 0) {
        return num;
    }
    else {
        return -1;
    }
}

/**
 * Checks if coordinates of ship entered create a horizontally oriented ship
 * @param startRow: int representing row of the start hull
 * @param endRow: int representing row of the end hull
 * @return bool representing if coordinates create horizontally oriented ship; true if so and false if not
 */
bool is_horizontal(int startRow, int endRow) {
    if (startRow == endRow) return true;
    else return false;
}

/**
 * Checks if coordinates of ship entered create a vertically oriented ship
 * @param startCol: int representing column of the start hull
 * @param endCol: int representing column of the end hull
 * @return bool representing if coordinates create vertically oriented ship; true if so and false if not
 */
bool is_vertical(int startCol, int endCol) {
    if (startCol == endCol) return true;
    else return false;
}

/**
 * Checks if coordinates of ship entered create a ship with correct length based on specified value
 * @param length: int representing correct length for ship
 * @param startRow: int representing row of the start hull
 * @param startCol: int representing column of the start hull
 * @param endRow: int representing row of the end hull
 * @param endCol: int representing column of the end hull
 * @return bool representing if coordinates create ship with correct length; true if so and false if not
 */
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

/**
 * Checks if coordinates of ship entered create a ship that overlaps with another ship
 * @param pShips: board struct representing board containing the user's current ships
 * @param startRow: int representing row of the start hull
 * @param startCol: int representing column of the start hull
 * @param endRow: int representing row of the end hull
 * @param endCol: int representing column of the end hull
 * @return bool representing if coordinates create ship that overlaps another; true if so and false if not
 */
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
    // checking for vertical ship overlap 
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

/**
 * Checks if coordinates of ship entered create a ship that is "valid" (either horizontal or vertical orientation, 
 correct length, and no overlap)
 * @param length: int representing correct length for ship
 * @param pShips: board struct representing board containing the user's current ships
 * @param startRow: int representing row of the start hull
 * @param startCol: int representing column of the start hull
 * @param endRow: int representing row of the end hull
 * @param endCol: int representing column of the end hull
 * @return bool representing if coordinates create a "valid" ship; true if so and false if not
 */
bool is_valid_ship(int length, board pShips, int startRow, int startCol, int endRow, int endCol) {
    if (!((is_horizontal(startRow, endRow)) || (is_vertical(startCol, endCol))) || !(is_correct_length(length, startRow, startCol, endRow, endCol)) || is_ship_overlapping(pShips, startRow, startCol, endRow, endCol)) return false;
    else return true;
}

/**
 * Asks user and gets input for hull coordinates to create ships until input is valid
 * @param startRow: int pointer to startRow representing row of the start hull
 * @param startCol: int pointer to startCol representing column of the start hull
 * @param endRow: int pointer to endRow representing row of the end hull
 * @param endCol: int pointer to endCol representing column of the end hull
 * @modifies value of startRow, startCol, endRow, endCol
 * @return nothing
 */
void get_valid_hull(int* startRow, int* startCol, int* endRow, int* endCol) {
    *startRow = -2, *startCol = -2, *endRow = -2, *endCol = -2;
    while (*startRow < 0 || *startRow > 9 || *startCol < 0 || *startCol > 9) {
        printf("\nEnter hull start [row] [col]: ");
        *startRow = getPosInt(false);
        *startCol = getPosInt(true);
        if (*startRow < 0 || *startRow > 9 || *startCol < 0 || *startCol > 9) printf("\n (!) Invalid input for start, stay within board and enter integers. (!)");
    }
    while (*endRow < 0 || *endRow > 9 || *endCol < 0 || *endCol > 9) {
        printf("\nEnter hull end [row] [col]: ");
        *endRow = getPosInt(false);
        *endCol = getPosInt(true);
        if (*endRow < 0 || *endRow > 9 || *endCol < 0 || *endCol > 9) printf("\n (!) Invalid input for end, stay within board and enter integers. (!)");
    }
}

/**
 * Asks user and gets input for a target to attack until input is valid
 * @param targetRow: int pointer to targetRow representing row of the target
 * @param targetCol: int pointer to targetCol representing column of the target
 * @modifies value of targetRow, targetCol
 * @return nothing
 */
void get_valid_target(int* targetRow, int* targetCol) {
    *targetRow = -2, *targetCol = -2; 
    while (*targetRow < 0 || *targetRow > 9 || *targetCol < 0 || *targetCol > 9) {
        printf("\nEnter target [row] [col]: ");
        *targetRow = getPosInt(false);
        *targetCol = getPosInt(true);
        if (*targetRow < 0 || *targetRow > 9 || *targetCol < 0 || *targetCol > 9) printf("\n (!) Invalid input for target, stay within board and enter integers. (!)");
    }
}

/**
 * Checks if coordinates of target entered make a new target (cannot attack same spot)
 * @param attackBoard: board struct representing the board of ships the player attacks
 * @param targetRow: int representing row of the target
 * @param targetCol: int representing the column of the target
 * @return bool representing if target coordinates are new; true if so and false if not
 */
bool is_valid_target(board attackBoard, int targetRow, int targetCol) {
    if (attackBoard.squares[9 - targetRow][targetCol] == '.') return true;
    else return false;
}

// modifies attackBoard with X, pShips with X, and decreases the corresponding ships health based on the target if hit and returns true for a hit 
/**
 * Checks if coordinates of target entered are a hit (land on one of the enemy ships)
 * @param attackBoard: pointer to attackBoard representing board of ships the player attacks
 * @param pShips: pointer to pShips representing board containing the user's current ships
 * @param p_carrier: pointer to p_carrier representing the enemy carrier ship
 * @param p_battleship: pointer to p_battleship representing the enemy battleship ship
 * @param p_destroyer: pointer to p_destroyer representing the enemy destroyer ship
 * @param p_submarine: pointer to p_submarine representing the enemy submarine ship
 * @param p_patrol_boat: pointer to p_patrol_boat representing the enemy patrol boat ship
 * @param targetRow: int representing row of the target
 * @param targetCol: int representing the column of the target
 * @return bool representing if target coordinates make a hit; true if so and false if not
 * @modifies attackBoard, pShips, p_carrier, p_battleship, p_destroyer, p_submarine, p_patrol_boat
 */
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
    // add the 'x' to the screen for both attack board and the person being attacked's ships if hit and '?' for miss
    if (result) {
        attackBoard->squares[9 - targetRow][targetCol] = 'X';
        pShips->squares[9 - targetRow][targetCol] = 'X';
    }
    else {
        attackBoard->squares[9 - targetRow][targetCol] = '?';
    }
    return result;
}

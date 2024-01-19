#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"
#include "input.h"
#include "ships.h"
#include "stages.h"

ship create_ship(int health, int startRow, int startCol, int endRow, int endCol) {
    ship shipStruct;
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
    shipStruct.health = health;
    shipStruct.startRow = startRow;
    shipStruct.startCol = startCol;
    shipStruct.endRow = endRow;
    shipStruct.endCol = endCol;
    return shipStruct;
}   
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef SHIPS_H
#define SHIPS_H

typedef struct ship_struct{
    int health;
    int startRow;
    int startCol;
    int endRow;
    int endCol;
} ship;
ship create_ship(int health, int startRow, int startCol, int endRow, int endCol);

#endif
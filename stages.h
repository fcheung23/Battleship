#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"

#ifndef STAGES_H
#define STAGES_H 

void print_welcome_screen();
void print_tutorial_screen();
void p1_place_carrier(board* p1Ships, ship* p1_carrier); 
void p1_place_battleship(board* p1Ships, ship* p1_battleship);
void p1_place_destroyer(board* p1Ships, ship* p1_destroyer);
void p1_place_submarine(board* p1Ships, ship* p1_submarine);
void p1_place_patrol_boat(board* p1Ships, ship* p1_patrol_boat);
void p1_ship_placement(board* p1Ships, ship* p1_carrier, ship* p1_battleship, ship* p1_destroyer, ship* p1_submarine, ship* p1_patrol_boat);
void p2_place_carrier(board* p2Ships, ship* p2_carrier);
void p2_place_battleship(board* p2Ships, ship* p2_battleship);
void p2_place_destroyer(board* p2Ships, ship* p2_destroyer);
void p2_place_submarine(board* p2Ships, ship* p2_submarine);
void p2_place_patrol_boat(board* p2Ships, ship* p2_patrol_boat);
void p2_ship_placement(board* p2Ships, ship* p2_carrier, ship* p2_battleship, ship* p2_destroyer, ship* p2_submarine, ship* p2_patrol_boat);
void print_ships(board pShips, ship p_carrier, ship p_battleship, ship p_destroyer, ship p_submarine, ship p_patrol_boat);
void print_hit_screen(board attackBoard, ship p_carrier, ship p_battleship, ship p_destroyer, ship p_submarine, ship p_patrol_boat);
void print_miss_screen(board attackBoard, ship p_carrier, ship p_battleship, ship p_destroyer, ship p_submarine, ship p_patrol_boat);
void p1_shot(board* p1Attack, board* p2Ships, ship* p2_carrier, ship* p2_battleship, ship* p2_destroyer, ship* p2_submarine, ship* p2_patrol_boat);
void p2_shot(board* p2Attack, board* p1Ships, ship* p1_carrier, ship* p1_battleship, ship* p1_destroyer, ship* p1_submarine, ship* p1_patrol_boat);
bool check_win(ship p1_carrier, ship p1_battleship, ship p1_destroyer, ship p1_submarine, ship p1_patrol_boat, 
    ship p2_carrier, ship p2_battleship, ship p2_destroyer, ship p2_submarine, ship p2_patrol_boat);

void play_game();

#endif
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"
#include "input.h"
#include "ships.h"
#include "stages.h"

// prints welcome screen
void print_welcome_screen() {
    printf("╔═════<[ - ][ | ][ | ]>   BATTLESHIP   <[ - ][ - ][ | ]>═════╗\n\n");
    board welcomeBoard = create_board();
    welcomeBoard.squares[9-8][2] = '^';
    welcomeBoard.squares[9-7][2] = 'X';
    welcomeBoard.squares[9-6][2] = '|';
    welcomeBoard.squares[9-5][2] = 'v';
    welcomeBoard.squares[9-7][7] = '~';
    welcomeBoard.squares[9-4][1] = '~';
    welcomeBoard.squares[9-4][4] = '<';
    welcomeBoard.squares[9-4][5] = '-';
    welcomeBoard.squares[9-4][6] = '-';
    welcomeBoard.squares[9-4][7] = '>';
    welcomeBoard.squares[9-1][0] = '<';
    welcomeBoard.squares[9-1][1] = '-';
    welcomeBoard.squares[9-1][2] = '-';
    welcomeBoard.squares[9-1][3] = 'X';
    welcomeBoard.squares[9-1][4] = '>';
    welcomeBoard.squares[9-1][7] = '~';
    print_board(welcomeBoard);
    printf("\n\n╙─────────────────────────────────────────────────────────────╜");
    printf("\n\n|                      (!) Zoom Until Bars (|) Are At the Edges of your Screen (!)                     |");
    printf("\n\n<[ - ][ - ][ | ]>   Press [Any Letter] + [Enter] to Start   <[ | ][ | ][ - ]>\n\n");
    delete_board(&welcomeBoard);    
}

// prints tutorial screen
void print_tutorial_screen() {
    printf("╔═════<[ - ][ | ][ | ]>   BATTLESHIP | Tutorial   <[ - ][ - ][ | ]>═════╗\n\n");
    board tutorialBoard = create_board();
    tutorialBoard.squares[9-8][1] = '^';
    tutorialBoard.squares[9-7][1] = '|';
    tutorialBoard.squares[9-6][1] = '|';
    tutorialBoard.squares[9-5][1] = 'V';

    tutorialBoard.squares[9-8][5] = '<';
    tutorialBoard.squares[9-8][6] = '-';
    tutorialBoard.squares[9-8][7] = '>';

    tutorialBoard.squares[9-3][1] = '<';
    tutorialBoard.squares[9-3][2] = '-';
    tutorialBoard.squares[9-3][3] = '>';

    tutorialBoard.squares[9-6][6] = '^';
    tutorialBoard.squares[9-5][6] = '|';
    tutorialBoard.squares[9-4][6] = '|';
    tutorialBoard.squares[9-3][6] = '|';
    tutorialBoard.squares[9-2][6] = 'v';

    tutorialBoard.squares[9-0][4] = '<';
    tutorialBoard.squares[9-0][5] = '>';
    print_board(tutorialBoard);
    printf("\n\n╙───────────────────────────────────────────────────────────────────────╜");
    printf("\n\n    1) Strategically place your ships to avoid enemy fire.");
    printf("\n    2) During rounds, each player gets one shot, with a “X” indicating a hit and a “?” for a miss.");
    printf("\n    3) Sink enemy ships before they sink yours!");
    printf("\n    (!) Pay attention when asked to pass to players, don't give away info! (!)");
    printf("\n  <SHIPS> (HP \u2665): Carrier (5 \u2665) Battleship (4 \u2665) Destroyer (3 \u2665) Submarine (3 \u2665) Patrol Boat (2 \u2665)");
    printf("\n\n<[ - ][ - ][ | ]>   Press [Any Letter] + [Enter] to Continue   <[ | ][ | ][ - ]>\n\n");
    delete_board(&tutorialBoard);    
}

// ask player 1 to place carrier (5), modifies p1Ships board and p1_carrier ship
void p1_place_carrier(board* p1Ships, ship* p1_carrier) {
    int startRow = -2, startCol = -2, endRow = -2, endCol = -2;
    bool shipPlaced = false;
    printf("╔═════<[ - ][ | ][ | ]>   BATTLESHIP   <[ - ][ - ][ | ]>═════╗\n\n");
    print_board(*p1Ships);
    printf("\n\n    Place Carrier (5 \u2665) <[][][][][]>");
    printf("\n\n╙─────────────────────────────────────────────────────────────╜");
    printf("\n\n<[ - ][ - ][ | ]>   Player 1 Ship Placement   <[ | ][ | ][ - ]>");
    do {    
        get_valid_hull(&startRow, & startCol, &endRow, &endCol); 
        shipPlaced = is_valid_ship(5, *p1Ships, startRow, startCol, endRow, endCol);
        if (!shipPlaced) { printf("\n (!) Invalid ship, use open squares, only horizontal/vertical orientation, and correct length. (!)"); }
    } while (!shipPlaced);
    *p1_carrier = create_ship(5, startRow, startCol, endRow, endCol);
    draw_ship(p1Ships, *p1_carrier); 
}

// ask player 1 to place battleship (4), modifies p1Ships board and p1_battleship ship
void p1_place_battleship(board* p1Ships, ship* p1_battleship) {
    int startRow = -2, startCol = -2, endRow = -2, endCol = -2;
    bool shipPlaced = false;
    printf("\n\n╔═════<[ - ][ | ][ | ]>   BATTLESHIP   <[ - ][ - ][ | ]>═════╗\n\n");
    print_board(*p1Ships);
    printf("\n\n    Place Battleship (4 \u2665) <[][][][]>");
    printf("\n\n╙─────────────────────────────────────────────────────────────╜");
    printf("\n\n<[ - ][ - ][ | ]>   Player 1 Ship Placement   <[ | ][ | ][ - ]>");
    do {    
        get_valid_hull(&startRow, & startCol, &endRow, &endCol);
        shipPlaced = is_valid_ship(4, *p1Ships, startRow, startCol, endRow, endCol);
        if (!shipPlaced) { printf("\n (!) Invalid ship, use open squares, only horizontal/vertical orientation, and correct length. (!)"); }
    } while (!shipPlaced);
    *p1_battleship = create_ship(4, startRow, startCol, endRow, endCol);
    draw_ship(p1Ships, *p1_battleship); 
}

// ask player 1 to place destroyer (3), modifies p1Ships board and p1_destroyer ship
void p1_place_destroyer(board* p1Ships, ship* p1_destroyer) {
    int startRow = -2, startCol = -2, endRow = -2, endCol = -2;
    bool shipPlaced = false;
    printf("\n\n╔═════<[ - ][ | ][ | ]>   BATTLESHIP   <[ - ][ - ][ | ]>═════╗\n\n");
    print_board(*p1Ships);
    printf("\n\n    Place Destroyer (3 \u2665) <[][][]>");
    printf("\n\n╙─────────────────────────────────────────────────────────────╜");
    printf("\n\n<[ - ][ - ][ | ]>   Player 1 Ship Placement   <[ | ][ | ][ - ]>");
    do {    
        get_valid_hull(&startRow, & startCol, &endRow, &endCol);  
        shipPlaced = is_valid_ship(3, *p1Ships, startRow, startCol, endRow, endCol);
        if (!shipPlaced) { printf("\n (!) Invalid ship, use open squares, only horizontal/vertical orientation, and correct length. (!)"); }
    } while (!shipPlaced);
    *p1_destroyer = create_ship(3, startRow, startCol, endRow, endCol);
    draw_ship(p1Ships, *p1_destroyer); 
}

// ask player 1 to place submarine (3), modifies p1Ships board and p1_submarine ship
void p1_place_submarine(board* p1Ships, ship* p1_submarine) {
    int startRow = -2, startCol = -2, endRow = -2, endCol = -2;
    bool shipPlaced = false;
    printf("\n\n╔═════<[ - ][ | ][ | ]>   BATTLESHIP   <[ - ][ - ][ | ]>═════╗\n\n");
    print_board(*p1Ships);
    printf("\n\n    Place Submarine (3 \u2665) <[][][]>");
    printf("\n\n╙─────────────────────────────────────────────────────────────╜");
    printf("\n\n<[ - ][ - ][ | ]>   Player 1 Ship Placement   <[ | ][ | ][ - ]>");
    do {    
        get_valid_hull(&startRow, & startCol, &endRow, &endCol); 
        shipPlaced = is_valid_ship(3, *p1Ships, startRow, startCol, endRow, endCol);
        if (!shipPlaced) { printf("\n (!) Invalid ship, use open squares, only horizontal/vertical orientation, and correct length. (!)"); }
    } while (!shipPlaced);
    *p1_submarine = create_ship(3, startRow, startCol, endRow, endCol);
    draw_ship(p1Ships, *p1_submarine); 
}

// ask player 1 to place patrol boat (2), modifies p1Ships board and p1_patrol_boat ship
void p1_place_patrol_boat(board* p1Ships, ship* p1_patrol_boat) {
    int startRow = -2, startCol = -2, endRow = -2, endCol = -2;
    bool shipPlaced = false;
    printf("\n\n╔═════<[ - ][ | ][ | ]>   BATTLESHIP   <[ - ][ - ][ | ]>═════╗\n\n");
    print_board(*p1Ships);
    printf("\n\n    Place Patrol Boat (2 \u2665) <[][]>");
    printf("\n\n╙─────────────────────────────────────────────────────────────╜");
    printf("\n\n<[ - ][ - ][ | ]>   Player 1 Ship Placement   <[ | ][ | ][ - ]>");
    do {    
        get_valid_hull(&startRow, & startCol, &endRow, &endCol);
        shipPlaced = is_valid_ship(2, *p1Ships, startRow, startCol, endRow, endCol);
        if (!shipPlaced) { printf("\n (!) Invalid ship, use open squares, only horizontal/vertical orientation, and correct length. (!)"); }
    } while (!shipPlaced);
    *p1_patrol_boat = create_ship(2, startRow, startCol, endRow, endCol);
    draw_ship(p1Ships, *p1_patrol_boat); 
}

// ask player 1 to place all ships
void p1_ship_placement(board* p1Ships, ship* p1_carrier, ship* p1_battleship, ship* p1_destroyer, ship* p1_submarine, ship* p1_patrol_boat) {
    p1_place_carrier(p1Ships, p1_carrier);
    p1_place_battleship(p1Ships, p1_battleship);
    p1_place_destroyer(p1Ships, p1_destroyer);
    p1_place_submarine(p1Ships, p1_submarine);
    p1_place_patrol_boat(p1Ships, p1_patrol_boat); 
}

// ask player 2 to place carrier (5), modifies p2Ships board and p2_carrier ship
void p2_place_carrier(board* p2Ships, ship* p2_carrier) {
    int startRow = -2, startCol = -2, endRow = -2, endCol = -2;
    bool shipPlaced = false;
    printf("\n\n╔═════<[ - ][ | ][ | ]>   BATTLESHIP   <[ - ][ - ][ | ]>═════╗\n\n");
    print_board(*p2Ships);
    printf("\n\n    Place Carrier (5 \u2665) <[][][][][]>");
    printf("\n\n╙─────────────────────────────────────────────────────────────╜");
    printf("\n\n<[ - ][ - ][ | ]>   Player 2 Ship Placement   <[ | ][ | ][ - ]>");
    do {    
        get_valid_hull(&startRow, & startCol, &endRow, &endCol); 
        shipPlaced = is_valid_ship(5, *p2Ships, startRow, startCol, endRow, endCol);
        if (!shipPlaced) { printf("\n (!) Invalid ship, use open squares, only horizontal/vertical orientation, and correct length. (!)"); }
    } while (!shipPlaced);
    *p2_carrier = create_ship(5, startRow, startCol, endRow, endCol);
    draw_ship(p2Ships, *p2_carrier); 
}

// ask player 2 to place battleship (4), modifies p2Ships board and p2_battleship ship
void p2_place_battleship(board* p2Ships, ship* p2_battleship) {
    int startRow = -2, startCol = -2, endRow = -2, endCol = -2;
    bool shipPlaced = false;
    printf("\n\n╔═════<[ - ][ | ][ | ]>   BATTLESHIP   <[ - ][ - ][ | ]>═════╗\n\n");
    print_board(*p2Ships);
    printf("\n\n    Place Battleship (4 \u2665) <[][][][]>");
    printf("\n\n╙─────────────────────────────────────────────────────────────╜");
    printf("\n\n<[ - ][ - ][ | ]>   Player 2 Ship Placement   <[ | ][ | ][ - ]>");
    do {    
        get_valid_hull(&startRow, & startCol, &endRow, &endCol);
        shipPlaced = is_valid_ship(4, *p2Ships, startRow, startCol, endRow, endCol);
        if (!shipPlaced) { printf("\n (!) Invalid ship, use open squares, only horizontal/vertical orientation, and correct length. (!)"); }
    } while (!shipPlaced);
    *p2_battleship = create_ship(4, startRow, startCol, endRow, endCol);
    draw_ship(p2Ships, *p2_battleship); 
}

// ask player 2 to place destroyer (3), modifies p2Ships board and p2_destroyer ship
void p2_place_destroyer(board* p2Ships, ship* p2_destroyer) {
    int startRow = -2, startCol = -2, endRow = -2, endCol = -2;
    bool shipPlaced = false;
    printf("\n\n╔═════<[ - ][ | ][ | ]>   BATTLESHIP   <[ - ][ - ][ | ]>═════╗\n\n");
    print_board(*p2Ships);
    printf("\n\n    Place Destroyer (3 \u2665) <[][][]>");
    printf("\n\n╙─────────────────────────────────────────────────────────────╜");
    printf("\n\n<[ - ][ - ][ | ]>   Player 2 Ship Placement   <[ | ][ | ][ - ]>");
    do {    
        get_valid_hull(&startRow, & startCol, &endRow, &endCol);  
        shipPlaced = is_valid_ship(3, *p2Ships, startRow, startCol, endRow, endCol);
        if (!shipPlaced) { printf("\n (!) Invalid ship, use open squares, only horizontal/vertical orientation, and correct length. (!)"); }
    } while (!shipPlaced);
    *p2_destroyer = create_ship(3, startRow, startCol, endRow, endCol);
    draw_ship(p2Ships, *p2_destroyer); 
}

// ask player 2 to place submarine (3), modifies p2Ships board and p2_submarine ship
void p2_place_submarine(board* p2Ships, ship* p2_submarine) {
    int startRow = -2, startCol = -2, endRow = -2, endCol = -2;
    bool shipPlaced = false;
    printf("\n\n╔═════<[ - ][ | ][ | ]>   BATTLESHIP   <[ - ][ - ][ | ]>═════╗\n\n");
    print_board(*p2Ships);
    printf("\n\n    Place Submarine (3 \u2665) <[][][]>");
    printf("\n\n╙─────────────────────────────────────────────────────────────╜");
    printf("\n\n<[ - ][ - ][ | ]>   Player 2 Ship Placement   <[ | ][ | ][ - ]>");
    do {    
        get_valid_hull(&startRow, & startCol, &endRow, &endCol); 
        shipPlaced = is_valid_ship(3, *p2Ships, startRow, startCol, endRow, endCol);
        if (!shipPlaced) { printf("\n (!) Invalid ship, use open squares, only horizontal/vertical orientation, and correct length. (!)"); }
    } while (!shipPlaced);
    *p2_submarine = create_ship(3, startRow, startCol, endRow, endCol);
    draw_ship(p2Ships, *p2_submarine); 
}

// ask player 2 to place patrol boat (2), modifies p2Ships board and p2_patrol_boat ship
void p2_place_patrol_boat(board* p2Ships, ship* p2_patrol_boat) {   
    int startRow = -2, startCol = -2, endRow = -2, endCol = -2;
    bool shipPlaced = false;
    printf("\n\n╔═════<[ - ][ | ][ | ]>   BATTLESHIP   <[ - ][ - ][ | ]>═════╗\n\n");
    print_board(*p2Ships);
    printf("\n\n    Place Patrol Boat (2 \u2665) <[][]>");
    printf("\n\n╙─────────────────────────────────────────────────────────────╜");
    printf("\n\n<[ - ][ - ][ | ]>   Player 2 Ship Placement   <[ | ][ | ][ - ]>");
    do {    
        get_valid_hull(&startRow, & startCol, &endRow, &endCol);   
        shipPlaced = is_valid_ship(2, *p2Ships, startRow, startCol, endRow, endCol);
        if (!shipPlaced) { printf("\n (!) Invalid ship, use open squares, only horizontal/vertical orientation, and correct length. (!)"); }
    } while (!shipPlaced);
    *p2_patrol_boat = create_ship(2, startRow, startCol, endRow, endCol);
    draw_ship(p2Ships, *p2_patrol_boat); 
}

// ask player 2 to place all ships
void p2_ship_placement(board* p2Ships, ship* p2_carrier, ship* p2_battleship, ship* p2_destroyer, ship* p2_submarine, ship* p2_patrol_boat) {
    p2_place_carrier(p2Ships, p2_carrier);
    p2_place_battleship(p2Ships, p2_battleship);
    p2_place_destroyer(p2Ships, p2_destroyer);
    p2_place_submarine(p2Ships, p2_submarine);
    p2_place_patrol_boat(p2Ships, p2_patrol_boat); 
}

// displays the player's selection of ship locations and health
void print_ships(board pShips, ship p_carrier, ship p_battleship, ship p_destroyer, ship p_submarine, ship p_patrol_boat) {
    printf("\n\n╔═════<[ - ][ | ][ | ]>   BATTLESHIP   <[ - ][ - ][ | ]>═════╗\n\n");
    print_board(pShips);
    printf("\n\n    ^ ^ ^   Your Ships and Health   ^ ^ ^");
    printf("\n  Carrier (%d/5 \u2665) Battleship (%d/4 \u2665) Destroyer (%d/3 \u2665) Submarine (%d/3 \u2665) Patrol Boat (%d/2 \u2665)", 
    p_carrier.health, p_battleship.health, p_destroyer.health, p_submarine.health, p_patrol_boat.health);
    printf("\n\n╙─────────────────────────────────────────────────────────────╜");
    printf("\n\n<[ - ][ - ][ | ]>   Press [Any Letter] + [Enter] to Continue   <[ | ][ | ][ - ]>\n\n");
}

// prints hit screen and announces sinking if necessary
void print_hit_screen(board attackBoard, ship p_carrier, ship p_battleship, ship p_destroyer, ship p_submarine, ship p_patrol_boat) {
    printf("\n\n╔═════<[ - ][ | ][ | ]>   BATTLESHIP   <[ - ][ - ][ | ]>═════╗\n\n");
    print_board(attackBoard);
    printf("\n\n    (!) Hit! <[X]> (!)");
    printf("\n    Ships Sucessfully Sunk: \n");
    if (p_carrier.health == 0) printf(" Carrier (5->0 \u2665) ");
    if (p_battleship.health == 0) printf(" Battleship (4->0 \u2665) ");
    if (p_destroyer.health == 0) printf(" Destroyer (3->0 \u2665) ") ;
    if (p_submarine.health == 0) printf(" Submarine (3->0 \u2665) ");
    if (p_patrol_boat.health == 0) printf(" Patrol Boat (2->0 \u2665) ");
    printf("\n\n╙─────────────────────────────────────────────────────────────╜");
}

// prints miss screen
void print_miss_screen(board attackBoard, ship p_carrier, ship p_battleship, ship p_destroyer, ship p_submarine, ship p_patrol_boat) {
    printf("\n\n╔═════<[ - ][ | ][ | ]>   BATTLESHIP   <[ - ][ - ][ | ]>═════╗\n\n");
    print_board(attackBoard);
    printf("\n\n    (!) Miss! (!)");
    printf("\n    Ships Sucessfully Sunk: ");
    if (p_carrier.health == 0) printf("Carrier (5->0 \u2665) ");
    if (p_battleship.health == 0) printf("Battleship (4->0 \u2665) ");
    if (p_destroyer.health == 0) printf("Destroyer (3->0 \u2665) ") ;
    if (p_submarine.health == 0) printf("Submarine (3->0 \u2665) ");
    if (p_patrol_boat.health == 0) printf("Patrol Boat (2->0 \u2665) ");
    printf("\n\n╙─────────────────────────────────────────────────────────────╜");
}

void p1_shot(board* p1Attack, board* p2Ships, ship* p2_carrier, ship* p2_battleship, ship* p2_destroyer, ship* p2_submarine, ship* p2_patrol_boat) {
    int targetRow = -2, targetCol = -2;
    bool validTarget = false;
    printf("\n\n╔═════<[ - ][ | ][ | ]>   BATTLESHIP   <[ - ][ - ][ | ]>═════╗\n\n");
    print_board(*p1Attack);
    printf("\n\n    ^ ^ ^   P1's Previous Shots   ^ ^ ^");
    printf("\n\n╙─────────────────────────────────────────────────────────────╜");
    printf("\n\n<[ - ][ - ][ | ]>   Player 1 Shot   <[ | ][ | ][ - ]>");
    do {    
        get_valid_target(&targetRow, &targetCol);
        validTarget = is_valid_target(*p1Attack, targetRow, targetCol);
        if (!validTarget) { printf("\n (!) Invalid target, choose new squares only. (!)"); }
    } while (!validTarget);
    if (is_hit(p1Attack, p2Ships, p2_carrier, p2_battleship, p2_destroyer, p2_submarine, p2_patrol_boat, targetRow, targetCol)) {
        print_hit_screen(*p1Attack, *p2_carrier, *p2_battleship, *p2_destroyer, *p2_submarine, *p2_patrol_boat);
    }
    else print_miss_screen(*p1Attack, *p2_carrier, *p2_battleship, *p2_destroyer, *p2_submarine, *p2_patrol_boat);
    printf("\n\n<[ - ][ - ][ | ]>   Player 1 Shot | Press [Any Letter] + [Enter] & PASS to Player 2  <[ | ][ | ][ - ]>");
}

void p2_shot(board* p2Attack, board* p1Ships, ship* p1_carrier, ship* p1_battleship, ship* p1_destroyer, ship* p1_submarine, ship* p1_patrol_boat) {
    int targetRow = -2, targetCol = -2;
    bool validTarget = false;
    printf("\n\n╔═════<[ - ][ | ][ | ]>   BATTLESHIP   <[ - ][ - ][ | ]>═════╗\n\n");
    print_board(*p2Attack);
    printf("\n\n    ^ ^ ^   P2's Previous Shots   ^ ^ ^");
    printf("\n\n╙─────────────────────────────────────────────────────────────╜");
    printf("\n\n<[ - ][ - ][ | ]>   Player 2 Shot   <[ | ][ | ][ - ]>");
    do {    
        get_valid_target(&targetRow, &targetCol);
        validTarget = is_valid_target(*p2Attack, targetRow, targetCol);
        if (!validTarget) { printf("\n (!) Invalid target, choose new squares only. (!)"); }
    } while (!validTarget);
    if (is_hit(p2Attack, p1Ships, p1_carrier, p1_battleship, p1_destroyer, p1_submarine, p1_patrol_boat, targetRow, targetCol)) {
        print_hit_screen(*p2Attack, *p1_carrier, *p1_battleship, *p1_destroyer, *p1_submarine, *p1_patrol_boat);
    }
    else print_miss_screen(*p2Attack, *p1_carrier, *p1_battleship, *p1_destroyer, *p1_submarine, *p1_patrol_boat);
    printf("\n\n<[ - ][ - ][ | ]>   Player 2 Shot | Press [Any Letter] + [Enter] & PASS to Player 1  <[ | ][ | ][ - ]>");
}

void print_p1_win_screen() {
    printf("\n\n╔═════<[ - ][ | ][ | ]>   BATTLESHIP   <[ - ][ - ][ | ]>═════╗\n\n");
    board winBoard = create_board();
    winBoard.squares[9 - 6][1] = '*';
    winBoard.squares[9 - 6][2] = '*';
    winBoard.squares[9 - 6][3] = '*';
    winBoard.squares[9 - 6][4] = '*';
    winBoard.squares[9 - 6][5] = '*';
    winBoard.squares[9 - 6][6] = '*';
    winBoard.squares[9 - 6][7] = '*';
    winBoard.squares[9 - 5][1] = '*';
    winBoard.squares[9 - 4][1] = '*';
    winBoard.squares[9 - 5][3] = 'P';  
    winBoard.squares[9 - 5][4] = '1';
    winBoard.squares[9 - 4][2] = 'W';
    winBoard.squares[9 - 4][3] = 'I';  
    winBoard.squares[9 - 4][4] = 'N';
    winBoard.squares[9 - 4][5] = 'S';
    winBoard.squares[9 - 4][6] = '!';  
    winBoard.squares[9 - 5][7] = '*';
    winBoard.squares[9 - 4][7] = '*';
    winBoard.squares[9 - 3][1] = '*';
    winBoard.squares[9 - 3][2] = '*';
    winBoard.squares[9 - 3][3] = '*';
    winBoard.squares[9 - 3][4] = '*';
    winBoard.squares[9 - 3][5] = '*';
    winBoard.squares[9 - 3][6] = '*';
    winBoard.squares[9 - 3][7] = '*';
    print_board(winBoard);
    printf("\n\n╙─────────────────────────────────────────────────────────────╜");
    printf("\n\n<[ - ][ - ][ | ]>   P 1   W I N S !   <[ | ][ | ][ - ]>\n\n");
    delete_board(&winBoard);    
}

void print_p2_win_screen() {
    printf("\n\n╔═════<[ - ][ | ][ | ]>   BATTLESHIP   <[ - ][ - ][ | ]>═════╗\n\n");
    board winBoard = create_board();
    winBoard.squares[9 - 6][1] = '*';
    winBoard.squares[9 - 6][2] = '*';
    winBoard.squares[9 - 6][3] = '*';
    winBoard.squares[9 - 6][4] = '*';
    winBoard.squares[9 - 6][5] = '*';
    winBoard.squares[9 - 6][6] = '*';
    winBoard.squares[9 - 6][7] = '*';
    winBoard.squares[9 - 5][1] = '*';
    winBoard.squares[9 - 4][1] = '*';
    winBoard.squares[9 - 5][3] = 'P';  
    winBoard.squares[9 - 5][4] = '2';
    winBoard.squares[9 - 4][2] = 'W';
    winBoard.squares[9 - 4][3] = 'I';  
    winBoard.squares[9 - 4][4] = 'N';
    winBoard.squares[9 - 4][5] = 'S';
    winBoard.squares[9 - 4][6] = '!';  
    winBoard.squares[9 - 5][7] = '*';
    winBoard.squares[9 - 4][7] = '*';
    winBoard.squares[9 - 3][1] = '*';
    winBoard.squares[9 - 3][2] = '*';
    winBoard.squares[9 - 3][3] = '*';
    winBoard.squares[9 - 3][4] = '*';
    winBoard.squares[9 - 3][5] = '*';
    winBoard.squares[9 - 3][6] = '*';
    winBoard.squares[9 - 3][7] = '*';
    print_board(winBoard);
    printf("\n\n╙─────────────────────────────────────────────────────────────╜");
    printf("\n\n<[ - ][ - ][ | ]>   P 2   W I N S !   <[ | ][ | ][ - ]>\n\n");
    delete_board(&winBoard);   
}

// checks win and responds accordingly
bool check_win(ship p1_carrier, ship p1_battleship, ship p1_destroyer, ship p1_submarine, ship p1_patrol_boat, 
    ship p2_carrier, ship p2_battleship, ship p2_destroyer, ship p2_submarine, ship p2_patrol_boat) {
    if (p1_carrier.health == 0 && p1_battleship.health == 0 && p1_destroyer.health == 0 && p1_submarine.health == 0 && p1_patrol_boat.health == 0) {
        print_p2_win_screen();
        return true;
    }
    else if (p2_carrier.health == 0 && p2_battleship.health == 0 && p2_destroyer.health == 0 && p2_submarine.health == 0 && p2_patrol_boat.health == 0) {
        print_p1_win_screen();
        return true;
    }
    else return false;
}

void play_game() {

    // for user progression
    char c;
    int num_args_read = 0;

    // create player 1's board of ships
    board p1Ships = create_board();

    // declare player 1's ships
    ship p1_carrier, p1_battleship, p1_destroyer, p1_submarine, p1_patrol_boat; 
    
    // define the ships and place them
    p1_ship_placement(&p1Ships, &p1_carrier, &p1_battleship, &p1_destroyer, &p1_submarine, &p1_patrol_boat);

    // display player 1's ships
    print_ships(p1Ships, p1_carrier, p1_battleship, p1_destroyer, p1_submarine, p1_patrol_boat);

    // create player 2's board of ships
    board p2Ships = create_board();

    // declare player 2's ships
    ship p2_carrier, p2_battleship, p2_destroyer, p2_submarine, p2_patrol_boat; 

    // take continue any key
    num_args_read = scanf("%c", &c);
    // define the ships and place them
    if (num_args_read >= 1) p2_ship_placement(&p2Ships, &p2_carrier, &p2_battleship, &p2_destroyer, &p2_submarine, &p2_patrol_boat);

   // display player 2's ships
    print_ships(p2Ships, p2_carrier, p2_battleship, p2_destroyer, p2_submarine, p2_patrol_boat);

    // create player 1 and player 2's attack boards (to track shots)
    board p1Attack = create_board();
    board p2Attack = create_board();

    // take continue any key
    num_args_read = scanf("%c", &c);
    // clear input buffer 
    while (getchar() != '\n');

    // do turns
    if (num_args_read >= 1) {
        
        num_args_read = 0;

        // adjust shot tracking for p1 and its effect on p2's ships
        p1_shot(&p1Attack, &p2Ships, &p2_carrier, &p2_battleship, &p2_destroyer, &p2_submarine, &p2_patrol_boat); 

        // continue while game not over
        while (1) {
            
            num_args_read = scanf("%c", &c);
            while (getchar() != '\n');
            if (num_args_read >= 1) print_ships(p2Ships, p2_carrier, p2_battleship, p2_destroyer, p2_submarine, p2_patrol_boat);
            num_args_read = 0;
            if (check_win(p1_carrier, p1_battleship, p1_destroyer, p1_submarine, p1_patrol_boat, 
                p2_carrier, p2_battleship, p2_destroyer, p2_submarine, p2_patrol_boat)) break; 
            
            num_args_read = scanf("%c", &c);
            while (getchar() != '\n');
            if (num_args_read >= 1) p2_shot(&p2Attack, &p1Ships, &p1_carrier, &p1_battleship, &p1_destroyer, &p1_submarine, &p1_patrol_boat); 
            num_args_read = 0;

            num_args_read = scanf("%c", &c);
            while (getchar() != '\n');
            if (num_args_read >= 1) print_ships(p1Ships, p1_carrier, p1_battleship, p1_destroyer, p1_submarine, p1_patrol_boat);   
            num_args_read = 0;
            if (check_win(p1_carrier, p1_battleship, p1_destroyer, p1_submarine, p1_patrol_boat, 
                p2_carrier, p2_battleship, p2_destroyer, p2_submarine, p2_patrol_boat)) break; 

            num_args_read = scanf("%c", &c);
            while (getchar() != '\n');
            if (num_args_read >= 1) p1_shot(&p1Attack, &p2Ships, &p2_carrier, &p2_battleship, &p2_destroyer, &p2_submarine, &p2_patrol_boat); 
            num_args_read = 0;
        
        }
    }

    // free all the boards
    delete_board(&p1Ships);
    delete_board(&p2Ships);
    delete_board(&p1Attack);
    delete_board(&p2Attack);

}
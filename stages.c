#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"
#include "input.h"
#include "ships.h"
#include "stages.h"

/**
 * Prints the welcome screen with graphic and resize instructions
 * @param none
 * @return nothing
 */
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

/**
 * Prints the tutorial screen with example board and instructions
 * @param none
 * @return nothing
 */
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

/**
 * Displays screen for P1 placing their carrier and places it (initializes the carrier and draws it onto the board)
 * @param p1Ships: pointer to the board struct representing player 1's board of ships
 * @param p1_carrier: pointer to the ship struct representing player 1's carrier ship
 * @return nothing
 * @modifies p1Ships, p1_carrier
 */
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

/**
 * Displays screen for P1 placing their battleship and places it (initializes the battleship and draws it onto the board)
 * @param p1Ships: pointer to the board struct representing player 1's board of ships
 * @param p1_battleship: pointer to the ship struct representing player 1's battleship ship
 * @return nothing
 * @modifies p1Ships, p1_battleship
 */
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

/**
 * Displays screen for P1 placing their destroyer and places it (initializes the destroyer and draws it onto the board)
 * @param p1Ships: pointer to the board struct representing player 1's board of ships
 * @param p1_destroyer: pointer to the ship struct representing player 1's destroyer ship
 * @return nothing
 * @modifies p1Ships, p1_destroyer
 */
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

/**
 * Displays screen for P1 placing their submarine and places it (initializes the submarine and draws it onto the board)
 * @param p1Ships: pointer to the board struct representing player 1's board of ships
 * @param p1_submarine: pointer to the ship struct representing player 1's submarine ship
 * @return nothing
 * @modifies p1Ships, p1_submarine
 */
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

/**
 * Displays screen for P1 placing their patrol boat and places it (initializes the patrol boat and draws it onto the board)
 * @param p1Ships: pointer to the board struct representing player 1's board of ships
 * @param p1_patrol_boat: pointer to the ship struct representing player 1's patrol boat ship
 * @return nothing
 * @modifies p1Ships, p1_patrol_boat
 */
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

/**
 * Places all of p1 ships (individually prompts user to place each ship, initializing and drawing them onto the board)
 * @param p1Ships: pointer to the board struct representing player 1's board of ships
 * @param p1_carrier: pointer to the ship struct representing player 1's carrier ship
 * @param p1_battleship: pointer to the ship struct representing player 1's battleship ship
 * @param p1_destroyer: pointer to the ship struct representing player 1's destroyer ship
 * @param p1_submarine: pointer to the ship struct representing player 1's submarine ship
 * @param p1_patrol_boat: pointer to the ship struct representing player 1's boat ship
 * @return nothing
 * @modifies p1Ships, p1_carrier, p1_battleship, p1_destroyer, p1_submarine, p1_patrol_boat
 */
void p1_ship_placement(board* p1Ships, ship* p1_carrier, ship* p1_battleship, ship* p1_destroyer, ship* p1_submarine, ship* p1_patrol_boat) {
    p1_place_carrier(p1Ships, p1_carrier);
    p1_place_battleship(p1Ships, p1_battleship);
    p1_place_destroyer(p1Ships, p1_destroyer);
    p1_place_submarine(p1Ships, p1_submarine);
    p1_place_patrol_boat(p1Ships, p1_patrol_boat); 
}

/**
 * Displays screen for P2 placing their carrier and places it (initializes the carrier and draws it onto the board)
 * @param p2Ships: pointer to the board struct representing player 2's board of ships
 * @param p2_carrier: pointer to the ship struct representing player 2's carrier ship
 * @return nothing
 * @modifies p2Ships, p2_carrier
 */
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

/**
 * Displays screen for P2 placing their battleship and places it (initializes the battleship and draws it onto the board)
 * @param p2Ships: pointer to the board struct representing player 2's board of ships
 * @param p2_battleship: pointer to the ship struct representing player 2's battleship ship
 * @return nothing
 * @modifies p2Ships, p2_battleship
 */
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

/**
 * Displays screen for P2 placing their destroyer and places it (initializes the destroyer and draws it onto the board)
 * @param p2Ships: pointer to the board struct representing player 2's board of ships
 * @param p2_destroyer: pointer to the ship struct representing player 2's destroyer ship
 * @return nothing
 * @modifies p2Ships, p2_destroyer
 */
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

/**
 * Displays screen for P2 placing their submarine and places it (initializes the submarine and draws it onto the board)
 * @param p2Ships: pointer to the board struct representing player 2's board of ships
 * @param p2_submarine: pointer to the ship struct representing player 2's submarine ship
 * @return nothing
 * @modifies p2Ships, p2_submarine
 */
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

/**
 * Displays screen for P2 placing their patrol boat and places it (initializes the patrol boat and draws it onto the board)
 * @param p2Ships: pointer to the board struct representing player 2's board of ships
 * @param p2_patrol_boat: pointer to the ship struct representing player 2's patrol boat ship
 * @return nothing
 * @modifies p2Ships, p2_patrol_boat
 */
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

/**
 * Places all of p2 ships (individually prompts user to place each ship, initializing and drawing them onto the board)
 * @param p2Ships: pointer to the board struct representing player 2's board of ships
 * @param p2_carrier: pointer to the ship struct representing player 2's carrier ship
 * @param p2_battleship: pointer to the ship struct representing player 2's battleship ship
 * @param p2_destroyer: pointer to the ship struct representing player 2's destroyer ship
 * @param p2_submarine: pointer to the ship struct representing player 2's submarine ship
 * @param p2_patrol_boat: pointer to the ship struct representing player 2's boat ship
 * @return nothing
 * @modifies p2Ships, p2_carrier, p2_battleship, p2_destroyer, p2_submarine, p2_patrol_boat
 */
void p2_ship_placement(board* p2Ships, ship* p2_carrier, ship* p2_battleship, ship* p2_destroyer, ship* p2_submarine, ship* p2_patrol_boat) {
    p2_place_carrier(p2Ships, p2_carrier);
    p2_place_battleship(p2Ships, p2_battleship);
    p2_place_destroyer(p2Ships, p2_destroyer);
    p2_place_submarine(p2Ships, p2_submarine);
    p2_place_patrol_boat(p2Ships, p2_patrol_boat); 
}

/**
 * Prints a player's board of ships and their corresponding hp
 * @param pShips: board representing board of ships to print
 * @param p_carrier: ship struct representing whichever player's carrier ship
 * @param p_battleship: ship struct representing whichever player's battleship ship
 * @param p_destroyer: ship struct representing whichever player's destroyer ship
 * @param p_submarine: ship struct representing whichever player's submarine ship
 * @param p_patrol_boat: ship struct representing whichever player's boat ship
 * @return nothing
 */
void print_ships(board pShips, ship p_carrier, ship p_battleship, ship p_destroyer, ship p_submarine, ship p_patrol_boat) {
    printf("\n\n╔═════<[ - ][ | ][ | ]>   BATTLESHIP   <[ - ][ - ][ | ]>═════╗\n\n");
    print_board(pShips);
    printf("\n\n    ^ ^ ^   Your Ships and Health   ^ ^ ^");
    printf("\n  Carrier (%d/5 \u2665) Battleship (%d/4 \u2665) Destroyer (%d/3 \u2665) Submarine (%d/3 \u2665) Patrol Boat (%d/2 \u2665)", 
    p_carrier.health, p_battleship.health, p_destroyer.health, p_submarine.health, p_patrol_boat.health);
    printf("\n\n╙─────────────────────────────────────────────────────────────╜");
    printf("\n\n<[ - ][ - ][ | ]>   Press [Any Letter] + [Enter] to Continue   <[ | ][ | ][ - ]>\n\n");
}

/**
 * Prints a player's updated "attackboard" (the board tracking their hits and misses on the enemy) in a screen
 signifying a hit and the enemy ships they have sunk
 * @param attackBoard: board representing whichever player's hits and misses
 * @param p_carrier: ship struct representing the enemy's carrier ship
 * @param p_battleship: ship struct representing the enemy's battleship ship
 * @param p_destroyer: ship struct representing the enemy's destroyer ship
 * @param p_submarine: ship struct representing the enemy's submarine ship
 * @param p_patrol_boat: ship struct representing the enemy's boat ship
 * @return nothing
 */
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

/**
 * Prints a player's updated "attackboard" (the board tracking their hits and misses on the enemy) in a screen
 signifying a miss and the enemy ships they have sunk
 * @param attackBoard: board representing whichever player's hits and misses
 * @param p_carrier: ship struct representing the enemy's carrier ship
 * @param p_battleship: ship struct representing the enemy's battleship ship
 * @param p_destroyer: ship struct representing the enemy's destroyer ship
 * @param p_submarine: ship struct representing the enemy's submarine ship
 * @param p_patrol_boat: ship struct representing the enemy's boat ship
 * @return nothing
 */
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

/**
 * Implements p1's turn to attack; asks for target until input is valid, acts accordingly to either hit
 or miss
 * @param p1Attack: pointer to the board struct representing board that tracks player 1's hits and misses
 * @param p2Ships: pointer to the board struct representing board containing the enemy's ships
 * @param p2_carrier: pointer to the ship struct representing the enemy carrier ship
 * @param p2_battleship: pointer to the ship struct representing the enemy battleship ship
 * @param p2_destroyer: pointer to the ship struct representing the enemy destroyer ship
 * @param p2_submarine: pointer to the ship struct representing the enemy submarine ship
 * @param p2_patrol_boat: pointer to the ship struct representing the enemy patrol boat ship
 * @return nothing
 * @modifies p1Attack, p2Ships, p2_carrier, p2_battleship, p2_destroyer, p2_submarine, p2_patrol_boat
 */
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

/**
 * Implements p2's turn to attack; asks for target until input is valid, acts accordingly to either hit
 or miss
 * @param p2Attack: pointer to the board struct representing board that tracks player 2's hits and misses
 * @param p1Ships: pointer to the board struct representing board containing the enemy's ships
 * @param p1_carrier: pointer to the ship struct representing the enemy carrier ship
 * @param p1_battleship: pointer to the ship struct representing the enemy battleship ship
 * @param p1_destroyer: pointer to the ship struct representing the enemy destroyer ship
 * @param p1_submarine: pointer to the ship struct representing the enemy submarine ship
 * @param p1_patrol_boat: pointer to the ship struct representing the enemy patrol boat ship
 * @return nothing
 * @modifies p2Attack, p1Ships, p1_carrier, p1_battleship, p1_destroyer, p1_submarine, p1_patrol_boat
 */
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

/**
 * Prints win screen signifying player 1's win
 * @param none
 * @return nothing
 */
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

/**
 * Prints win screen signifying player 2's win
 * @param none
 * @return nothing
 */
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

/**
 * Checks if the game has been won (if someone has sunk all of the opposing player's ships)
 * @param p1_carrier: ship struct representing player 1's carrier ship
 * @param p1_battleship: ship struct representing player 1's battleship ship
 * @param p1_destroyer: ship struct representing player 1's destroyer ship
 * @param p1_submarine: ship struct representing player 1's submarine ship
 * @param p1_patrol_boat: ship struct representing player 1's boat ship
 * @param p2_carrier: ship struct representing player 2's carrier ship
 * @param p2_battleship: ship struct representing player 2's battleship ship
 * @param p2_destroyer: ship struct representing player 2's destroyer ship
 * @param p2_submarine: ship struct representing player 2's submarine ship
 * @param p2_patrol_boat: ship struct representing player 2's boat ship
 * @return bool representing if game has been won; true if so and false if not
 */
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

/**
 * Initializes all variables necessary for playing the game and progression, calls stages in order, does turns until 
 a player wins, deallocates memory after
 * @param none
 * @return nothing
 */
void play_game() {

    // for progressing
    char c;
    int num_args_read = 0;

    // allow both users to place ships and display their choices
    board p1Ships = create_board();
    ship p1_carrier, p1_battleship, p1_destroyer, p1_submarine, p1_patrol_boat; 
    p1_ship_placement(&p1Ships, &p1_carrier, &p1_battleship, &p1_destroyer, &p1_submarine, &p1_patrol_boat);
    print_ships(p1Ships, p1_carrier, p1_battleship, p1_destroyer, p1_submarine, p1_patrol_boat);

    board p2Ships = create_board();
    ship p2_carrier, p2_battleship, p2_destroyer, p2_submarine, p2_patrol_boat; 
    // take continue any key
    num_args_read = scanf("%c", &c);
    if (num_args_read >= 1) p2_ship_placement(&p2Ships, &p2_carrier, &p2_battleship, &p2_destroyer, &p2_submarine, &p2_patrol_boat);
    print_ships(p2Ships, p2_carrier, p2_battleship, p2_destroyer, p2_submarine, p2_patrol_boat);


    board p1Attack = create_board();
    board p2Attack = create_board();

    // once ready, start turns
    num_args_read = scanf("%c", &c);
    while (getchar() != '\n');
    if (num_args_read >= 1) {
        
        num_args_read = 0;

        // p1 always goes first
        p1_shot(&p1Attack, &p2Ships, &p2_carrier, &p2_battleship, &p2_destroyer, &p2_submarine, &p2_patrol_boat); 

        // continue while game not over
        while (1) {
            // let p2 show the damage p1 did to them
            num_args_read = scanf("%c", &c);
            while (getchar() != '\n');
            if (num_args_read >= 1) print_ships(p2Ships, p2_carrier, p2_battleship, p2_destroyer, p2_submarine, p2_patrol_boat);
            num_args_read = 0;
            if (check_win(p1_carrier, p1_battleship, p1_destroyer, p1_submarine, p1_patrol_boat, 
                p2_carrier, p2_battleship, p2_destroyer, p2_submarine, p2_patrol_boat)) break; 
            // p2 turn to attack
            num_args_read = scanf("%c", &c);
            while (getchar() != '\n');
            if (num_args_read >= 1) p2_shot(&p2Attack, &p1Ships, &p1_carrier, &p1_battleship, &p1_destroyer, &p1_submarine, &p1_patrol_boat); 
            num_args_read = 0;
            // let p1 see the damage p2 did to them
            num_args_read = scanf("%c", &c);
            while (getchar() != '\n');
            if (num_args_read >= 1) print_ships(p1Ships, p1_carrier, p1_battleship, p1_destroyer, p1_submarine, p1_patrol_boat);   
            num_args_read = 0;
            if (check_win(p1_carrier, p1_battleship, p1_destroyer, p1_submarine, p1_patrol_boat, 
                p2_carrier, p2_battleship, p2_destroyer, p2_submarine, p2_patrol_boat)) break; 
            // p1 turn to attack
            num_args_read = scanf("%c", &c);
            while (getchar() != '\n');
            if (num_args_read >= 1) p1_shot(&p1Attack, &p2Ships, &p2_carrier, &p2_battleship, &p2_destroyer, &p2_submarine, &p2_patrol_boat); 
            num_args_read = 0;
        
        }
    }

    delete_board(&p1Ships);
    delete_board(&p2Ships);
    delete_board(&p1Attack);
    delete_board(&p2Attack);

}

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"
#include "input.h"
#include "ships.h"
#include "stages.h"

// improvements:
// maybe add < > to the ends of the ships just change the draw_ship function (implemented :))
// under your ships and damage add all the ship healths (implemented)
// change to only enter only needed

// issues:
// function to check for overlap does not fucking work (resolved)
// fix getValidInt() (resolved)
int main() {

    // for continue commands
    char c;
    int num_args_read = 0;

    // call welcome screen
    print_welcome_screen();
    num_args_read = scanf("%c", &c);
    // call tutorial screen
    if (num_args_read >= 1) print_tutorial_screen();
    while (getchar() != '\n');
    num_args_read = scanf("%c", &c);
    // start playing the game
    if (num_args_read >= 1) play_game();

}
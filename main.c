#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"
#include "input.h"
#include "ships.h"
#include "stages.h"

// BattleShip Game
int main() {

    // for continue commands
    char c;
    int num_args_read = 0;

    print_welcome_screen();
    num_args_read = scanf("%c", &c);
    if (num_args_read >= 1) print_tutorial_screen();
    while (getchar() != '\n');
    num_args_read = scanf("%c", &c);
    if (num_args_read >= 1) play_game();

}

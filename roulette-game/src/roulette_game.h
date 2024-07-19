/* 
Header file to connect the game logic to the gui.


must include all the functions for the game logic in here
*/

----------------------------------------------------------------------
ex. 

#ifndef ROULETTE_GAME_H
#define ROULETTE_GAME_H

// Declare the functions for game logic
double placeNumberBet(int number, double bet, int random);
double placeOddEvenBet(double bet, int random);
double placeBlackRedBet(double bet, int random, int blackNumbers[], int redNumbers[]);

#endif
----------------------------------------------------------------------
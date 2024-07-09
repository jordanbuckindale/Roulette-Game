/*
roulette game with gui, visual spinning wheel and betting table where user can place bets. Game will load with loading screen where pregame funtions run to ensure integrity of bet placing (ie. wheel numbers, betting table catagories).


to do: 
- bettingtableCheck function
- figure out gui
- learn how to calculate the wheel spin
- create loading screen
- 
*/

#include<stdio.h>
#include <stdlib.h>
#include <time.h>

void checkRouletteNumbers(int rouletteWheelNumbers[]);

int main() {

    // roulette variables
    #define numberTotal 37

    int rouletteWheelNumbers[numberTotal] = {0, 32, 15, 19, 4, 21,
                                             2, 25, 17, 34, 6, 27,
                                             13, 36, 11, 30, 8, 23, 
                                             10, 5, 24, 16, 33, 1,
                                             20, 14, 31, 9, 22, 18, 
                                             29, 7, 28, 12, 35, 3,
                                             26};

    checkRouletteNumbers(rouletteWheelNumbers);
    
    int redNumbers[] = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};
    int blackNumbers[] = {2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35};
    int greenNumbers[] = {0,00};
    int oddNumbers[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35};
    int evenNumbers[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36};
    int firstDozen[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int secondDozen[] = {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
    int thirdDozen[] = {25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36};
     

    // game variables
    int const MIN_NUMBER = 0, MAX_NUMBER = 36;
    int number;
    int random;
    int money;
    int startingMoney;

    char gametype;
    char evenoodd;
    char blackred;
    char stop = 'N';
    
    double bet, winnings = 0;

    printf("Welcome to ROULETTE\n\n");
    printf("with how much money do you want to start?\n\n");
    
    // read input from user for buy in amount 
    scanf("%d", &startingMoney);

    // insert value of money into new var.
    money = startingMoney;

    while(money > 0 && stop != 'y') {

        money = money + winnings;
        winnings = 0;
        printf("How much would you like to bet sir?");
        scanf("%lf", &bet);

        // condition to make sure that the bet doesnt exceed the total amount of money.
        while(bet > money) {
            printf("How much would you like to bet sir?");
            scanf("%lf", &bet);
        }

        // scan the type of bet
        printf("Would you like to bet on a number(n), on odd/even(o), or on black/red (b)");
        scanf("%c", &gametype);

        if (gametype == 'n' || gametype == 'N') {

            printf("What number would you like to bet on? ");
            scanf("%d", &number);

            if(number == 0) {
                number = 37;
            }

            srand(time(0));
            random = rand() % 37;

            if (number != random) {
                printf("The ball landed on %d\n", &random);
                printf("You lose %.2f.\n", &winnings);
                winnings -= bet;
            }

            if(number == random) {
                printf("The ball landed on %d\n", &random);
                printf("You win %.2f.\n", &winnings);
                winnings += bet;
            }
        }

    
    }

    return 0;
}


 // new

    

/* 
Function to check the spin table has all the correct numbers. compare the outcomes to the numbers of the table.
*/
void checkRouletteNumbers(int rouletteWheelNumbers[]) {
    
    // Iterate through numbers 0 to 36.
    for (int i = 0; i <= 36; i++) {

        // variable to indicate if the number has been found.
        int found = 0;

        // for loop to iterate through the length of the array and check every element within the array to confirm the number is present.
        for(int j = 0; j <= numberTotal; j++){
            
            // if the number is present, the 'found' variable will act as a boolean and switch to 1 or 'true'.
            if(i == rouletteWheelNumbers[j]){
                found = 1;
            }
            
        }  
        // if the number is not found within the array, output error message and exit.    
        if(found != 1) {
                printf("Game Error: Missing number %d.\n", i);
                return;
            }   
    }
    // if successful, output and continue game.
    printf("ALL numbers are present. \n");
}

/*
Function to check the arrays that represent the betting table outcomes.
*/
void checkBettingTable(int redNumbers[], int blackNumbers[], int oddNumbers[], int evenNumbers[], int firstDozen[], int secondDozen[],int thirdDozen[]) {
    
    // check all these values compared to the game values.
    int redNum[] = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};
    int blackNum[] = {2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35};
    int oddNum[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35};
    int evenNum[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36};
    int fDozen[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int sDozen[] = {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
    int tDozen[] = {25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36};
     
     // function here.
}
/*
roulette game with gui, visual spinning wheel and betting table where user can place bets. Game will load with loading screen where pregame funtions run to ensure integrity of bet placing (ie. wheel numbers, betting table catagories).


to do: 
- bettingtableCheck function
- figure out gui
- learn how to calculate the wheel spin
- create loading screen


first layer:
Menu  
- play (second layer)
- settings (configs)
- exit (exit program)


second layer:
- place bet (third layer)
- table summary (visual output)
- return to lobby (back to first layer)

third layer:
- place bets (fourth layer)
- bet summary (visual output)
- confirm bet (visual output and compute then back to second layer)
-back (back to second layer)

fourth layer:
- odd even (function)
- red black (function)
- number    (function)


*/

#include<stdio.h>
#include <stdlib.h>
#include <time.h>


void checkRouletteNumbers(int rouletteWheelNumbers[]);
char loadingScreen(int rouletteWheelNumbers[]);
int placeNumberBet(int number,double bet, int random);
int placeOddEvenBet();
int placeBlackRedBet();
int numberGenerator();
void AccBalanceReport(int money, int startingMoney, int counter);

int main() {


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

    int const MIN_NUMBER = 0, MAX_NUMBER = 36;
    int beginning;
    int number;
    int money;
    int random;
    int startingMoney;
    int counter;

    char gametype;
    char evenoodd;
    char blackred;
    char stop = 'N';
    
    double bet, winnings = 0;

    beginning = loadingScreen(rouletteWheelNumbers);

    if (beginning == 'p' || beginning == 'p') {

        printf("\n\nWith how much money do you want to start? \n");
        
        // read valid input from user for buy in amount and exit with error code otherwise.
        if (scanf("%d", &startingMoney) != 1) {
            printf("Invalid input for starting money.\n");
            return 1;
        }
        // insert value of money into new var.
        money = startingMoney;

        while(money > 0 && stop != 'y') {

            money = money + winnings;
            winnings = 0;
            AccBalanceReport(money, startingMoney, counter);

            counter += 1;
            printf("\nHow much would you like to bet? \n");
            if (scanf("%lf", &bet) != 1) {
                printf("Invalid input for bet amount.\n");
                return 1;
            }

            // condition to make sure that the bet doesnt exceed the total amount of money.
            while(bet > money) {
                printf("You can't bet more than you have. How much would you like to bet? \n");
                if (scanf("%lf", &bet) != 1) {
                    printf("Invalid input for bet amount.\n");
                    return 1;
                }
            }

            // scan the type of bet
            printf("\nWould you like to bet on a number(n), on odd/even(o), or on black/red (b) \n");
            if (scanf(" %c", &gametype) != 1) {
                printf("Invalid input for game type.\n");
                return 1;
            }

            // generate number after bet selected.
            random = numberGenerator();


            if (gametype == 'n' || gametype == 'N') {

                winnings = placeNumberBet(number, bet, random);

            }

            if (gametype == 'o' || gametype == 'O') {

                //winnings = placeOddEvenBet(number, bet, random);

            }

            if (gametype == 'b' || gametype == 'B') {

                //winnings = placeBlacKRedBet(number, bet, random);

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
    for (int i = 0; i < 20; i++) {
        printf("%*s", i, "*");
        printf("Loading...");
        printf("%*s\n", 20-i, "*");
    }

    for (int i = 0; i < 20; i++) {
        printf("%*s", 20-i, "*");
        printf("Loading...");
        printf("%*s\n", i, "*");
    }

    printf("*****ALL NUMBERS PRESENT******\n\n");

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


int placeOddEvenBet();
int palceBlackRedBet();


int placeNumberBet(int number, double bet, int random) {

    double payout;
    char answer;

    printf("\nWhat number would you like to bet on? \n");
    
    if (scanf("%d", &number) != 1) {
        printf("Invalid input for number.\n");
        return 1;
    }
 
    printf("\n     %.0f$ placed on %d\n", bet, number);
    printf("--------------------------\n");
    printf("  The ball landed on %d\n", random);  // Use %d for int


    if (number != random) {
        printf("\n     You lose %.2f!\n", bet);
        payout -= bet;
    }
    

    if (number == random) {
        printf("\n     You win %.2f!\n", bet * 35);  // Roulette pays 35:1 on a single number
        payout += bet * 35;
    }



    return payout;
}

int numberGenerator(void) {

    int num;

    srand(time(0));
    num = rand() % 37;

    return num;
}


char loadingScreen(int rouletteWheelNumbers[]) { 

    char start; 
    printf("-----WELCOME TO ROULETTE-----\n\n");
    printf("Menu: \n");
    printf("- Play     (p) \n");
    printf("- Settings (s) \n");
    printf("- Exit     (e) \n\n");

    printf("Select menu item: ");

    if (scanf(" %c", &start) != 1) {
            printf("Invalid entry.\n");
            return 1;
    }

    return start;
}

void AccBalanceReport(int money, int startingMoney, int counter) {

    int winnings = money - startingMoney;

    if(winnings < 0) {
        winnings = 0;
    }


    printf("--------------------------\n\n");
    printf("         Summary          \n\n");
    printf("Account Balance:  $%d\n", money);
    printf("Total Winnings:    %d\n", winnings);
    printf("Number of Bets:    %d\n\n", counter);
    printf("--------------------------\n");
}
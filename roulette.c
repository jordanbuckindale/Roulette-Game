/*
roulette game with gui, visual spinning wheel and betting table where user can place bets. Game will load with loading screen where pregame funtions run to ensure integrity of bet placing (ie. wheel numbers, betting table catagories).


to do: 
- bettingtableCheck function
- figure out gui
- learn how to calculate the wheel spin
- create loading screen


first layer:
Menu  
- play            (second layer)
- settings        (configs)
- exit            (exit program)


second layer:
- place bet       (third layer)
- table summary   (visual output)
- return to lobby (back to first layer)

third layer:
- place bets      (fourth layer)
- bet summary     (visual output)
- confirm bet     (visual output and compute then back to second layer)
- back            (back to second layer)

fourth layer:
- odd even        (function)
- red black       (function)
- number          (function)


// remove number from number parameters and have as varaible in function?
*/

#include<stdio.h>
#include <stdlib.h>
#include <time.h>


void checkRouletteNumbers(int rouletteWheelNumbers[]);
int placeOddEvenBet(double bet, int random);
int placeBlackRedBet(double bet, int random, int blackNumbers[], int redNumbers[]);
int placeNumberBet(double bet, int random);
int numberGenerator();
char loadingScreen(int rouletteWheelNumbers[]);
char playScreen();
char settingsScreen();
int initializeStartingMoney();
double initializeBet(int money);
int placeBet(double bet, int random, int blackNumbers[], int redNumbers[]);
void AccBalanceReport(int money, int startingMoney, int counter);
char promptQuit();

int main() {


    #define numberTotal 37
        
    int rouletteWheelNumbers[numberTotal] =    {0, 32, 15, 19, 4, 21,
                                                2, 25, 17, 34, 6, 27,
                                                13, 36, 11, 30, 8, 23, 
                                                10, 5, 24, 16, 33, 1,
                                                20, 14, 31, 9, 22, 18, 
                                                29, 7, 28, 12, 35, 3,
                                                26};

    checkRouletteNumbers(rouletteWheelNumbers);

    int redNumbers[] = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};
    int blackNumbers[] = {2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35};
    int greenNumbers[] = {0};
    int oddNumbers[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35};
    int evenNumbers[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36};
    int firstDozen[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int secondDozen[] = {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
    int thirdDozen[] = {25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36};

    int const MIN_NUMBER = 0, MAX_NUMBER = 36;
    
    // initialize variables to store players choice.
    int beginning;
    int playChoice;

    //initizalize all other variables.
    int money;
    int random;
    int startingMoney;
    int counter;

    char gametype;
    char evenoodd;
    char blackred;
    char stop = 'N';
    
    double bet, winnings = 0;

    // call function to present loading screen and prompt user for input. 
    beginning = loadingScreen(rouletteWheelNumbers);

    // if statement for when user inputs 'p' or 'P' to play, allowing the user to place bet.
    if (beginning == 'p' || beginning == 'P') {
        
        // call function to present play screen, and prompt user for input.
        playChoice = playScreen();

        // checks user input for 'p' or 'P' to initiate money and place bet.  
        if (playChoice == 'p' || playChoice == 'P') {
           
            // function that facilitates processing users starting money.
            money = initializeStartingMoney();

            // while loop that allows user to place bets as long as money is still in account and user hasnt prompted to quit.
            while(money > 0 && stop != 'y') {

                // add winnings from bet and initialize back to 0, ready for next bet.
                money = money + winnings;
                winnings = 0;

                // call function to present account summary.
                AccBalanceReport(money, startingMoney, counter);

                // incremented variable that is used in AccBalanceReport(). Keeps track of how many bets are placed by user. 
                counter += 1;
                
                // call function that prompts user for bet amount. 
                bet = initializeBet(money);
                
                // call function that allows user to place bet. Function that facilitates bet for user; what kind of bet, spin table, and result of spin then returns winnings. 
                winnings = placeBet(bet, random, blackNumbers, redNumbers);

                // call function to prompt user to quit. stores results and is checked through while loop.
                stop = promptQuit();
                
            }
        }

        // if statement for when user inputs 't' or 'T' to report account summary, allowing user to view betting history.
        if (playChoice == 't' || playChoice == 'T') {

            AccBalanceReport(money, startingMoney, counter);
        }

        // if statement for when user inputs 'x' or 'X' to exit. Function call to loading screen. 
        if (playChoice == 'x' || playChoice == 'X') {
        
            beginning = loadingScreen(rouletteWheelNumbers);
        }
    }

    return 0;
}

 // write if statement for configuring settings.

 // write if statement to exit program.


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

/*
Function for user to place bet for odd or even numbers on roulette table.

Function prompts user for bet type, whether odd or even, spins the roulette table, thn outputs the result and returns the winnings. 
*/
int placeOddEvenBet( double bet, int random) {

    double payout;
    char choice;

    //prompt user for bet type.
    printf("Would you like to bet on odd (o) or even (e) numbers? \n");
    if (scanf(" %c", &choice) != 1) {
        printf("Invalid input for game type.\n");
        return 1;
    }
    

    //if user selects 'o' or 'O' then a bet will be placed on all odd numbers.
    if(choice == 'o' || choice == 'O') {

        printf("\n   %.0f$ placed on odd\n", bet);
        printf("--------------------------\n");
        printf("  The ball landed on %d\n", random);

        // lose
        if (random % 2 == 0) {
        printf("\n     You lose %.2f!\n", bet);
        payout -= bet;
        }
    
        //win
        if (random != 0 && random % 2 != 0) {
        printf("\n     You win %.2f!\n", bet);  
        payout += bet;
        }
    }
    //if user selects 'e' or 'E' then a bet will be placed on all even numbers.
    if(choice == 'e' || choice == 'E') {

        printf("\n   %.0f$ placed on even\n", bet);
        printf("--------------------------\n");
        printf("  The ball landed on %d\n", random);

        // lose
        if (random != 0 && random % 2 != 0) {
        printf("\n     You lose %.2f!\n", bet);
        payout -= bet;
        }
    
        //win
        if (random % 2 == 0) {
        printf("\n     You win %.2f!\n", bet);  
        payout += bet;
        }

    }

    return payout;
    
}

/*
Function for user to place bet for black or red numbers on roulette table.

Function prompts user for bet type, whether red or black, spins the roulette table, thn outputs the result and returns the winnings. 
*/ 
int placeBlackRedBet(double bet, int random, int blackNumbers[], int redNumbers[]) {

    double payout = 0;
    char choice;
    int status = 0;

    printf("\nwould you like to bet on black (b) or red (r)? \n");
    if (scanf(" %c", &choice) != 1) {
            printf("Invalid input for game type.\n");
            return 1;
        }

    //if user selects 'b' or 'B' then a bet will be placed on all black numbers.
    if(choice == 'b' || choice == 'B') {

        printf("\n  %.0f$ placed on black\n", bet);
        printf("--------------------------\n");
        printf("  The ball landed on %d\n", random);

        // check if spun number is black.
        for (int i = 0; i < 19; i++) {
            if(random == blackNumbers[i]) {
                status = 1;
                break;
            }
        }

        // lose
        if (status == 0) {
        printf("\n     You lose %.2f!\n", bet);
        payout -= bet;
        }
    
        // win
        if (status == 1) {
        printf("\n     You win %.2f!\n", bet);  
        payout += bet;
        }
    }
    //if user selects 'r' or 'R' then a bet will be placed on all red numbers.
    if(choice == 'r' || choice == 'R') {

        printf("\n  %.0f$ placed on red\n", bet);
        printf("--------------------------\n");
        printf("  The ball landed on %d\n", random);

        // Check if spun number is red.
        for (int i = 0; i < 19; i++) {
            if(random == redNumbers[i]) {
                status = 1;
                break;
            }
        }

        // lose.
        if (status == 0) {
        printf("\n     You lose %.2f!\n", bet);
        payout -= bet;
        }
    
        // win.
        if (status == 1) {
        printf("\n     You win %.2f!\n", bet);  
        payout += bet;
        }
    }

    return payout;
}

/*
Function for user to place bet for numbers on roulette table.

Function prompts user for bet type, which number, spins the roulette table, thn outputs the result and returns the winnings. 
*/ 
int placeNumberBet(double bet, int random) {

    double payout;
    int number;

    //output
    printf("\nWhat number would you like to bet on? \n");
    
    if (scanf("%d", &number) != 1) {
        printf("Invalid input for number.\n");
        return 1;
    }
 
    printf("\n     %.0f$ placed on %d\n", bet, number);
    printf("--------------------------\n");
    printf("  The ball landed on %d\n", random);  // Use %d for int

    // check if number was spun and store payout winnings.
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

int numberGenerator() {

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

char playScreen() {

    char choice; 
    printf("-------------PLAY-------------\n\n");
    printf("Play Menu: \n");
    printf("- Place Bet       (p) \n");
    printf("- Table Summary   (t) \n");
    printf("- Exit to Lobby   (x) \n\n");

    printf("Select menu item: ");

    if (scanf(" %c", &choice) != 1) {
            printf("Invalid entry.\n");
            return 1;

   }

    return choice;
}




/*
Function to allow user to configure settings for the game.

Ideas:
- table minimum bets
- high rollers table (extra 00)
- maximum bets
*/
//char settingsScreen() {
    
    //char start; 
    //printf("-----------SETTINGS------------\n\n");
    //printf("Menu: \n");
    //printf("- Play     (p) \n");
    //printf("- Settings (s) \n");
    //printf("- Exit     (e) \n\n");

    //printf("Select menu item: ");

    //if (scanf(" %c", &start) != 1) {
    //        printf("Invalid entry.\n");
    //        return 1;
    //}

    //return start;

//}


int initializeStartingMoney() {

    int startingMoney;

    printf("\n\nWith how much money do you want to start? \n");
        
    // read valid input from user for buy in amount and exit with error code otherwise.
    while (scanf("%d", &startingMoney) != 1) {
        printf("Invalid input for starting money.\n");
        printf("With how much money do you want to start? \n");
    }

    return startingMoney;
    
}

double initializeBet(int money) {

    double bet;

    printf("\nHow much would you like to bet? \n");
    while((scanf("%lf", &bet) != 1)) {
        printf("Invalid input for bet amount.\n");
        return 1;
    }

    // condition to make sure that the bet doesnt exceed the total amount of money.
    while(bet > money) {
        printf("You can't bet more than you have. How much would you like to bet? \n");
        while(scanf("%lf", &bet) != 1) {

            printf("Invalid input for bet amount.\n");
            printf("How much would you like to bet? \n");
        }
    }

    return bet;

}


int placeBet(double bet, int random,int blackNumbers[], int redNumbers[]) {
    
    int number;
    char gametype;
    double winnings;
    
    // scan the type of bet
    printf("\nWould you like to bet on a number(n), on odd/even(o), or on black/red (b) \n");
    if (scanf(" %c", &gametype) != 1) {
        printf("Invalid input for game type.\n");

        //idea to have while loop to keep reprompting until valid answer
        //printf("\n Bet types:\n - bet on number(n)\n - bet on odd/even(o)\n - bet on black(b) \n");

        return 1;
    }

    // generate number after bet selected.
    random = numberGenerator();


    if (gametype == 'n' || gametype == 'N') {

        winnings = placeNumberBet(bet, random);

    }

    if (gametype == 'o' || gametype == 'O') {

        winnings = placeOddEvenBet(bet, random);

    }

    if (gametype == 'b' || gametype == 'B') {

        winnings = placeBlackRedBet(bet, random, blackNumbers, redNumbers);

    }

    return winnings;
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

char promptQuit() {
    
    char stop;
    printf("Would you like to quit (y/n)? ");

    if (scanf(" %c", &stop) != 1) {
            printf("Invalid entry.\n");
            return 1;

   }    

   return stop;

}

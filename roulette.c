#include<stdio.h>

void checkRouletteNumbers(int rouletteWheelNumbers[]);

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
    int oddNumbers[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35};
    int evenNumbers[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36};
    int firstDozen[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int secondDozen[] = {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
    int thirdDozen[] = {25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36};
     

    
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


void checkBettingTable(void) {
    

    // must check all these.
    int redNumbers[] = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};
    int blackNumbers[] = {2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35};
    int oddNumbers[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35};
    int evenNumbers[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36};
    int firstDozen[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int secondDozen[] = {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
    int thirdDozen[] = {25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36};
     



}
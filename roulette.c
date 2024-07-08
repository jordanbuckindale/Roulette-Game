#include<stdio.h>


int main() {

    int rouletteWheelNumbers[37] = {0, 32, 15, 19, 4, 21,
                                  2, 25, 17, 34, 6, 27,
                                  13, 36, 11, 30, 8, 23, 
                                  10, 5, 24, 16, 33, 1,
                                  20, 14, 31, 9, 22, 18, 
                                  29, 7, 28, 12, 35, 3,
                                  26};

    checkRouletteNumbers(rouletteWheelNumbers);
    
    int redNumbers[] = {};
    int blackNumbers[] = {};
    int oddNumbers[] = {};
    int evenNumbers[] = {};
    int firstDozen[] = {};
    int secondDozen [] = {};
    int thirdDozen[] = {};
     

    
    
            
        

     return 0;
}






int checkRouletteNumbers(int rouletteWheelNumbers[]) {
    
    
        for (int i = 0; i <= 36; i++) {
            

            for(int j = 0; j<= 36; j++){
                
                if(i == rouletteWheelNumbers[j]){
                    printf("%d\n", rouletteWheelNumbers[j]);
                    j = 100;
                    break;
                }
                    
                else {
                    printf("Missing number %d", i);

                    return 0;
                }
            }         
        }
    }
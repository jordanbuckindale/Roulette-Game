#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>
#include "wheel.h"

typedef struct {
    int number;
    int color;  // 0 for green, 1 for red, 2 for black
    int column;
    int dozen;
} RouletteNumber;

RouletteNumber roulette_numbers[37];

void initialize_roulette_numbers() {
    int reds[] = {1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36};
    for (int i = 0; i < 37; i++) {
        roulette_numbers[i].number = i;
        roulette_numbers[i].color = 2;  // Default to black
        for (int j = 0; j < 18; j++) {
            if (i == reds[j]) {
                roulette_numbers[i].color = 1;  // Red
                break;
            }
        }
        if (i == 0) roulette_numbers[i].color = 0;  // Green
        roulette_numbers[i].column = (i - 1) % 3 + 1;
        roulette_numbers[i].dozen = (i - 1) / 12 + 1;
    }
}

int spin_wheel() {
    return rand() % 37;
}

int evaluate_bet(int bet_type, int bet_value, int winning_number) {
    RouletteNumber result = roulette_numbers[winning_number];
    switch(bet_type) {
        case 0:  // Straight up
            return (bet_value == winning_number) ? 35 : -1;
        case 1:  // Red/Black
            return (bet_value == result.color) ? 1 : -1;
        case 2:  // Odd/Even
            return ((winning_number % 2 == bet_value) && winning_number != 0) ? 1 : -1;
        case 3:  // Dozens
            return (bet_value == result.dozen) ? 2 : -1;
        case 4:  // Columns
            return (bet_value == result.column) ? 2 : -1;
        case 5:  // Low/High
            return ((bet_value == 0 && winning_number <= 18) || 
                    (bet_value == 1 && winning_number >= 19 && winning_number != 0)) ? 1 : -1;
        default:
            return -1;
    }
}

void update_balance(int *balance, int bet_amount, int winnings) {
    *balance += winnings * bet_amount;
}

// Add more functions as needed for handling bets, updating UI, etc.

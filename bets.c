#include <gtk/gtk.h>
#include <math.h>
#include <stdio.h>
#include "wheel.h"

/*
Function to create the draw object. 

Parameters (from left to right): 
(1). pointer to the widget being drawn.
(2). pointer to object used to perform drawing operations.
(3). pointer to pass custom data to the callback function.
*/
gboolean on_draw_table(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    // Set background color (green)
    cairo_set_source_rgb(cr, 0.25, 0.5, 0.25);
    cairo_paint(cr);

    // Set up dimensions
    int width = 400;
    int height = 200;
    int cell_width = width / 14;  // 12 number columns + 1 for 0
    int cell_height = height / 5;  // 3 number rows + 1 for additional bets
    int redNumbers[] = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};
    int bet_num = 0;    //start index
    int red_num_found;

    // Draw 0 column
    cairo_set_source_rgb(cr, 0, 0.5, 0);  // Green for 0
    cairo_rectangle(cr, 0, 0, cell_width, 3 * cell_height);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);  // White text
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 20);
    cairo_move_to(cr, 0.3 * cell_width, 1.5 * cell_height);
    cairo_show_text(cr, "0");

    // Draw number grid
    for (int i = 0; i < 36; i++) {
        int col = (i / 3) + 1;
        int row = 2 - (i % 3);  // Reverse row order
        bet_num ++; //increment to number 1
        red_num_found = 0; // false
        
        // check if they are red numbers, if not, they are black.
        for(int j = 0; j < 18; j++) {

            if(bet_num == redNumbers[j]) {
                cairo_set_source_rgb(cr, 0.8, 0, 0);  // Red
                red_num_found = 1;
                break;
            }
        }
    
        // if red number not found, treat as black number.
        if(red_num_found == 0) {
            cairo_set_source_rgb(cr, 0, 0, 0);  // black
        }
        

        // Draw rectangle
        cairo_rectangle(cr, col * cell_width, row * cell_height, cell_width, cell_height);
        cairo_fill(cr);

        // Add number text
        cairo_set_source_rgb(cr, 1, 1, 1);  // White text
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 15);
        char num_str[3];
        snprintf(num_str, sizeof(num_str), "%d", i + 1);
        cairo_move_to(cr, (col + 0.5) * cell_width - 10, (row + 0.5) * cell_height + 10);
        cairo_show_text(cr, num_str);
    }

    
    // Add 2 to 1 columns
    for (int i = 0; i < 3; i++) {
        cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);  // Light gray
        cairo_rectangle(cr, 13 * cell_width, i * cell_height, cell_width, cell_height);
        cairo_fill(cr);
        cairo_set_source_rgb(cr, 1, 1, 1);  // White text
        cairo_set_font_size(cr, 12);
        cairo_move_to(cr, 13.1 * cell_width, (i + 0.5) * cell_height + 5);
        cairo_show_text(cr, "2to1");
    }

    // 1st dozen
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);  // Dark gray
    cairo_rectangle(cr, cell_width, 3 * cell_height, 4 * cell_width, cell_height);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, 2.25 * cell_width, 3.5 * cell_height);
    cairo_show_text(cr, "1ST 12");

    // 2nd dozen
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);  
    cairo_rectangle(cr, 5 * cell_width, 3 * cell_height, 4 * cell_width, cell_height);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, 6.25 * cell_width, 3.5 * cell_height);
    cairo_show_text(cr, "2ND 12");
    // 3rd dozen
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);  
    cairo_rectangle(cr, 9 * cell_width, 3 * cell_height, 4 * cell_width, cell_height);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, 10.25 * cell_width, 3.5 * cell_height);
    cairo_show_text(cr, "3RD 12");

    // Add more betting areas and text as needed
    // 1 to 18
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);  
    cairo_rectangle(cr, cell_width, 4 * cell_height, 2 * cell_width, cell_height);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, 1.1 * cell_width, 4.5 * cell_height);
    cairo_show_text(cr, "1 TO 18");
    // even
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);  
    cairo_rectangle(cr, 3 * cell_width, 4 * cell_height, 2 * cell_width, cell_height);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, 3.3 * cell_width, 4.5 * cell_height);
    cairo_show_text(cr, "EVEN");
    // red
    cairo_set_source_rgb(cr, 1, 0.0, 0.0);  
    cairo_rectangle(cr, 5 * cell_width, 4 * cell_height, 2 * cell_width, cell_height);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, 5.5 * cell_width, 4.5 * cell_height);
    cairo_show_text(cr, "RED");
    // black
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);  // Dark gray
    cairo_rectangle(cr, 7 * cell_width, 4 * cell_height, 2 * cell_width, cell_height);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, 7.3 * cell_width, 4.5 * cell_height);
    cairo_show_text(cr, "BLACK"); 
    // odd
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);  // Dark gray
    cairo_rectangle(cr, 9 * cell_width, 4 * cell_height, 2 * cell_width, cell_height);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, 9.4 * cell_width, 4.5 * cell_height);
    cairo_show_text(cr, "ODD");
    // 19 to 36
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);  // Dark gray
    cairo_rectangle(cr, 11 * cell_width, 4 * cell_height, 2 * cell_width, cell_height);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, 11.2 * cell_width, 4.5 * cell_height);
    cairo_show_text(cr, "19 TO 36");

    cairo_set_line_width(cr, 2.0);
    
    // outlines of betting table.
    for( int i = 0; i <= 5; i++) {

        // draw lines for first 3 rows.
        if(i <= 3) {
          
            // horizontal lines (1 to 3 rows). 
            if (i == 3) {
                cairo_move_to(cr, 0, i * cell_height);
            }
            else {
                cairo_move_to(cr, cell_width, i * cell_height);
            }
            cairo_line_to(cr, 14 * cell_width, i * cell_height); // Adjust according to the number of columns
            cairo_stroke(cr);
        
            // vertical lines (1 to 3 rows).
            for(int j = 0; j < 15; j++) {
                cairo_move_to(cr, j * cell_width, 0);
                cairo_line_to(cr, j * cell_width, i * cell_height);
                cairo_stroke(cr);
            }
            
        }

        else {
            // horizontal lines (4th and 5th row)
            cairo_move_to(cr, cell_width, i * cell_height);
            cairo_line_to(cr, (12 * cell_width) + cell_width, i * cell_height); // Adjust according to the number of columns
            cairo_stroke(cr);

            // vertical lines (4th row)
            if(i == 4) {

                for(int k = 0; k <= 3; k++) {
                cairo_move_to(cr, (k * 4 * cell_width) + cell_width, i * cell_height);
                cairo_line_to(cr, (k * 4 * cell_width) + cell_width, (i - 1) * cell_height);
                cairo_stroke(cr);
                }
            }

            // vertical lines (5th row)
            if(i == 5) {

                for(int k = 0; k <= 6; k++) {
                cairo_move_to(cr, (k * 2 * cell_width) + cell_width, i * cell_height);
                cairo_line_to(cr, (k * 2 * cell_width) + cell_width, (i - 1) * cell_height);
                cairo_stroke(cr);
                }
            }

        }
    }     



    return FALSE;
}

/*
* function that creates and returns the roulette betting table. 
*/
GtkWidget* create_roulette_table(void) {
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 400, 200);

    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw_table), NULL);
    return drawing_area;
}

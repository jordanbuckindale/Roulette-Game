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
    int cell_width = width / 13;  // 12 number columns + 1 for 0
    int cell_height = height / 5;  // 3 number rows + 1 for additional bets

    // Draw number grid
    for (int i = 0; i < 36; i++) {
        int col = i / 3;
        int row = 2 - (i % 3);  // Reverse row order
        
        // Set color (red for odd, black for even)
        if ((i + 1) % 2 == 0) {
            cairo_set_source_rgb(cr, 0, 0, 0);  // Black
        } else {
            cairo_set_source_rgb(cr, 0.8, 0, 0);  // Red
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

    
    // Add 2 to 1 (1st row).
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);  // Green
    cairo_rectangle(cr, 12 * cell_width, 0, cell_width, cell_height);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);  // White text
    
    cairo_save(cr);
    cairo_set_font_size(cr, 10);
    cairo_rotate(cr, -M_PI_2);
    cairo_move_to(cr, -0.9 * cell_height, 12.6 * cell_width);
    cairo_show_text(cr, "2 TO 1");
    cairo_restore(cr);

    // Add 2 to 1 (2nd row).
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);  // Green
    cairo_rectangle(cr, 12 * cell_width, 1 * cell_height, cell_width, cell_height);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);  // White text
    
    
    cairo_save(cr);
    cairo_set_font_size(cr, 10);
    cairo_rotate(cr, -M_PI_2);
    cairo_move_to(cr, -1.9 * cell_height, 12.6 * cell_width);
    cairo_show_text(cr, "2 TO 1");
    cairo_restore(cr);

    // Add 2 to 1 (3rd row).
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);  // Green
    cairo_rectangle(cr, 12 * cell_width, 2 * cell_height, cell_width,cell_height);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);  // White text
    
    cairo_save(cr);
    cairo_set_font_size(cr, 10);
    cairo_rotate(cr, -M_PI_2);
    cairo_move_to(cr, -2.9 * cell_height, 12.6 * cell_width);
    cairo_show_text(cr, "2 TO 1");
    cairo_restore(cr);

    // 1st dozen
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);  // Dark gray
    cairo_rectangle(cr, 0, 3 * cell_height, 4 * cell_width, cell_height);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, 1.25 * cell_width, 3.5 * cell_height);
    cairo_show_text(cr, "1ST 12");

    // 2nd dozen
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);  
    cairo_rectangle(cr, 4 * cell_width, 3 * cell_height, 4 * cell_width, cell_height);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, 5.25 * cell_width, 3.5 * cell_height);
    cairo_show_text(cr, "2ND 12");
    // 3rd dozen
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);  
    cairo_rectangle(cr, 8 * cell_width, 3 * cell_height, 4 * cell_width, cell_height);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, 9.25 * cell_width, 3.5 * cell_height);
    cairo_show_text(cr, "3RD 12");

    // Add more betting areas and text as needed
    // 1 to 18
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);  
    cairo_rectangle(cr, 0, 4 * cell_height, 2 * cell_width, cell_height);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, 0.1 * cell_width, 4.5 * cell_height);
    cairo_show_text(cr, "1 TO 18");
    // even
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);  
    cairo_rectangle(cr, 2 * cell_width, 4 * cell_height, 2 * cell_width, cell_height);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, 2.25 * cell_width, 4.5 * cell_height);
    cairo_show_text(cr, "EVEN");
    // red
    cairo_set_source_rgb(cr, 1, 0.0, 0.0);  
    cairo_rectangle(cr, 4 * cell_width, 4 * cell_height, 2 * cell_width, cell_height);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, 4.5 * cell_width, 4.5 * cell_height);
    cairo_show_text(cr, "RED");
    // black
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);  // Dark gray
    cairo_rectangle(cr, 6 * cell_width, 4 * cell_height, 2 * cell_width, cell_height);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, 6.1 * cell_width, 4.5 * cell_height);
    cairo_show_text(cr, "BLACK"); 
    // odd
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);  // Dark gray
    cairo_rectangle(cr, 8 * cell_width, 4 * cell_height, 2 * cell_width, cell_height);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, 8.3 * cell_width, 4.5 * cell_height);
    cairo_show_text(cr, "ODD");
    // 19 to 36
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);  // Dark gray
    cairo_rectangle(cr, 10 * cell_width, 4 * cell_height, 2 * cell_width, cell_height);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, 10 * cell_width, 4.5 * cell_height);
    cairo_show_text(cr, "19 TO 36");

    cairo_set_line_width(cr, 2.0);
    
    // outlines of betting table.
    for( int i = 0; i <= 5; i++) {

        // draw lines for first 3 rows.
        if(i <= 3) {

            // horizontal lines (1 to 3 rows). 
            cairo_move_to(cr, 0, i * cell_height);
            cairo_line_to(cr, 13 * cell_width, i * cell_height); // Adjust according to the number of columns
            cairo_stroke(cr);
        
            // vertical lines (1 to 3 rows).
            for(int j = 0; j < 14; j++) {
                cairo_move_to(cr, j * cell_width, 0);
                cairo_line_to(cr, j * cell_width, i * cell_height);
                cairo_stroke(cr);
            }
        }

        else {
            // horizontal lines (4th and 5th row)
            cairo_move_to(cr, 0, i * cell_height);
            cairo_line_to(cr, 12 * cell_width, i * cell_height); // Adjust according to the number of columns
            cairo_stroke(cr);

            // vertical lines (4th row)
            if(i == 4) {

                for(int k = 0; k <= 3; k++) {
                cairo_move_to(cr, k * 4 * cell_width, i * cell_height);
                cairo_line_to(cr, k * 4 * cell_width, (i - 1) * cell_height);
                cairo_stroke(cr);
                }
            }

            // vertical lines (5th row)
            if(i == 5) {

                for(int k = 0; k <= 6; k++) {
                cairo_move_to(cr, k * 2 * cell_width, i * cell_height);
                cairo_line_to(cr, k * 2 * cell_width, (i - 1) * cell_height);
                cairo_stroke(cr);
                }
            }

        }
    }     



    return FALSE;
}

/*
Function to update wheel angle and simulate the spin of the wheel using sine function as a multiplier on the angle.

*/
// int main(int argc, char *argv[]) {
    
//     // try to initiate gtk library, if unsuccessful then exit.
//     if (!gtk_init_check(&argc, &argv)) {
//         fprintf(stderr, "Failed to initialize GTK\n");
//         return 1;
//     }
    
//     printf("GTK initialized\n");
    
//     // create window. if unsuccessful then exit.
//     GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//     if (!window) {
//         fprintf(stderr, "Failed to create window\n");
//         return 1;
//     }
    
//     printf("Window created\n");
    
//     // create drawing widget.
//     GtkWidget *drawing_area = gtk_drawing_area_new();
//     if (!drawing_area) {
//         fprintf(stderr, "Failed to create drawing area\n");
//         return 1;
//     }
    
//     printf("Drawing area created\n");
    
    
//     // set size of widgets.
//     gtk_widget_set_size_request(drawing_area, 400, 300);
//    // connect signal to interaction.
//    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw_table), NULL);
   
//     // addd drawing widget to window widget.
//     gtk_container_add(GTK_CONTAINER(window), drawing_area);
    

    

//     // connect signal to user interaction to exit.
//     g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
//     // visualize all widgets.
//     gtk_widget_show_all(window);
    
//     printf("Starting main loop\n");
//     gtk_main();
    
//     printf("Main loop ended\n");
    
    
    
//     return 0;
// }


/*
* function that creates and returns the roulette betting table. 
*/
GtkWidget* create_roulette_table(void) {
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 400, 200);

    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw_table), NULL);
    return drawing_area;
}

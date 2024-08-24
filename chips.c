#include <gtk/gtk.h>
#include <math.h>
#include <stdio.h>
#include "wheel.h"

gboolean on_draw_chips(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    
    int con = -17;
    // Set background color (green)
    cairo_set_source_rgb(cr, 0.25, 0.5, 0.25);
    cairo_paint(cr);

    // Set up dimensions
    int width = 400;
    int height = 100;
    int cell_width = (width / 5);  // 12 number columns + 1 for 0
    //int cell_height = height - 10;  // 3 number rows + 1 for additional bets

    // Draw number grid
    for (int i = 0; i < 5; i++) {
        const char *chip_values[] = {"250", "100", "25", "5", "1"};

        cairo_move_to(cr, i * cell_width, height / 2); // Move to location.
        cairo_set_source_rgb(cr, 0.6, 0.6, 0.6);
        cairo_arc(cr, i * cell_width + cell_width /2, height / 2, (cell_width/2 - 10), 0, 2 * M_PI); // Draw the wheel
        cairo_close_path(cr); // Close the path to the center
        cairo_fill(cr); // Fill the segment
        // Add number text

        // outline
        cairo_set_line_width(cr, 2); // Width of the outline
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_arc(cr, i * cell_width + cell_width /2, height / 2, (cell_width/2 - 10), 0, 2 * M_PI);
        cairo_stroke(cr);


        // text
        cairo_set_source_rgb(cr, 0, 0, 0);  // White text
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 20);
    
        cairo_move_to(cr, (i * cell_width + cell_width /2) + con, height / 2 + 5);
        cairo_show_text(cr, chip_values[i]);

        con += 3;
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
//     gtk_widget_set_size_request(drawing_area, 400, 100);
//    // connect signal to interaction.
//    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw_chips), NULL);
   
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

GtkWidget* create_roulette_chips(void) {
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 400, 100);

    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw_chips), NULL);
    return drawing_area;
}
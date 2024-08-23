/* 
-----------------------------------------------------
used in demo

-----------------------------------------------------
*/
#include <gtk/gtk.h>
#include <math.h>
#include <stdio.h>
#include "wheel.h"

#define WHEEL_SIZE 400


/*
Function to create the draw object. 

Parameters (from left to right): 
(1). pointer to the widget being drawn.
(2). pointer to object used to perform drawing operations.
(3). pointer to pass custom data to the callback function.
*/
gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    
    int roulette_numbers[] = {0, 32, 15, 19, 4, 21, 2, 25, 17, 34, 6, 27, 13, 36, 11, 30, 8, 23, 10, 5, 24, 16, 33, 1, 20, 14, 31, 9, 22, 18, 29, 7, 28, 12, 35, 3, 26};
    // create pointer to a casted parameter variable.
    WheelState *state = (WheelState*)user_data;
    
    // print to console.
    printf("Drawing wheel. Angle: %f\n", state->angle);
    
    // call cairo function(s) to set background color.
    cairo_set_source_rgb(cr, 0.25, 0.5, 0.25);
    cairo_paint(cr);
    
    // call cairo function to move wheel to the center of the drawing area.
    cairo_translate(cr, WHEEL_SIZE/2, WHEEL_SIZE/2);
    
    // call cairo function to rotate wheel based on current angle stored in structure variable.
    cairo_rotate(cr, state->angle);
    
    // Add font for numbers.
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 20);

    for (int i = 0; i < 37; i++) {
        
        // set to black 
        if (i % 2 == 0) {
            cairo_set_source_rgb(cr, 0, 0, 0);
        }
        // set to red
        if (i % 2 != 0) {
            cairo_set_source_rgb(cr, 1, 0, 0);
        }
        // set first slice as green
        if(i == 0) {
            cairo_set_source_rgb(cr, 0.25, 1, 0.25);
        }

        cairo_move_to(cr, 0, 0); // move to center of drawing area
        cairo_arc(cr, 0, 0, WHEEL_SIZE/2 - 10, i * 2 * M_PI / 37, (i + 1) * 2 * M_PI / 37); // draw the section of the circle.
        cairo_close_path(cr);
        cairo_fill(cr);

        // line in roulette table
        // cairo_set_source_rgb(cr, 1, 0, 1); //set color back to white
        // cairo_move_to(cr, 0, 0); // move to orgin of drawing area
        // cairo_line_to(cr, 0, WHEEL_SIZE/2 - 10, i * 2 M_PI / 37, (i + 1) * 2 * M_PI /37); // draw line to arc of circle.
        // cairo_stroke(cr); // color.

        // Draw the number for the current slot
        double angle = (i + 0.5) * 2 * M_PI / 37; // Center of the slice
        //double text_radius = WHEEL_SIZE / 2 - 30; // Adjust as needed
        double text_x = (WHEEL_SIZE / 2 - 30) * cos(angle);
        double text_y = (WHEEL_SIZE / 2 - 30) * sin(angle);

        cairo_save(cr);

        // Move to the text position
        cairo_translate(cr, text_x, text_y);

        // Rotate the text to face the center
        cairo_rotate(cr, angle + M_PI / 2); // Add PI/2 to make text perpendicular to radius

        // Set text color (white in this case)
        cairo_set_source_rgb(cr, 1, 1, 1);

        // Draw the text
        char num_str[3];
        snprintf(num_str, sizeof(num_str), "%d", roulette_numbers[i]);
        
        // Center the text
        cairo_text_extents_t extents;
        cairo_text_extents(cr, num_str, &extents);
        cairo_move_to(cr, -extents.width / 2, extents.height / 2);

        cairo_show_text(cr, num_str);

        // Restore the context state
        cairo_restore(cr);
    }
    
    // create hallow  wheel inside roulette wheel.
    cairo_move_to(cr, 0, 0); // Move to center of the wheel
    cairo_set_source_rgb(cr, 0.25, 0.5, 0.25);
    cairo_arc(cr, 0, 0, (WHEEL_SIZE/2 - 10) / 2, 0, 2 * M_PI); // Draw the segment of the wheel
    cairo_close_path(cr); // Close the path to the center
    cairo_fill(cr); // Fill the segment

    // Set the outline color and width.
    cairo_set_line_width(cr, 2); // Width of the outline
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_arc(cr, 0, 0, (WHEEL_SIZE/2 - 10) / 2, 0, 2 * M_PI);
    cairo_stroke(cr);
    cairo_arc(cr, 0, 0, (WHEEL_SIZE/2 - 10), 0, 2 * M_PI);
    cairo_stroke(cr);

    cairo_arc(cr, 0, 0, (WHEEL_SIZE/2 - 45), 0, 2 * M_PI);
    cairo_stroke(cr);
    
    return FALSE;
}
/*
Function to update wheel angle and simulate the spin of the wheel using sine function as a multiplier on the angle.

Visual: 
    1 |* *     
      |     *             
      |       *          
      |         *       
    0 |          *        
      ------------|------------|
      0         pi/2           pi    

The function works by using the natural behaviour
of the sine wave to create a smooth deceleration.

The way it works is we know cos(0) = 1 and cos(pi/2) = 0
so we will use cos as a multiplier to the angle to act 
as speed. This means we must increment x (in this case 
x = spin duration) to go from 0 to pi/2. 0 meaning full speed
and 1 being the wheel is at a dead stop. The value to increment
will be based on the refresh rate so that we can have a smooth
spinning animation so taking 16 miliseconds per refresh we can 
make it increment by 0.016. 
*/
gboolean update_wheel(gpointer user_data) {

    WheelState *state = (WheelState*)user_data;


    if (state && state->spinning) {
        
        // calculate the current speed of the spin by using cosine of the spin_duration.
        double current_speed = cos(state->spin_duration);

        // Ensure current_speed is non-negative, since it is based on cos function heading toward pi/2.
        if (current_speed < 0) {
            current_speed = 0;
            state->spinning = 0;  // Stop spinning when speed drops to zero
        }
        // adjust angle speed by multiplying with speed variable (from full angle rotation to 0)
        double new_angle = state->angle * current_speed;
        
        //The increment value of 0.016 seconds corresponds to the 16 milliseconds 
        state->spin_duration += 0.016;
        
        // increment and store new angle into structure.
        state->angle += new_angle;

        //make sure the angle is within range (0 to 2*PI)
        if (state->angle > 2 * M_PI) {
            state->angle -= 2 * M_PI;
        }
        printf("Updating wheel. Angle: %f\n", state->angle);
        if (state->drawing_area) {
            gtk_widget_queue_draw(state->drawing_area);
        }

    }

    else {

        state->angle += state->angle;

    }
    return TRUE;  // Always return TRUE to keep the timer running
}

/*
 create the wheel and return it to the main file.
*/
GtkWidget* create_roulette_wheel(void) {

    // Seed the random number generator once in main
    srand(time(NULL));
    
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, WHEEL_SIZE, WHEEL_SIZE);
    
  // set up the wheel variables.
    WheelState *state = g_new(WheelState, 1);
    state->angle = 0.03;
    state->spinning = 1;
    state->spin_duration = (M_PI / 2) * ((double) rand() / RAND_MAX);
    state->drawing_area = drawing_area;

    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw), state);
    g_timeout_add(16, update_wheel, state);

    return drawing_area;
}

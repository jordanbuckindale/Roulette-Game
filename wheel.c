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
Function to trigger the wheel to spin.
 */
void trigger_wheel_spin(WheelState *state) {

    if(state->spin_state == 0) {
        
        state->spin_state = 1;
        state->spinning = 1;
        state->spin_duration = 0;
        state->initial_speed = 0.2;

    }
}

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

        // Draw the number for the current slot
        double angle = (i + 0.5) * 2 * M_PI / 37; // Center of the slice
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

    switch(state->spin_state) {
        case 0: // Slow constant spin
            state->angle += 0.25 * (M_PI / 180); // 0.25 degrees per update
            break;
        case 1: // Fast spin
            if (state->spinning) {
                double current_speed = state->initial_speed * cos(state->spin_duration);
                if (current_speed < 0.01) {
                    state->spin_state = 2;
                    state->spinning = 0;
                } else {
                    state->angle += current_speed;
                    state->spin_duration += 0.016;
                }
            }
            break;
        case 2: // Stopping
            if (state->angle < 0.01) {
                state->spin_state = 0;
                state->angle = 0;
            } else {
                state->angle *= 0.95; // Gradually slow down
            }
            break;
    }

    // Normalize angle
    while (state->angle >= 2 * M_PI) {
        state->angle -= 2 * M_PI;
    }

    if (state->drawing_area) {
        gtk_widget_queue_draw(state->drawing_area);
    }

    return TRUE;
}

/*
 create the wheel and return it to the main file.
*/
GtkWidget* create_roulette_wheel(void) {
    // Create a new drawing area
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, WHEEL_SIZE, WHEEL_SIZE);
    
    // Initialize the wheel state
    WheelState *state = g_new(WheelState, 1);
    state->angle = 0;
    state->spinning = 0;
    state->spin_duration = 0;
    state->initial_speed = 0;
    state->drawing_area = drawing_area;
    state->spin_state = 0; // Start with slow spin

    // Associate the state with the drawing area
    g_object_set_data_full(G_OBJECT(drawing_area), "wheel_state", state, g_free);

    // Connect the draw signal
    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw), state);

    // Set up a timer to update the wheel
    g_timeout_add(16, update_wheel, state);

    return drawing_area;
}

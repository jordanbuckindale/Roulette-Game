#ifndef WHEEL_H
#define WHEEL_H

#include <gtk/gtk.h>

typedef struct {
    double angle;
    int spinning;
    double initial_speed;
    double spin_duration;
    GtkWidget *drawing_area;
    int spin_state;
    double ball_angle;
    double ball_speed;
} WheelState;

typedef struct {
    GtkWidget *drawing_area; //-> *drawing_area (GTK widget pointer)
} betting_table;


// WHEEL.C
GtkWidget* create_roulette_wheel(void);
gboolean update_wheel(gpointer user_data);

// BETS.C 
GtkWidget* create_roulette_table(void);

// CHIPS.C
GtkWidget* create_roulette_chips(void);

#endif // WHEEL_H

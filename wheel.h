#ifndef WHEEL_H
#define WHEEL_H

#include <gtk/gtk.h>

typedef struct {
    double angle;
    int spinning;
    double initial_speed;
    double spin_duration;
    GtkWidget *drawing_area;
} WheelState;

typedef struct {
    GtkWidget *drawing_area; //-> *drawing_area (GTK widget pointer)
} betting_table;

GtkWidget* create_roulette_wheel(void);
gboolean update_wheel(gpointer user_data);

GtkWidget* create_roulette_table(void);

#endif // WHEEL_H
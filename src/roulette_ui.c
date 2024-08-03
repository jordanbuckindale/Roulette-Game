#include "roulette_ui.h"
#include <gtk/gtk.h>

struct _RouletteUI {
    GtkWidget *window;
    GtkWidget *wheel_area;
    GtkWidget *table_area;
    // Other UI elements...
    GList *bet_spots;
};

RouletteUI* roulette_ui_new(void) {
    RouletteUI *ui = g_new(RouletteUI, 1);
    // Initialize UI elements...
    return ui;
}

void roulette_ui_show(RouletteUI *ui) {
    gtk_widget_show_all(ui->window);
}

void roulette_ui_free(RouletteUI *ui) {
    // Free allocated resources...
    g_free(ui);
}

// Other UI-related functions...

#include <gtk/gtk.h>
#include "wheel.h"

typedef struct {
    GtkWidget *window;
    GtkWidget *wheel_area;
    GtkWidget *table_area;
    GtkWidget *balance_label;
    GtkWidget *winnings_label;
    GtkWidget *bet_total_button;
    GtkWidget *place_bet_button;
    GtkWidget *chip_buttons[5];
    // Add other necessary components
} RouletteUI;

static void create_chip_buttons(RouletteUI *ui, GtkGrid *grid) {
    const char *chip_values[] = {"250", "100", "25", "5", "1"};
    for (int i = 0; i < 5; i++) {
        ui->chip_buttons[i] = gtk_button_new_with_label(chip_values[i]);
        gtk_grid_attach(grid, ui->chip_buttons[i], i, 4, 1, 1);
        // Connect click handlers and style the buttons
    }
}


static void setup_ui(RouletteUI *ui) {
    ui->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(ui->window), "Roulette Game");
    gtk_container_set_border_width(GTK_CONTAINER(ui->window), 10);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(ui->window), grid);


    // Roulette Wheel
    //ui->wheel_area = draw_roulette_wheel_new();
    ui->wheel_area = create_roulette_wheel();
    gtk_grid_attach(GTK_GRID(grid), ui->wheel_area, 0, 0, 2, 3);

    // Betting Table
    //ui->table_area = gtk_drawing_area_new();
    ui->table_area = create_roulette_table();
    gtk_widget_set_size_request(ui->table_area, 400, 200);
    gtk_grid_attach(GTK_GRID(grid), ui->table_area, 2, 0, 3, 1.5);

    // Labels
    
    ui->balance_label = create_roulette_chips();
    gtk_widget_set_size_request(ui->balance_label, 400, 100);
    gtk_grid_attach(GTK_GRID(grid), ui->balance_label, 2, 1.5, 3, 2);

    // ui->winnings_label = gtk_label_new("Winnings: $0");
    // gtk_grid_attach(GTK_GRID(grid), ui->winnings_label, 4, 2, 1, 1);

    // Buttons 
    ui->bet_total_button = gtk_button_new_with_label("Bet Total: $0");
    
    gtk_grid_attach(GTK_GRID(grid), ui->bet_total_button, 2, 3, 1, 1);

    ui->place_bet_button = gtk_button_new_with_label("Place Bet");
    gtk_grid_attach(GTK_GRID(grid), ui->place_bet_button, 4, 3, 1, 1);

    // Chip Buttons
    create_chip_buttons(ui, GTK_GRID(grid));

    // Connect signals and set up drawing callbacks
    // ...

    gtk_widget_show_all(ui->window);
}

int main(int argc, char *argv[]) {
    
    if (!gtk_init_check(&argc, &argv)) {
        fprintf(stderr, "Failed to initialize GTK\n");
        return 1;
    }

    RouletteUI ui;
    setup_ui(&ui);
    
    g_signal_connect(ui.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_main();
    return 0;
}

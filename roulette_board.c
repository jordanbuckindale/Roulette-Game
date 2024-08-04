/* 
-----------------------------------------------------
Jordan Buckindale
Date: July 28 2024

Overview:
This program is an implementation of the GTK
library to create a roulette board.

To Do: 
(1) - 
(2) - 
(3) - 
(4) - 

-----------------------------------------------------
*/
#include <gtk/gtk.h>
#include <math.h>
#include <stdio.h>

typedef struct {
    GtkWidget *window; // pointer to main window widget.
    GtkWidget *wheel_area;
    GtkWidget *table_area;
    GtkWidget *balance_label;
    GtkWidget *winnings_label;
    GtkWidget *bet_total_button;
    GtkWidget *place_bet_button;
    GtkWidget *chips_buttons[5];
} RouletteUI;

static void create_chip_buttons(RouletteUI *ui, GtkGrid *grid) {
    const char *chip_values[] = {"250", "100", "25", "5", "1"};
    for(int i = 0; i < 5; i++) {
        ui->chips_buttons[i] = gtk_button_new_with_label(chip_values[i]);
        gtk_grid_attach(GTK_GRID(grid), ui->chips_buttons[i], i, 4, 1, 1);
    }
}

/* Function that will be called whenever user clicks button 'click me'. */
static void on_button_clicked(GtkWidget *button, gpointer user_data) {
    
    // output.
    g_print("Button clicked\n"); // prints button clicked to the terminal.
}

/* Creates roulette betting table. */
static void setup_ui(RouletteUI *ui) {
    // initialize the gtk window for the application structure.
    ui->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    // set title.
    gtk_window_set_title(GTK_WINDOW(ui->window), "Roulette Game");
    // set border width.
    gtk_container_set_border_width(GTK_CONTAINER(ui->window), 10);
    // set default window size
    // gtk_window_set_default_size(GTK_WINDOW(ui->window), 800, 600);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(ui->window), grid);

    // Set spacing between grid cells
    // gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    // gtk_grid_set_column_spacing(GTK_GRID(grid), 10);


    // roulette wheel.
    ui->wheel_area = gtk_label_new("Roulette Wheel");
    gtk_grid_attach(GTK_GRID(grid), ui->wheel_area, 0, 0, 2, 3);

    // betting table.
    ui->table_area = gtk_label_new("Roulette Table");
    gtk_grid_attach(GTK_GRID(grid), ui->table_area, 2, 0, 3, 2);

    ui->balance_label = gtk_label_new("Balance: $1000");
    gtk_grid_attach(GTK_GRID(grid), ui->balance_label, 2, 2, 1, 1);

    ui->winnings_label = gtk_label_new("Winnings: $0");
    gtk_grid_attach(GTK_GRID(grid), ui->winnings_label, 4, 2, 1, 1);

    // Buttons
    ui->bet_total_button = gtk_button_new_with_label("Bet Total: $0");
    gtk_grid_attach(GTK_GRID(grid), ui->bet_total_button, 2, 3, 1, 1);

    ui->place_bet_button = gtk_button_new_with_label("Place Bet");
    gtk_grid_attach(GTK_GRID(grid), ui->place_bet_button, 4, 3, 1, 1);

    // Chip Buttons
    create_chip_buttons(ui, GTK_GRID(grid));

    // Connect signals and set up drawing callbacks
    /// connect signals.
    g_signal_connect(ui->place_bet_button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    // connects the action of user exiting or 'destroying' the window to the function 'gtk_main_quit' which will then exit the GTK loop.
    g_signal_connect(ui->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(ui->window);
}

/* runs program for roulette betting table application. */
int main(int argc, char *argv[]) {
    // initializes the GTK library.
    gtk_init(&argc, &argv);

    RouletteUI ui;
    setup_ui(&ui);

    gtk_main();
    // recursive loop which waits for user event (like button click) and triggers correct callback function.

    return 0;
    // exit program.
}
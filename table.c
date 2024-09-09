#include <gtk/gtk.h>
#include "wheel.h"
#include "logic.c"

typedef struct {
    GtkWidget *window;
    GtkWidget *wheel_area;
    GtkWidget *table_area;
    GtkWidget *chips_area;
    GtkWidget *balance_label;
    GtkWidget *bet_total_label;
    GtkWidget *result_label;
    int balance;
    int current_bet;
    int current_bet_type;
    int current_bet_value;
} RouletteUI;


static void on_table_click(GtkWidget *widget, GdkEventButton *event, gpointer user_data) {
    //RouletteUI *ui = (RouletteUI*)user_data;
    
    // Implement logic to handle clicks on the betting table
    // Update current_bet_type and current_bet_value based on where the user clicked
    // Update the bet_total_label
}

static void on_spin_clicked(GtkButton *button, gpointer user_data) {
    RouletteUI *ui = (RouletteUI*)user_data;
    WheelState *wheel_state = g_object_get_data(G_OBJECT(ui->wheel_area), "wheel_state");
    
    // temporary fix to spin wheel until betting system is created.
    trigger_wheel_spin(wheel_state);
    
    /*
    if (wheel_state && ui->current_bet > 0) {
        trigger_wheel_spin(wheel_state);
        
        int winning_number = spin_wheel();
        int result = evaluate_bet(ui->current_bet_type, ui->current_bet_value, winning_number);
        
        if (result > 0) {
            update_balance(&ui->balance, ui->current_bet, result);
            gtk_label_set_text(GTK_LABEL(ui->result_label), "You won!");
        } else {
            update_balance(&ui->balance, ui->current_bet, -1);
            gtk_label_set_text(GTK_LABEL(ui->result_label), "You lost.");
        }
        
        char balance_text[50];
        snprintf(balance_text, sizeof(balance_text), "Balance: $%d", ui->balance);
        gtk_label_set_text(GTK_LABEL(ui->balance_label), balance_text);
        
        ui->current_bet = 0;
        gtk_label_set_text(GTK_LABEL(ui->bet_total_label), "Current Bet: $0");
    }
    */
}

static void setup_ui(RouletteUI *ui) {
    ui->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(ui->window), "Roulette Game");
    gtk_container_set_border_width(GTK_CONTAINER(ui->window), 10);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(ui->window), grid);

    ui->balance = 1000;  // Starting balance
    ui->current_bet = 0;
    ui->current_bet_type = -1;
    ui->current_bet_value = -1;

    char balance_text[50];
    snprintf(balance_text, sizeof(balance_text), "Balance: $%d", ui->balance);
    ui->balance_label = gtk_label_new(balance_text);
    gtk_grid_attach(GTK_GRID(grid), ui->balance_label, 2, 1, 1, 1);
    
    ui->bet_total_label = gtk_label_new("Current Bet: $0");
    gtk_grid_attach(GTK_GRID(grid), ui->bet_total_label, 3, 1, 1, 1);
    
    GtkWidget *spin_button = gtk_button_new_with_label("Spin");
    gtk_grid_attach(GTK_GRID(grid), spin_button, 4, 2, 1, 1);
    g_signal_connect(spin_button, "clicked", G_CALLBACK(on_spin_clicked), ui);
    
    g_signal_connect(ui->table_area, "button-press-event", G_CALLBACK(on_table_click), ui);
   
    ui->chips_area = create_roulette_chips();
    gtk_widget_set_size_request(ui->chips_area, 400, 100);
    gtk_grid_attach(GTK_GRID(grid), ui->chips_area, 2, 2, 2, 1);
    
    // Roulette Wheel
    //ui->wheel_area = draw_roulette_wheel_new();
    ui->wheel_area = create_roulette_wheel();
    gtk_grid_attach(GTK_GRID(grid), ui->wheel_area, 0, 0, 2, 3);

    // Betting Table
    //ui->table_area = gtk_drawing_area_new();
    ui->table_area = create_roulette_table();
    gtk_widget_set_size_request(ui->table_area, 400, 200);
    gtk_grid_attach(GTK_GRID(grid), ui->table_area, 2, 0, 3, 1);

    // Connect signals and set up drawing callbacks
    // ...

    gtk_widget_show_all(ui->window);
}

int main(int argc, char *argv[]) {
    
    if (!gtk_init_check(&argc, &argv)) {
        fprintf(stderr, "Failed to initialize GTK\n");
        return 1;
    }
    
    srand(time(NULL));  // Initialize random number generator
    initialize_roulette_numbers();

    RouletteUI ui;
    setup_ui(&ui);
    
    g_signal_connect(ui.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_main();
    return 0;
}

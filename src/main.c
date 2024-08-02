/* 
-----------------------------------------------------
Jordan Buckindale
Date: August 1 2024

Main program to run program.

To Do:
(1) - implement roulette_ui_new();
(2) - implement roulette_ui_free(ui);
-----------------------------------------------------
*/

#include <gtk/gtk.h>
#include "roulette_ui.h"

int main(int argc, char *argv[]) {
    
  gtk_init(&argc, &argv);

  RouletteUI *ui = roulette_ui_new();
  roulette_ui_show(ui);
  gtk_main();

  roulette_ui_free(ui);
  return 0;
}

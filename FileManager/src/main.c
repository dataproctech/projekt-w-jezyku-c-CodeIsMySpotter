#include <gtk/gtk.h>
#include "main_window.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWindow *window = create_window("FileManager", 1200, 800);
    if (!window) return 1;

    show_window(window);
    gtk_main();


    return 0;
}

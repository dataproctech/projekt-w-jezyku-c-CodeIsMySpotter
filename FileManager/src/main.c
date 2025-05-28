#include <gtk/gtk.h>
#include "main_window.h"
#include "system_utils.h"

void app(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWindow *window = create_window("FileManager", 1200, 800);
    if (!window) return;

    show_window(window);
    gtk_main();

}





int main(int argc, char *argv[]) {
    app(argc, argv);   

    return 0;
}
#include <GTK/gtk.h>
#include <stdio.h>
#include <stdlib.h>







int main() {

    // Initialize GTK
    gtk_init(NULL, NULL);
    // Create a new window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "File Manager");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    gtk_window_set_icon_from_file(GTK_WINDOW(window), "icon.png", NULL);
    // Connect the destroy event to close the application
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);


    // start event loop
    gtk_widget_show_all(window);
    gtk_main();
    // Clean up and exit
    gtk_widget_destroy(window);
    gtk_main_quit();
    // Free any resources if needed
    return 0;
}
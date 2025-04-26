#include <GTK/gtk.h>
#include <window_utils.h>




GTKWindow *create_window(const char *title, int width, int height) {
    GTKWindow *window = (GTKWindow *)malloc(sizeof(GTKWindow));
    if (!window) {
        fprintf(stderr, "Failed to allocate memory for window\n");
        return NULL;
    }
    
    window->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window->window), title);
    gtk_window_set_default_size(GTK_WINDOW(window->window), width, height);
    gtk_window_set_position(GTK_WINDOW(window->window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window->window), TRUE);
    gtk_window_set_icon_from_file(GTK_WINDOW(window->window), "icon.png", NULL);

    g_signal_connect(window->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    return window;
}   
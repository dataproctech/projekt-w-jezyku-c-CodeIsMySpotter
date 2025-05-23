#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>

#include "navbar.h"
#include "side_bar.h"
#include "main_content.h"

// Declarations

static inline void create_main_window(GtkWindow *window);
static inline GtkWindow *create_window(const char *title, int width, int height);
static inline void show_window(GtkWindow *window);

// Function Definitions

static inline GtkWindow *create_window(const char *title, int width, int height) {
    GtkWindow *window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
    gtk_widget_set_name(GTK_WIDGET(window), "main-window");
    gtk_window_set_title(window, title);
    gtk_window_set_default_size(window, width, height);
    gtk_window_set_position(window, GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(window, TRUE);
    gtk_window_set_decorated(window, FALSE); 

    g_object_set_data(G_OBJECT(window), "path", g_strdup(""));


    if (!gtk_window_set_icon_from_file(window, "assets/Icon.png", NULL)) {
        fprintf(stderr, "Warning: Could not load icon.png\n");
    }
    create_main_window(window);

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "./src/file.css", NULL);
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);


    return window;
}

void create_main_window(GtkWindow *window) {
    
    GtkWidget *frame = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), frame);
    
    GtkWidget *navbar = add_navbar_to_window(window);
    GtkWidget *main_content = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    g_object_set_data(G_OBJECT(window), "main-content", main_content);
    GtkWidget *sidebar = add_sidebar_to_window(window); 
    GtkWidget *main_area = create_main_content(window);
    
    
    gtk_widget_set_name(frame, "window-frame");

    gtk_box_pack_start(GTK_BOX(frame), navbar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(frame), main_content, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(main_content), main_area, TRUE, TRUE, 0);
}





static inline void show_window(GtkWindow *window) {
    if (window) {
        gtk_widget_show_all(GTK_WIDGET(window));
    }
}



static inline void set_window_size(GtkWindow *window, int width, int height) {
    if (window) {
        gtk_window_set_default_size(window, width, height);
    }
}


#endif
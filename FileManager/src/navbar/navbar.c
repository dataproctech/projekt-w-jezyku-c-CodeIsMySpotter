#include "navbar.h"
#include "navbar_icon.h"
#include <gtk/gtk.h>

GtkWidget *add_navbar_to_window(GtkWindow *window) {
    GtkWidget *navbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(navbar, "navbar");
    gtk_widget_set_hexpand(navbar, TRUE);
    
    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
    gtk_widget_set_margin_end(button_box, 8);
    
    
    create_icon(navbar);
    create_min_btn(window, button_box);
    create_close_btn(window, button_box);

    
    gtk_box_pack_end(GTK_BOX(navbar), button_box, FALSE, FALSE, 0);


    return navbar;
}


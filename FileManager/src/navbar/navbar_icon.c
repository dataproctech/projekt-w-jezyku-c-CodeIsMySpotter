#include "navbar_icon.h"

void create_icon(GtkWidget *navbar) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("assets/icon.png", 40, 40, TRUE, NULL);
    GtkWidget *icon = gtk_image_new_from_pixbuf(pixbuf);

    gtk_widget_set_margin_start(icon, 8);
    gtk_widget_set_margin_top(icon, 4);
    gtk_widget_set_margin_bottom(icon, 4);

    gtk_box_pack_start(GTK_BOX(navbar), icon, FALSE, FALSE, 0);
    g_object_unref(pixbuf);
    
}
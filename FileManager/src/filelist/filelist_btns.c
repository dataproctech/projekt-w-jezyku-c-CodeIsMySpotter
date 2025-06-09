#include "filelist_btns.h"
#include <gtk/gtk.h>


GtkWidget *create_icon_from_file(const char *filepath, int width, int height) {
    GError *error = NULL;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filepath, &error);
    if (!pixbuf) {
        g_warning("Failed to load icon from %s: %s", filepath, error->message);
        g_error_free(error);
        return gtk_image_new(); 
    }

    GdkPixbuf *scaled = gdk_pixbuf_scale_simple(pixbuf, width, height, GDK_INTERP_BILINEAR);
    g_object_unref(pixbuf);  

    GtkWidget *image = gtk_image_new_from_pixbuf(scaled);
    g_object_unref(scaled);  

    return image;
}



GtkWidget *create_entry_button(const char *filename, gboolean is_file) {
    gchar *utf8_filename = g_locale_to_utf8(filename, -1, NULL, NULL, NULL);
    if (!utf8_filename) {
        utf8_filename = g_strdup(filename);
    }

    GtkWidget *button = gtk_button_new();
    gtk_widget_set_name(button, "entry-button");

    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);

    GtkWidget *icon;
    if (is_file) {
        icon = create_icon_from_file("assets/File.png", 35, 35);
    } else {
        icon = create_icon_from_file("assets/DirectoryIcon.png", 35, 35);
    }

    GtkWidget *label = gtk_label_new(utf8_filename);
    gtk_label_set_xalign(GTK_LABEL(label), 0.0); 

    gtk_box_pack_start(GTK_BOX(hbox), icon, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), label, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(button), hbox);

    gtk_widget_show_all(button);

    g_free(utf8_filename);
    return button;
}

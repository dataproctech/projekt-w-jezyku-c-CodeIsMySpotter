#include "pathlabel.h"
#include <gtk/gtk.h>


void create_path_label(GtkWindow *window, GtkWidget *container)
{
    const char *path = g_object_get_data(G_OBJECT(window), "path");

    GtkWidget *path_label = gtk_label_new(path);
    gtk_widget_set_name(path_label, "path-label");
    g_object_set_data(G_OBJECT(window), "path-label", path_label);

    gtk_box_pack_start(GTK_BOX(container), path_label, FALSE, FALSE, 0);
}
#include <gtk/gtk.h>

static inline void create_list(GtkWidget *container);


static inline void create_list(GtkWidget *container)
{

    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_name(scrolled_window, "scrolled-window");
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    GtkWidget *vertical_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(vertical_box, "list");

    gtk_container_add(GTK_CONTAINER(scrolled_window), vertical_box);
    gtk_box_pack_start(GTK_BOX(container), scrolled_window, TRUE, TRUE, 0);
}
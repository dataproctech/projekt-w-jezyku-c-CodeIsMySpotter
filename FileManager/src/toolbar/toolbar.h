#include <gtk/gtk.h>
#include "toolbar_btns.h"

static inline void create_toolbar(GtkWindow *window, GtkWidget *container)
{
    GtkWidget *toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(toolbar, "toolbar");
    gtk_widget_set_hexpand(toolbar, TRUE);

    create_go_back_btn(toolbar);
    create_create_new_folder_btn(toolbar);
    create_filter_by_btn(toolbar);
    create_find_btn(toolbar);

    gtk_box_pack_start(GTK_BOX(container), toolbar, FALSE, FALSE, 0);
}
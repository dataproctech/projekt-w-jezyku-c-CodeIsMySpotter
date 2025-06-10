#include "filelist.h"
#include "filelist_btns.h"
#include "../utils/runtime_utils.h"
#include "../utils/system_utils.h"

#include <gtk/gtk.h>


void on_click_update_path_label() {

}

void update_filelist(gpointer user_data){
    GtkWindow *window = GTK_WINDOW(user_data);
    List *file_list = (List *)g_object_get_data(G_OBJECT(window), "file_list");
    GtkWidget *list_box = g_object_get_data(G_OBJECT(window), "file_list_widget");

        if (!file_list || !list_box) {
        g_warning("List or list widget is NULL.");
        return;
    }

    GList *children = gtk_container_get_children(GTK_CONTAINER(list_box));
    for (GList *child = children; child != NULL; child = child->next) {
        gtk_widget_destroy(GTK_WIDGET(child->data));
    }
    g_list_free(children);

    for (size_t i = 0; i < file_list->size; i++) {
        char *filename = (char *)file_list->items[i];

        gboolean is_file = strchr(filename, '.') != NULL;

        GtkWidget *button = create_entry_button(filename, is_file, window);



        gtk_box_pack_start(GTK_BOX(list_box), button, FALSE, FALSE, 2);
    }

    gtk_widget_show_all(list_box);
}



void create_list(GtkWidget *container, GtkWindow *window) {

    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_name(scrolled_window, "scrolled-window");
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);


    GtkWidget *vertical_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(vertical_box, "list");

    gtk_container_add(GTK_CONTAINER(scrolled_window), vertical_box);
    gtk_box_pack_start(GTK_BOX(container), scrolled_window, TRUE, TRUE, 0);

    g_object_set_data(G_OBJECT(window), "file_list_widget", vertical_box);
}

void create_entries(GtkWidget *list_container) {
    

}
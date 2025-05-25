#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>


static inline GtkWidget *create_main_content(GtkWindow *window);
static inline GtkWidget *create_vertical_box();

static inline void create_path_label(GtkWindow *window, GtkWidget *container);
static inline void create_toolbar(GtkWindow *window, GtkWidget *container);
static inline void create_list(GtkWidget *container);


static inline void on_go_back_clicked(GtkButton *button, gpointer user_data) {
    // Implement the functionality for going back
}

static inline void on_create_new_folder_clicked(GtkButton *button, gpointer user_data) {
    // Implement the functionality for creating a new folder
}

static inline void on_filter_by_clicked(GtkButton *button, gpointer user_data) {
    // Implement the functionality for filtering
}


static inline GtkWidget *create_main_content(GtkWindow *window) {

    GtkWidget *main_content_vertical = create_vertical_box();
    create_path_label(window, main_content_vertical);
    create_toolbar(window, main_content_vertical);
    create_list(main_content_vertical);
    
    return main_content_vertical;
}


static inline GtkWidget *create_vertical_box() {
    
    GtkWidget *vertical_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(vertical_box, "vertical-box");
    gtk_box_set_homogeneous(GTK_BOX(vertical_box), false);
    gtk_widget_set_margin_top(vertical_box, 20);
    gtk_widget_set_margin_end(vertical_box, 20);
    gtk_widget_set_margin_start(vertical_box, 20);

    return vertical_box;
}
  

static inline void create_list(GtkWidget *container) {

  GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
  gtk_widget_set_name(scrolled_window, "scrolled-window");
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  
  GtkWidget *vertical_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_name(vertical_box, "list");

  gtk_container_add(GTK_CONTAINER(scrolled_window), vertical_box);
  gtk_box_pack_start(GTK_BOX(container), scrolled_window, TRUE, TRUE, 0);

}



static inline void create_toolbar(GtkWindow *window, GtkWidget *container) {
  GtkWidget *toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_set_name(toolbar, "toolbar");
  gtk_widget_set_hexpand(toolbar, TRUE);

  GtkWidget *go_back_btn = gtk_button_new();
  gtk_widget_set_name(go_back_btn, "toolbar-btn");
  gtk_box_pack_start(GTK_BOX(toolbar), go_back_btn, FALSE, FALSE, 0);

  GtkWidget *create_new_folder_btn = gtk_button_new();
  gtk_widget_set_name(create_new_folder_btn, "toolbar-btn");
  gtk_box_pack_start(GTK_BOX(toolbar), create_new_folder_btn, FALSE, FALSE, 0);

  GtkWidget *filter_by_btn = gtk_button_new();
  gtk_widget_set_name(filter_by_btn, "toolbar-btn");
  gtk_box_pack_start(GTK_BOX(toolbar), filter_by_btn, FALSE, FALSE, 0);

  gtk_box_pack_start(GTK_BOX(container), toolbar, FALSE, FALSE, 0);

  
}

static inline void create_path_label(GtkWindow *window, GtkWidget *container) {
    const char *path = g_object_get_data(G_OBJECT(window), "path");
    
    GtkWidget *path_label = gtk_label_new(path);
    gtk_widget_set_name(path_label, "path-label");
    g_object_set_data(G_OBJECT(window), "path-label", path_label);

    gtk_box_pack_start(GTK_BOX(container), path_label, FALSE, FALSE, 0);    
}
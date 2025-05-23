#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>


static inline GtkWidget *create_vertical_box();
static inline GtkWidget *create_path_label(GtkWindow *window);
static inline GtkWidget *create_main_content(GtkWindow *window);
static inline GtkWidget *create_toolbar(GtkWindow *window);
static inline GtkWidget *create_list();


static inline GtkWidget *create_main_content(GtkWindow *window) {
    GtkWidget *main_content_vertical = create_vertical_box();
    GtkWidget *path_label = create_path_label(window);
    GtkWidget *toolbar = create_toolbar(window);
    GtkWidget *list = create_list();

    gtk_box_pack_start(GTK_BOX(main_content_vertical), path_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(main_content_vertical), toolbar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(main_content_vertical), list, TRUE, TRUE, 0);
  
    return main_content_vertical;
}


static inline GtkWidget *create_list() {
  GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
  gtk_widget_set_name(scrolled_window, "scrolled-window");
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  
  
  GtkWidget *vertical_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_name(vertical_box, "list");

  gtk_container_add(GTK_CONTAINER(scrolled_window), vertical_box);

  return scrolled_window;
}



static inline GtkWidget *create_toolbar(GtkWindow *window){
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

  return toolbar;
  
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

static inline GtkWidget *create_path_label(GtkWindow *window) {
    const char *path = g_object_get_data(G_OBJECT(window), "path");
    
    GtkWidget *path_label = gtk_label_new(path);
    gtk_widget_set_name(path_label, "path-label");
    g_object_set_data(G_OBJECT(window), "path-label", path_label);

    return path_label;
}
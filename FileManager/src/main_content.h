#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>

static inline GtkWidget *create_vertical_box(GtkWindow *window);
static inline GtkWidget *create_path_label(GtkWindow *window);
static inline GtkWidget *create_main_content(GtkWindow *window);
static inline GtkWidget *create_list(GtkWindow *window);


static inline GtkWidget *create_main_content(GtkWindow *window) {
    GtkWidget *main_content_vertical = create_vertical_box(window);
    GtkWidget *path_label = create_path_label(window);
    GtkWidget *list = create_list(window);

    gtk_box_pack_start(GTK_BOX(main_content_vertical), path_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(main_content_vertical), list, TRUE, TRUE, 0);
  
    return main_content_vertical;
}


static inline GtkWidget *create_list(GtkWindow *window) {
  GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
  gtk_widget_set_name(scrolled_window, "scrolled-window");
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  
  
  GtkWidget *vertical_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_name(vertical_box, "list");

  gtk_container_add(GTK_CONTAINER(scrolled_window), vertical_box);

  return scrolled_window;
}


static inline GtkWidget *create_vertical_box(GtkWindow *window) {
    

    GtkWidget *vertical_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(vertical_box, "vertical-box");
    gtk_box_set_homogeneous(GTK_BOX(vertical_box), false);
    gtk_widget_set_margin_top(vertical_box, 20);
    gtk_widget_set_margin_right(vertical_box, 20);
    gtk_widget_set_margin_left(vertical_box, 20);

  

    return vertical_box;
}

static inline GtkWidget *create_path_label(GtkWindow *window) {
    GtkWidget *path_label = gtk_label_new("Path: /home/user");
    gtk_widget_set_name(path_label, "path-label");

    return path_label;
}
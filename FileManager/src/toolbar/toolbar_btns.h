#ifndef TOOLBAR_BTNS_H
#define TOOLBAR_BTNS_H

#include <gtk/gtk.h>

void on_go_back_clicked(GtkButton *button, gpointer user_data);
void on_create_new_folder_clicked(GtkButton *button, gpointer user_data);
void on_filter_by_clicked(GtkButton *button, gpointer user_data);

void create_go_back_btn(GtkWidget *container, GtkWindow *window);
void create_create_new_folder_btn(GtkWidget *container, GtkWindow *window);
void create_sort_btn(GtkWidget *container);
void create_find_btn(GtkWidget *container);

#endif // TOOLBAR_BTNS_H

#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <gtk/gtk.h>
#include <windows.h>  

#include "../utils/runtime_utils.h"
#include "../utils/system_utils.h"
#include "../filelist/filelist.h"
#include "sidebar_btns.h"

GtkWidget* add_sidebar_to_window(GtkWindow *window);
void create_disk_label(GtkWidget *container);
void on_dir_clicked(GtkButton *button, gpointer user_data);
void on_disk_clicked(GtkButton *button, gpointer user_data);

#endif // SIDEBAR_H

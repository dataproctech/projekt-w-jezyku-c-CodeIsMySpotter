#include <gtk/gtk.h>





#ifndef FILELIST_H
#define FILELIST_H

#include <gtk/gtk.h>

GtkWidget *create_icon_from_file(const char *filepath, int width, int height);
GtkWidget *create_entry_button(const char *filename, gboolean is_file, GtkWindow *window);

#endif // ICON_UTILS_H

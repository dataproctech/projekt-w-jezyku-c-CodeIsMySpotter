#include "filelist_btns.h"
#include "filelist.h"
#include "../utils/runtime_utils.h"
#include "../utils/system_utils.h"
#include <gtk/gtk.h>



void on_delete_entry(GtkMenuItem *menuitem, gpointer user_data) {
    GtkWidget *button = g_object_get_data(G_OBJECT(menuitem), "entry_widget");
    const char *entry_name = g_object_get_data(G_OBJECT(button), "entry_name");
    gboolean is_file = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "is_file"));

    GtkWindow *window = g_object_get_data(G_OBJECT(button), "parent_window");
    const char *current_path = g_object_get_data(G_OBJECT(window), "path");

    char full_path[PATH_MAX];
    snprintf(full_path, sizeof(full_path), "%s/%s", current_path, entry_name);

    Result res;
    if (is_file) {
        res = delete_file(full_path);
    } else {
        res = delete_dir(full_path); 
    }

    if (res.error_code == ERR) {
        g_warning("Błąd usuwania: %s", res.message);
        return;
    } else {
        g_message("Usunięto: %s", res.message);
    }

    List *old_list = g_object_get_data(G_OBJECT(window), "file_list");
    if (old_list != NULL) {
        list_deinit(old_list, free);
    }

    Result dir_res = list_dir(current_path);
    if (dir_res.error_code == OK) {
        List *dir_list = (List *)dir_res.value;
        g_object_set_data(G_OBJECT(window), "file_list", dir_list);
        update_filelist(GTK_WIDGET(window));
    } else {
        g_warning("Nie udało się odczytać katalogu: %s", dir_res.message);
    }
}


gboolean on_entry_right_click(GtkWidget *widget, GdkEventButton *event, gpointer user_data) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 3) {
        GtkWidget *menu = gtk_menu_new();

        GtkWidget *delete_item = gtk_menu_item_new_with_label("Usuń");
        gtk_menu_shell_append(GTK_MENU_SHELL(menu), delete_item);

        // przekazanie widgetu jako dane
        g_object_set_data(G_OBJECT(delete_item), "entry_widget", widget);
        g_signal_connect(delete_item, "activate", G_CALLBACK(on_delete_entry), NULL);

        gtk_widget_show_all(menu);
        gtk_menu_popup_at_pointer(GTK_MENU(menu), (GdkEvent *)event);

        return TRUE;
    }
    return FALSE;
}



void on_entry_clicked(GtkButton *button, gpointer user_data) {
    const char *entry_name = g_object_get_data(G_OBJECT(button), "entry_name");
    GtkWindow *window = g_object_get_data(G_OBJECT(button), "parent_window");

    if (!entry_name || !GTK_IS_WINDOW(window)) return;

    const char *current_path = g_object_get_data(G_OBJECT(window), "path");
    if (!current_path) return;

    char new_path[PATH_MAX];
    snprintf(new_path, sizeof(new_path), "%s/%s", current_path, entry_name);

    if (!g_file_test(new_path, G_FILE_TEST_IS_DIR)) return;

    g_object_set_data_full(G_OBJECT(window), "path", g_strdup(new_path), g_free);

    GtkWidget *path_label = g_object_get_data(G_OBJECT(window), "path-label");
    if (GTK_IS_LABEL(path_label)) {
        gtk_label_set_text(GTK_LABEL(path_label), new_path);
    }

    Result dir_res = list_dir(new_path);
    List *dir_list = (List *)unwrap_or(dir_res, NULL);
    if (dir_list) {
        List *old_list = g_object_get_data(G_OBJECT(window), "file_list");
        if (old_list != NULL) {
            list_deinit(old_list, free);
        }

        g_object_set_data(G_OBJECT(window), "file_list", dir_list);
        update_filelist(window);
    }
}



GtkWidget *create_icon_from_file(const char *filepath, int width, int height) {
    GError *error = NULL;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filepath, &error);
    if (!pixbuf) {
        g_warning("Failed to load icon from %s: %s", filepath, error->message);
        g_error_free(error);
        return gtk_image_new(); 
    }

    GdkPixbuf *scaled = gdk_pixbuf_scale_simple(pixbuf, width, height, GDK_INTERP_BILINEAR);
    g_object_unref(pixbuf);  

    GtkWidget *image = gtk_image_new_from_pixbuf(scaled);
    g_object_unref(scaled);  

    return image;
}



GtkWidget *create_entry_button(const char *filename, gboolean is_file, GtkWindow *window) {
    gchar *utf8_filename = g_locale_to_utf8(filename, -1, NULL, NULL, NULL);
    if (!utf8_filename) {
        utf8_filename = g_strdup(filename);
    }

    GtkWidget *button = gtk_button_new();
    gtk_widget_set_name(button, "entry-button");

    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);

    GtkWidget *icon;
    if (is_file) {
        icon = create_icon_from_file("assets/File.png", 35, 35);
        g_signal_connect(button, "button-press-event", G_CALLBACK(on_entry_right_click), NULL);
    } else {
        icon = create_icon_from_file("assets/DirectoryIcon.png", 35, 35);
        g_signal_connect(button, "clicked", G_CALLBACK(on_entry_clicked), NULL);
        g_signal_connect(button, "button-press-event", G_CALLBACK(on_entry_right_click), NULL);
    }

    GtkWidget *label = gtk_label_new(utf8_filename);
    gtk_label_set_xalign(GTK_LABEL(label), 0.0); 

    g_object_set_data_full(G_OBJECT(button), "entry_name", g_strdup(filename), g_free);
    g_object_set_data(G_OBJECT(button), "is_file", GINT_TO_POINTER(is_file));
    g_object_set_data(G_OBJECT(button), "parent_window", window);

    gtk_box_pack_start(GTK_BOX(hbox), icon, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), label, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(button), hbox);

    gtk_widget_show_all(button);

    g_free(utf8_filename);
    return button;
}

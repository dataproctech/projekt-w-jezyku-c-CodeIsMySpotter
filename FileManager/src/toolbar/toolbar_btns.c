#include "toolbar_btns.h"
#include "../filelist/filelist.h"
#include "../utils/runtime_utils.h"
#include "../utils/system_utils.h"
#include <gtk/gtk.h>

void on_go_back_clicked(GtkButton *button, gpointer user_data) {
    GtkWindow *window = GTK_WINDOW(user_data);

    char *current_path = (char *)g_object_get_data(G_OBJECT(window), "path");
    if (!current_path || strlen(current_path) == 0) {
        return;
    }

    char new_path[PATH_MAX];
    strncpy(new_path, current_path, sizeof(new_path));
    new_path[sizeof(new_path) - 1] = '\0';

    size_t len = strlen(new_path);

    if (len > 1 && (new_path[len - 1] == '/' || new_path[len - 1] == '\\')) {
        new_path[len - 1] = '\0';
        len--;
    }

    char *last_sep = strrchr(new_path, '/');
    if (!last_sep) {
        last_sep = strrchr(new_path, '\\'); 
    }

    if (last_sep) {
        if (last_sep == new_path + 2 && new_path[1] == ':') {
            new_path[last_sep - new_path + 1] = '\0'; 
        } else {
            *last_sep = '\0'; 
        }
    } else {
        return;
    }

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


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void on_create_new_folder_clicked(GtkButton *button, gpointer user_data)
{
    GtkWindow *window = GTK_WINDOW(user_data);

    GtkWidget *dialog = gtk_dialog_new_with_buttons(
        "Create New",
        window,
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        "_Cancel", GTK_RESPONSE_CANCEL,
        "_Create", GTK_RESPONSE_ACCEPT,
        NULL
    );

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Enter name of file or folder...");
    gtk_box_pack_start(GTK_BOX(content_area), entry, TRUE, TRUE, 10);
    gtk_widget_show_all(dialog);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        const char *name = gtk_entry_get_text(GTK_ENTRY(entry));
        const char *current_path = g_object_get_data(G_OBJECT(window), "path");

        if (name && strlen(name) > 0 && current_path) {
            char full_path[512];
            snprintf(full_path, sizeof(full_path), "%s/%s", current_path, name);

            Result result;
            if (strchr(name, '.')) {
              
                FILE *f = fopen(full_path, "w");
                if (f) {
                    fclose(f);
                    result = ok(NULL, "File created");
                } else {
                    result = err("Could not create file");
                }
            } else {
            
                result = create_dir(full_path);  
            }

            if (result.error_code == OK) {
                List *old_list = g_object_get_data(G_OBJECT(window), "file_list");
                if (old_list) list_deinit(old_list, free);

                Result dir_res = list_dir(current_path);
                List *new_list = (List *)unwrap_or(dir_res, NULL);
                g_object_set_data(G_OBJECT(window), "file_list", new_list);

                update_filelist(window);
            } else {
                g_warning("Create failed: %s", result.message);
            }
        }
    }

    gtk_widget_destroy(dialog);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void on_sort_by_clicked(GtkButton *button, gpointer user_data)
{
    // Implement the functionality for filtering
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_go_back_btn(GtkWidget *container, GtkWindow *window) {
    GdkPixbuf *go_back_icon = gdk_pixbuf_new_from_file_at_scale("assets/GoBack.png", 40, 40, TRUE, NULL);
    GtkWidget *go_back_image = gtk_image_new_from_pixbuf(go_back_icon);
    GtkWidget *go_back_btn = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(go_back_btn), go_back_image);
    gtk_widget_set_name(go_back_btn, "toolbar-btn");
    gtk_box_pack_start(GTK_BOX(container), go_back_btn, FALSE, FALSE, 0);
    g_object_unref(go_back_icon);
    g_signal_connect(go_back_btn, "clicked", G_CALLBACK(on_go_back_clicked), window);


}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_create_new_folder_btn(GtkWidget *container, GtkWindow *window) {
    GdkPixbuf *create_new_folder_icon = gdk_pixbuf_new_from_file_at_scale("assets/CreateDir.png", 40, 40, TRUE, NULL);
    GtkWidget *create_new_folder_btn = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(create_new_folder_btn), gtk_image_new_from_pixbuf(create_new_folder_icon));
    gtk_widget_set_name(create_new_folder_btn, "toolbar-btn");
    gtk_box_pack_start(GTK_BOX(container), create_new_folder_btn, FALSE, FALSE, 0);
    g_object_unref(create_new_folder_icon);
    g_signal_connect(create_new_folder_btn, "clicked", G_CALLBACK(on_create_new_folder_clicked), window);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void create_sort_btn(GtkWidget *container) {
    GdkPixbuf *sort_icon = gdk_pixbuf_new_from_file_at_scale("assets/FilterBy.png", 40, 40, TRUE, NULL);
    GtkWidget *sort_btn = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(sort_btn), gtk_image_new_from_pixbuf(sort_icon));
    gtk_widget_set_name(sort_btn, "toolbar-btn");
    gtk_box_pack_start(GTK_BOX(container), sort_btn, FALSE, FALSE, 0);
    g_object_unref(sort_icon);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_find_btn(GtkWidget *container) {
    GdkPixbuf *find_icon = gdk_pixbuf_new_from_file_at_scale("assets/Find.png", 40, 40, TRUE, NULL);
    GtkWidget *find_btn = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(find_btn), gtk_image_new_from_pixbuf(find_icon));
    gtk_widget_set_name(find_btn, "toolbar-btn");
    gtk_box_pack_start(GTK_BOX(container), find_btn, FALSE, FALSE, 0);
    g_object_unref(find_icon);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
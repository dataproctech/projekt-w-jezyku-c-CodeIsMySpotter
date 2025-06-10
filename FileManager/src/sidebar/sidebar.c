#include "../utils/runtime_utils.h"
#include "../utils/system_utils.h"
#include "../filelist/filelist.h"
#include <sidebar_btns.h>
#include "sidebar.h"



void on_dir_clicked(GtkButton *button, gpointer user_data) {
    GtkWindow *window = GTK_WINDOW(user_data);
    const char *folder_name = g_object_get_data(G_OBJECT(button), "folder_name");

    GtkWidget *path_label = g_object_get_data(G_OBJECT(window), "path-label");
    const gchar *new_path = NULL;

    if (g_strcmp0(folder_name, "Desktop") == 0) {
        new_path = g_get_user_special_dir(G_USER_DIRECTORY_DESKTOP);
    } else if (g_strcmp0(folder_name, "Documents") == 0) {
        new_path = g_get_user_special_dir(G_USER_DIRECTORY_DOCUMENTS);
    } else if (g_strcmp0(folder_name, "Downloads") == 0) {
        new_path = g_get_user_special_dir(G_USER_DIRECTORY_DOWNLOAD);
    }

    if (new_path != NULL) {
        g_object_set_data_full(G_OBJECT(window), "path", g_strdup(new_path), g_free);
        gtk_label_set_text(GTK_LABEL(path_label), new_path);

        
        const char *as_char = (const char *)new_path;
        Result dir_res = list_dir(as_char);

        List *dir_list = (List *)unwrap_or(dir_res, NULL);
        if (dir_list) {
          List *old_list = g_object_get_data(G_OBJECT(window), "file_list");
          if (old_list != NULL) {
              list_deinit(old_list, free);
          }

          g_object_set_data(G_OBJECT(window), "file_list", dir_list);
          update_filelist(user_data);
      }



    } else {
        //g_print("Unknown folder name: %s\n", folder_name);
    }
}

void on_disk_clicked(GtkButton *button, gpointer user_data) {
    GtkWindow *window = GTK_WINDOW(user_data);
    const char *disk_name = g_object_get_data(G_OBJECT(button), "disk_name");
    
    char path[4] = { disk_name[0], ':', '/', '\0' };

    g_object_set_data_full(G_OBJECT(window), "path", g_strdup(path), g_free);

    GtkWidget *path_label = g_object_get_data(G_OBJECT(window), "path-label");
    if (GTK_IS_LABEL(path_label)) {
        gtk_label_set_text(GTK_LABEL(path_label), path);
    }

    Result dir_res = list_dir(path);
    List *dir_list = (List *)unwrap_or(dir_res, NULL);

    if (dir_list) {
        List *old_list = g_object_get_data(G_OBJECT(window), "file_list");
        if (old_list != NULL) {
            list_deinit(old_list, free);
        }

        g_object_set_data(G_OBJECT(window), "file_list", dir_list);
        update_filelist(user_data);
    } else {
        g_warning("Failed to read directory or directory is empty.");
    }
}

GtkWidget* add_sidebar_to_window(GtkWindow *window) {
    GtkWidget *main_content = g_object_get_data(G_OBJECT(window), "main-content");
    if (!GTK_IS_BOX(main_content)) {
        g_warning("main-content not found or invalid");
        return NULL;
    }

    // Sidebar container
    GtkWidget *sidebar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(sidebar, "sidebar");
    gtk_widget_set_vexpand(sidebar, TRUE);
    gtk_widget_set_hexpand(sidebar, FALSE);
    gtk_container_set_border_width(GTK_CONTAINER(sidebar), 10);

    GdkPixbuf *folder_icon_pixbuf = gdk_pixbuf_new_from_file_at_size("assets/directoryIcon.png", 24, 24, NULL);
    GtkWidget *folder_icon = gtk_image_new_from_pixbuf(folder_icon_pixbuf);

    GtkWidget *directories_label = gtk_label_new("System Directories:");
    gtk_widget_set_name(directories_label, "sidebar-label");
    gtk_label_set_xalign(GTK_LABEL(directories_label), 0.0); 
    gtk_widget_set_halign(directories_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(sidebar), directories_label, FALSE, FALSE, 0);

    const char *folder_names[] = { "Desktop", "Downloads", "Documents", NULL };
    for (int i = 0; folder_names[i] != NULL; i++) {
        GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
        gtk_widget_set_name(hbox, "sidebar-box");

        GtkWidget *icon = gtk_image_new_from_pixbuf(folder_icon_pixbuf);
        GtkWidget *label = gtk_label_new(folder_names[i]);
        gtk_widget_set_name(label, "sidebar-label");

        gtk_box_pack_start(GTK_BOX(hbox), icon, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);


        GtkWidget *button = gtk_button_new();
        gtk_widget_set_name(button, "sidebar-button");
        g_object_set_data(G_OBJECT(button), "folder_name", folder_names[i]);
        g_signal_connect(button, "clicked", G_CALLBACK(on_dir_clicked), window);
        gtk_container_add(GTK_CONTAINER(button), hbox);
        gtk_box_pack_start(GTK_BOX(sidebar), button, FALSE, FALSE, 0);
    }

    GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(sidebar), separator, FALSE, FALSE, 10);

    GdkPixbuf *disk_icon_pixbuf = gdk_pixbuf_new_from_file_at_size("assets/DiskIcon.png", 24, 24, NULL);
    GtkWidget *disk_icon = gtk_image_new_from_pixbuf(disk_icon_pixbuf);

    create_disk_label(sidebar);


    DWORD drives = GetLogicalDrives();

    for (char letter = 'A'; letter <= 'Z'; ++letter) {
        if (drives & (1 << (letter - 'A'))) {
            char disk_label[4] = { letter, ':', '\\', '\0' };
            GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
            gtk_widget_set_name(hbox, "sidebar-box");

            GtkWidget *icon = gtk_image_new_from_pixbuf(disk_icon_pixbuf);
            GtkWidget *label = gtk_label_new(disk_label);
            gtk_widget_set_name(label, "sidebar-label");

            gtk_box_pack_start(GTK_BOX(hbox), icon, FALSE, FALSE, 0);
            gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);

            GtkWidget *button = gtk_button_new();
            char *str = g_strdup_printf("%c", letter);
            g_object_set_data(G_OBJECT(button), "disk_name", str);
            g_signal_connect(button, "clicked", G_CALLBACK(on_disk_clicked), window);
            gtk_widget_set_name(button, "sidebar-button");
            gtk_container_add(GTK_CONTAINER(button), hbox);
            gtk_box_pack_start(GTK_BOX(sidebar), button, FALSE, FALSE, 0);


        }
    }

    gtk_box_pack_start(GTK_BOX(main_content), sidebar, FALSE, FALSE, 0);

    return sidebar;
}



void create_disk_label(GtkWidget *container){
    GtkWidget *disks_label = gtk_label_new("Disks:");
    gtk_widget_set_name(disks_label, "sidebar-label");
    gtk_label_set_xalign(GTK_LABEL(disks_label), 0.0); 
    gtk_widget_set_halign(disks_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(container), disks_label, FALSE, FALSE, 0);
}

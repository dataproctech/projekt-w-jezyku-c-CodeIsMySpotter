#include <gtk/gtk.h>
#include <windows.h>  

void on_dir_clicked(GtkButton *button, gpointer user_data) {
    GtkWindow *window = GTK_WINDOW(user_data);
    const char *folder_name = g_object_get_data(G_OBJECT(button), "folder_name");
    printf("Folder clicked: %s\n", folder_name);
}

void on_disk_clicked(GtkButton *button, gpointer user_data) {
    GtkWindow *window = GTK_WINDOW(user_data);
    const char *disk_name = g_object_get_data(G_OBJECT(button), "disk_name");
    printf("Disk clicked: %s\n", disk_name);
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

    // Ikonka folderu
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

    // Separator
    GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(sidebar), separator, FALSE, FALSE, 10);

    // Label "Disks"

    GdkPixbuf *disk_icon_pixbuf = gdk_pixbuf_new_from_file_at_size("assets/DiskIcon.png", 24, 24, NULL);
    GtkWidget *disk_icon = gtk_image_new_from_pixbuf(disk_icon_pixbuf);

    GtkWidget *disks_label = gtk_label_new("Disks:");
    gtk_widget_set_name(disks_label, "sidebar-label");
    gtk_label_set_xalign(GTK_LABEL(disks_label), 0.0); 
    gtk_widget_set_halign(disks_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(sidebar), disks_label, FALSE, FALSE, 0);

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

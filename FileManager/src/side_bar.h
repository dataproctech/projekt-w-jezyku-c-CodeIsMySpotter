#include <gtk/gtk.h>
#include <windows.h>  // do GetLogicalDrives()

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
    GdkPixbuf *folder_icon_pixbuf = gdk_pixbuf_new_from_file_at_size("assets/directoryIcon.png", 16, 16, NULL);
    GtkWidget *folder_icon = gtk_image_new_from_pixbuf(folder_icon_pixbuf);

    // Lista folderów
    const char *folder_names[] = { "Desktop", "Downloads", "Documents", NULL };
    for (int i = 0; folder_names[i] != NULL; i++) {
        GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

        GtkWidget *icon = gtk_image_new_from_pixbuf(folder_icon_pixbuf);
        GtkWidget *label = gtk_label_new(folder_names[i]);
        GtkStyleContext *context = gtk_widget_get_style_context(label);
        gtk_style_context_add_class(context, "sidebar-label");

        gtk_box_pack_start(GTK_BOX(hbox), icon, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);

        GtkWidget *button = gtk_button_new();
        gtk_container_add(GTK_CONTAINER(button), hbox);
        gtk_box_pack_start(GTK_BOX(sidebar), button, FALSE, FALSE, 0);
    }

    // Separator
    GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(sidebar), separator, FALSE, FALSE, 10);

    // Label "Disks"
    GtkWidget *disks_label = gtk_label_new("Disks:");
    gtk_box_pack_start(GTK_BOX(sidebar), disks_label, FALSE, FALSE, 0);

    // Sprawdź dostępne dyski
    DWORD drives = GetLogicalDrives();
    for (char letter = 'A'; letter <= 'Z'; ++letter) {
        if (drives & (1 << (letter - 'A'))) {
            char disk_label[4] = { letter, ':', '\\', '\0' };

            GtkWidget *disk_button = gtk_button_new_with_label(disk_label);
            gtk_box_pack_start(GTK_BOX(sidebar), disk_button, FALSE, FALSE, 0);
        }
    }

    // Dodaj sidebar do main_content (po lewej stronie)
    gtk_box_pack_start(GTK_BOX(main_content), sidebar, FALSE, FALSE, 0);

    return sidebar;
}

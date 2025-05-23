#include <gtk/gtk.h>


static inline GtkWidget *add_navbar_to_window(GtkWindow *window);
static inline void create_min_btn(GtkWindow *window, GtkWidget *container);
static inline void create_close_btn(GtkWindow *window, GtkWidget *container);
static inline void create_icon(GtkWidget *navbar);
static inline void on_minimize_clicked(GtkButton *button, gpointer user_data);
static inline void on_close_clicked(GtkButton *button, gpointer user_data);


static inline void on_minimize_clicked(GtkButton *button, gpointer user_data) {
    GtkWindow *window = GTK_WINDOW(user_data);
    gtk_window_iconify(window);
}

static inline void on_close_clicked(GtkButton *button, gpointer user_data) {
    GtkWindow *window = GTK_WINDOW(user_data);
    gtk_window_close(window);
}

static inline GtkWidget *add_navbar_to_window(GtkWindow *window) {
    GtkWidget *navbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(navbar, "navbar");
    gtk_widget_set_hexpand(navbar, TRUE);
    
    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
    gtk_widget_set_margin_end(button_box, 8);
    
    
    create_icon(navbar);
    create_min_btn(window, button_box);
    create_close_btn(window, button_box);

    
    gtk_box_pack_end(GTK_BOX(navbar), button_box, FALSE, FALSE, 0);


    return navbar;
}

static inline void create_icon(GtkWidget *navbar) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("assets/icon.png", 40, 40, TRUE, NULL);
    GtkWidget *icon = gtk_image_new_from_pixbuf(pixbuf);

    gtk_widget_set_margin_start(icon, 8);
    gtk_widget_set_margin_top(icon, 4);
    gtk_widget_set_margin_bottom(icon, 4);

    gtk_box_pack_start(GTK_BOX(navbar), icon, FALSE, FALSE, 0);
}


static inline void create_min_btn(GtkWindow *window, GtkWidget *container) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("assets/MinimizeBtn.png", 40, 40, TRUE, NULL);
    GtkWidget *minimize_icon = gtk_image_new_from_pixbuf(pixbuf);

    GtkWidget *minimize_btn = gtk_button_new();
    gtk_widget_set_name(minimize_btn, "minimize-btn");
    gtk_button_set_image(GTK_BUTTON(minimize_btn), minimize_icon);
    g_signal_connect(minimize_btn, "clicked", G_CALLBACK(on_minimize_clicked), window);

    gtk_box_pack_start(GTK_BOX(container), minimize_btn, FALSE, FALSE, 0);

}

static inline void create_close_btn(GtkWindow *window, GtkWidget *container) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("assets/CloseBtn.png", 40, 40, TRUE, NULL);
    GtkWidget *close_icon = gtk_image_new_from_pixbuf(pixbuf);

    GtkWidget *close_btn = gtk_button_new();
    gtk_widget_set_name(close_btn, "close-btn");
    gtk_button_set_image(GTK_BUTTON(close_btn), close_icon);
    g_signal_connect(close_btn, "clicked", G_CALLBACK(on_close_clicked), window);

    gtk_box_pack_start(GTK_BOX(container), close_btn, FALSE, FALSE, 0);

}
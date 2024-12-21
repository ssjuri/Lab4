#include <gtk/gtk.h>

void on_button_clicked(GtkWidget *widget, gpointer data) {
    g_print("Button clicked!\n");
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *button;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK+ Example");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    button = gtk_button_new_with_label("Click Me!");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);

    gtk_container_add(GTK_CONTAINER(window), button);
    gtk_widget_show_all(window);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_main();
    return 0;
}

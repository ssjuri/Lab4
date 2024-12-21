#include <gtk/gtk.h>

void on_calculate_clicked(GtkWidget *widget, gpointer data) {
    GtkEntry **entries = (GtkEntry **)data;
    const char *num1 = gtk_entry_get_text(entries[0]);
    const char *num2 = gtk_entry_get_text(entries[1]);
    int result = atoi(num1) + atoi(num2);

    char result_str[32];
    sprintf(result_str, "Result: %d", result);
    gtk_entry_set_text(entries[2], result_str);
}

int main(int argc, char *argv[]) {
    GtkWidget *window, *grid, *entry1, *entry2, *result_entry, *button;
    GtkEntry *entries[3];

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculator");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    entry1 = gtk_entry_new();
    entry2 = gtk_entry_new();
    result_entry = gtk_entry_new();
    gtk_entry_set_editable(GTK_ENTRY(result_entry), FALSE);

    button = gtk_button_new_with_label("Calculate");
    entries[0] = GTK_ENTRY(entry1);
    entries[1] = GTK_ENTRY(entry2);
    entries[2] = GTK_ENTRY(result_entry);

    g_signal_connect(button, "clicked", G_CALLBACK(on_calculate_clicked), entries);

    gtk_grid_attach(GTK_GRID(grid), entry1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), result_entry, 0, 2, 2, 1);

    gtk_widget_show_all(window);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_main();
    return 0;
}

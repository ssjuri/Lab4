#include <gtk/gtk.h>

// 버튼 클릭 시 호출되는 콜백 함수
static void on_button_clicked(GtkWidget *widget, gpointer data) {
    const char *button_label = gtk_button_get_label(GTK_BUTTON(widget));
    GtkEntry *entry = GTK_ENTRY(data);

    if (g_strcmp0(button_label, "C") == 0) {
        gtk_entry_set_text(entry, "");
    } else if (g_strcmp0(button_label, "=") == 0) {
        const char *expression = gtk_entry_get_text(entry);
        // 간단한 계산 처리 (eval 구현 필요)
        gtk_entry_set_text(entry, "결과");
    } else {
        const char *current_text = gtk_entry_get_text(entry);
        char *new_text = g_strdup_printf("%s%s", current_text, button_label);
        gtk_entry_set_text(entry, new_text);
        g_free(new_text);
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // 윈도우 생성
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "계산기");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);

    // 수직 박스 레이아웃
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // 입력창
    GtkWidget *entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

    // 버튼 레이아웃
    GtkWidget *grid = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

    // 버튼 배열
    const char *buttons[] = {
        "7", "8", "9", "+",
        "4", "5", "6", "-",
        "1", "2", "3", "*",
        "C", "0", "=", "/"
    };

    // 버튼 생성 및 배치
    for (int i = 0; i < 16; i++) {
        GtkWidget *button = gtk_button_new_with_label(buttons[i]);
        g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), entry);
        gtk_grid_attach(GTK_GRID(grid), button, i % 4, i / 4, 1, 1);
    }

    // 윈도우 종료 시 프로그램 종료
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // UI 표시
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

#include <gtk/gtk.h>


static gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data) {
    // Drawing code goes here
    cairo_set_source_rgb(cr, 0.3, 0.5, 0.7);
    cairo_rectangle(cr, 50, 50, 200, 200);
    cairo_fill(cr);
    return FALSE;
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *drawing_area;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Graphics Library Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    drawing_area = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(draw_callback), NULL);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.graphics_library", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

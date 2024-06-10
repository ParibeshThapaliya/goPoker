#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "GUI.h"
static void on_destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

void load_image(GtkWidget *window, char *file)
{
    GtkWidget *image;
    image = gtk_image_new_from_file(file);
    gtk_container_add(GTK_CONTAINER(window), image);
}
init_gui(int *argc, char ***argv, GtkWidget *main_window)
{
    gtk_init(&argc, &argv);
    main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(main_window), "Poker");
    gtk_window_set_default_size(GTK_WINDOW(main_window), WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_container_set_border_width(GTK_CONTAINER(main_window), 10);
     g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}
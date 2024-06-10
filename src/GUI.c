#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "GUI.h"
static void destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

void load_image(GtkWidget *window, char *file)
{
    GtkWidget *image;
    image = gtk_image_new_from_file(file);
    gtk_container_add(GTK_CONTAINER(window), image);
}

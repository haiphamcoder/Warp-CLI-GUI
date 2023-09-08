/*
    Warp-Cloudflare-GUI
*/

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

GtkWidget *window;
GtkWidget *switch_button;

int main(int argc, char *argv[])
{
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the builder
    GtkBuilder *builder = gtk_builder_new();

    // Load the UI file
    gtk_builder_add_from_file(builder, "ui.glade", NULL);

    return 0;
}
/*
    Warp-Cloudflare-GUI
*/

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

GtkWidget *window;
GtkWidget *switch_button;

void switch_button_callback(GtkWidget *widget, GParamSpec *pspec, gpointer data)
{
    if (gtk_switch_get_active(GTK_SWITCH(switch_button)))
    {
        system("warp-cli connect > /dev/null");
    }
    else
    {
        system("warp-cli disconnect > /dev/null");
    }
}

int main(int argc, char *argv[])
{
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the builder
    GtkBuilder *builder = gtk_builder_new();

    // Load the UI file
    gtk_builder_add_from_file(builder, "ui.glade", NULL);

    // Get the window object
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Get the switch button object
    switch_button = GTK_WIDGET(gtk_builder_get_object(builder, "switch_button"));
    if (system("warp-cli status | grep \"Status update: Connected\" > /dev/null") == 0)
    {
        gtk_switch_set_active(GTK_SWITCH(switch_button), TRUE);
    }
    else
    {
        gtk_switch_set_active(GTK_SWITCH(switch_button), FALSE);
    }

    // Connect the switch button callback
    g_signal_connect(switch_button, "notify::active", G_CALLBACK(switch_button_callback), NULL);

    // Destroy the builder
    g_object_unref(builder);

    // Show the window
    gtk_widget_show(window);

    // Start the main loop
    gtk_main();

    return 0;
}
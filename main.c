#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include <pthread.h>

GtkWidget *window;
GtkWidget *switch_button;
GtkWidget *lbl_status;
pthread_mutex_t switch_mutex = PTHREAD_MUTEX_INITIALIZER;
bool switch_active = false;

bool check_connection_status()
{
    int result = system("warp-cli status | grep \"Status update: Connected\" > /dev/null 2>&1");
    if (WIFEXITED(result) && WEXITSTATUS(result) == 0)
    {
        gtk_label_set_text(GTK_LABEL(lbl_status), "CONNECTED");
        return true;
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(lbl_status), "DISCONNECTED");
        return false;
    }
}

void switch_button_toggled(GtkWidget *widget, gpointer data)
{
    gboolean active = gtk_switch_get_active(GTK_SWITCH(widget));
    pthread_mutex_lock(&switch_mutex);
    switch_active = active;
    if (switch_active)
    {
        system("warp-cli connect > /dev/null 2>&1");
        gtk_label_set_text(GTK_LABEL(lbl_status), "CONNECTED");
    }
    else
    {
        system("warp-cli disconnect > /dev/null 2>&1");
        gtk_label_set_text(GTK_LABEL(lbl_status), "DISCONNECTED");
    }
    pthread_mutex_unlock(&switch_mutex);
}

void quit_program(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

int main(int argc, char *argv[])
{
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the builder
    GtkBuilder *builder = gtk_builder_new();

    // Load the UI file
    gtk_builder_add_from_file(builder, "ui.glade", NULL);

    // Connect signal handlers to the constructed widgets.
    gtk_builder_connect_signals(builder, NULL);

    // Get the window object
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    g_signal_connect(window, "destroy", G_CALLBACK(quit_program), NULL);

    // Get the status label object
    lbl_status = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_status"));

    // Get the switch button object
    switch_button = GTK_WIDGET(gtk_builder_get_object(builder, "switch_button"));
    gtk_switch_set_active(GTK_SWITCH(switch_button), check_connection_status());
    g_signal_connect(switch_button, "notify::active", G_CALLBACK(switch_button_toggled), NULL);

    // Load the CSS file
    GtkCssProvider *css_provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_css_provider_load_from_path(css_provider, "styles/style.css", NULL);
    g_object_unref(css_provider);

    // Destroy the builder
    g_object_unref(builder);

    // Show the window
    gtk_widget_show(window);

    // Start the main loop
    gtk_main();

    return 0;
}
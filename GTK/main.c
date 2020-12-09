#include <gtk/gtk.h>

static void activate (GtkApplication* app, gpointer user_data)
{
    GtkWidget *window;
    window = gtk_application_window_new(app);
    gtk_window_set_title (GTK_WINDOW(window),"ocr_window");
    gtk_window_set_default_size (GTK_WINDOW(window),200,200);
    gtk_widget_show_all(window);
}
// Structure of the graphical user interface.
typedef struct UserInterface
{
    GtkWindow* ocr_window;              // Main window
    GtkDrawingArea* area;               // Drawing area
    GtkButton* grayscale_button;                    
    GtkButton* b_and_w_button;
    GtkButton* segmentation_button;                 
    //GtkCheckButton* training_cb;      // Training check box
} UserInterface;

void redraw_item(GtkDrawingArea *area, GdkRectangle *old, GdkRectangle *new)
{
    gdk_rectangle_union(old, new, old);
    gtk_widget_queue_draw_area(GTK_WIDGET(area), old->x, old->y, old->width, old->height);
}

/*char* open(GtkWidget *window)
{
    GtkWindow *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new ("Open File",
                                      window,
                                      action,
                                      _("_Cancel"),
                                      GTK_RESPONSE_CANCEL,
                                      _("_Open"),
                                      GTK_RESPONSE_ACCEPT,
                                      NULL);

    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        filename = gtk_file_chooser_get_filename (chooser);
        return filename;
    }
}*/

int main (int argc, char *argv[])
{

    GtkWidget *window;
    // Initializes GTK.
    gtk_init(NULL, NULL);

    // Constructs a GtkBuilder instance.
    GtkBuilder* builder = gtk_builder_new ();


    // Loads the UI description.
    // (Exits if an error occurs.)
    GError* error = NULL;
    if (gtk_builder_add_from_file(builder, "ocr_window.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }
    gtk_builder_add_from_file(builder,"ocr_window",NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder,"ocr_window"));
    gtk_builder_connect_signals(builder,NULL);

    gtk_widget_show(window);

    // Gets the widgets.
    //GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(builder, "ocr_window"));
    //GtkDrawingArea* area = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "area"));
    GtkButton* grayscale_button = GTK_BUTTON(gtk_builder_get_object(builder, "grayscale_button"));
    GtkButton* b_and_w_button = GTK_BUTTON(gtk_builder_get_object(builder, "b_and_w_button"));
    GtkButton* segmentation_button = GTK_BUTTON(gtk_builder_get_object(builder, "segmentation_button"));    


    // Connects event handlers.
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);


    //char* filename= open(window);
    // Runs the main loop.
    gtk_main();

    // Exits.
    return 0;
}

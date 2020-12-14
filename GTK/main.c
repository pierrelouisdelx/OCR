#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <gtk/gtk.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../SDL/sdl.h"
#include "../SDL/pixel_operations.h"
#include "../SDL/paragraph.h"

#include "../NeuralNetwork/neuralnetwork.c"
#include "../NeuralNetwork/row_matrix.c"
#include "../NeuralNetwork/main.c"

typedef struct 
{
    GtkWidget *w_dlg_file_choose; // Pointer to file chooser dialog box
    GtkImage *w_img_main; // Pointer to image widget
    char *image; //Image filename
} app_widgets;

void css() //Load css in gtk
{
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), 
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *myCssFile = "style.css";
    GError *error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
    g_object_unref (provider);
}

void surface_to_image(SDL_Surface *surface, app_widgets *widgets)
{
    Uint32 src_format;
    Uint32 dst_format;

    GdkPixbuf *pixbuf;
    gboolean has_alpha;
    int rowstride;
    guchar *pixels;

    //Convert image from surface to a pixbuf friendly format
    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32); 
    SDL_Surface *output = SDL_ConvertSurface(surface, format, 0);
    SDL_FreeFormat(format);

    // select format                                                            
    src_format = output->format->format;
    has_alpha = SDL_ISPIXELFORMAT_ALPHA(src_format);
    if (has_alpha)
        dst_format = SDL_PIXELFORMAT_RGBA32;
    else 
        dst_format = SDL_PIXELFORMAT_RGB24;

    // create pixbuf                                                            
    pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, has_alpha, 8,
                             output->w, output->h);
    rowstride = gdk_pixbuf_get_rowstride(pixbuf);
    pixels = gdk_pixbuf_get_pixels(pixbuf);

    // copy pixels                                                              
    SDL_LockSurface(output);
    SDL_ConvertPixels(output->w, output->h, src_format,
               output->pixels, output->pitch,
               dst_format, pixels, rowstride);
    SDL_UnlockSurface(output);

    // create GtkImage from pixbuf                                              
    gtk_image_set_from_pixbuf(GTK_IMAGE(widgets->w_img_main),pixbuf);

    // release reference pixbuf                                      
    g_object_unref(pixbuf);
}

void gtk_grayscale(GtkWindow *window, app_widgets *widgets)
{
    SDL_Surface *image = load_image(widgets->image);
    image = grayscale(image);
    surface_to_image(image, widgets);
}

void gtk_blackwhite(GtkWindow *window, app_widgets *widgets)
{
    SDL_Surface *image = load_image(widgets->image);
    image = blackwhite(image);
    surface_to_image(image, widgets);
}

void gtk_segmentation(GtkWindow *window, app_widgets *widgets)
{
    SDL_Surface *image = load_image(widgets->image);
    image = lines_reco(image);
    image = char_reco(image);
    surface_to_image(image, widgets);
}

// File --> Open
void on_menuitm_open_activate(GtkMenuItem *menuitem, app_widgets *widgets)
{ 
    // Show the "Open Image" dialog box
    gtk_widget_show(widgets->w_dlg_file_choose);
    
    // Check return value from Open Image dialog box to see if user clicked the Open button
    if (gtk_dialog_run(GTK_DIALOG (widgets->w_dlg_file_choose)) == GTK_RESPONSE_OK) {
        // Get the file name from the dialog box
        widgets->image = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widgets->w_dlg_file_choose));
        if (widgets->image != NULL) 
        {
            GtkImage *img = GTK_IMAGE(gtk_image_new());
            gtk_image_set_from_file(img, widgets->image);
            GdkPixbuf *pixbuf = gtk_image_get_pixbuf(img);
            pixbuf = gdk_pixbuf_scale_simple(pixbuf, 680, 450, GDK_INTERP_BILINEAR);//Scale image
            gtk_image_set_from_pixbuf(GTK_IMAGE(widgets->w_img_main),pixbuf);
        }
    }

    // Finished with the "Open Image" dialog box, so hide it
    gtk_widget_hide(widgets->w_dlg_file_choose);
}

// File --> Quit
void on_menuitm_close_activate(GtkMenuItem *menuitem, app_widgets *widgets)
{
    gtk_main_quit();
}

void on_window_main_destroy()
{
    gtk_main_quit();
}

int main (int argc, char *argv[])
{
    // Initializes GTK.
    gtk_init(NULL, NULL);

    // Constructs a GtkBuilder instance.
    GtkBuilder* builder = gtk_builder_new();

    // Loads the UI description.
    // (Exits if an error occurs.)
    GError* error = NULL;
    if (gtk_builder_add_from_file(builder, "window.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    app_widgets *widgets = g_slice_new(app_widgets);

    css();
    
    // Gets the widgets.
    GtkWidget* window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    widgets->w_dlg_file_choose = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_file_choose"));
    widgets->w_img_main = GTK_IMAGE(gtk_builder_get_object(builder, "img_main"));

    GtkButton* grayscale = GTK_BUTTON(gtk_builder_get_object(builder, "grayscale"));
    GtkButton* blackandwhite = GTK_BUTTON(gtk_builder_get_object(builder, "blackandwhite"));
    GtkButton* segmentation = GTK_BUTTON(gtk_builder_get_object(builder, "segmentation"));
    GtkButton* ocr = GTK_BUTTON(gtk_builder_get_object(builder, "ocr"));
    GtkButton* text = GTK_BUTTON(gtk_builder_get_object(builder, "text"));
    GtkButton* save = GTK_BUTTON(gtk_builder_get_object(builder, "save"));
    GtkButton* quit = GTK_BUTTON(gtk_builder_get_object(builder, "quit"));

    gtk_builder_connect_signals(builder, widgets);
    g_object_unref(builder);

    //CONNECT SIGNAL
    g_signal_connect(window, "destroy",G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(grayscale, "clicked", G_CALLBACK(gtk_grayscale), widgets);
    g_signal_connect(blackandwhite, "clicked", G_CALLBACK(gtk_blackwhite), widgets);
    g_signal_connect(segmentation, "clicked", G_CALLBACK(gtk_segmentation), widgets);
    g_signal_connect(ocr, "clicked", G_CALLBACK(ocr), NULL);
    //g_signal_connect(text, "clicked", G_CALLBACK(open_file), widgets);
    //g_signal_connect(save, "clicked", G_CALLBACK(open_file), widgets);
    g_signal_connect(quit, "clicked",G_CALLBACK(gtk_main_quit), G_OBJECT(window));

    gtk_main();
    g_slice_free(app_widgets, widgets);

    return 0;
}

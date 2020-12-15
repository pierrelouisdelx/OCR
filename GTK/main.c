#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <gtk/gtk.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../SDL/sdl.h"
#include "../SDL/pixel_operations.h"
#include "../SDL/paragraph.h"
#include "../SDL/rotate.h"

#include "../NeuralNetwork/neuralnetwork.h"
#include "../NeuralNetwork/row_matrix.h"
#include "../NeuralNetwork/ocr.h"

#define UNUSED(x) (void) (x)

typedef struct button
{
    GtkButton* rotate;
    GtkButton* grayscale;
    GtkButton* blackandwhite;
    GtkButton* segmentation;
    GtkButton* ocr;
    GtkButton* text;
    GtkButton* train;
} button;

/*typedef struct Save
{
    GtkWidget *dlg_file_save;
    GtkWidget *name;
    GtkTextBuffer *buffer;
} Save;*/

typedef struct app_widgets 
{
    GtkWidget *w_dlg_file_choose; // Pointer to file chooser dialog box
    GtkWidget *about; // Pointer to image widget
    GtkImage *w_img_main; // Pointer to image widget
    char *image; //Image filename

    GtkWidget *text;
    GtkTextBuffer *buffer;
    button btn;
    //Save *save;
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

    const gchar *myCssFile = "GTK/style.css";
    GError *error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
    g_object_unref (provider);
}

void activate_buttons(app_widgets *widgets)
{
    gtk_widget_set_sensitive(GTK_WIDGET(widgets->btn.rotate), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(widgets->btn.grayscale), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(widgets->btn.blackandwhite), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(widgets->btn.segmentation), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(widgets->btn.ocr), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(widgets->btn.text), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(widgets->btn.train), TRUE);
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

void gtk_rotate(GtkWindow *window, app_widgets *widgets)
{
    UNUSED(window);
    SDL_Surface *image = load_image(widgets->image);
    image = resizeSquare(image);
    image = Rotate(image,10);
    surface_to_image(image, widgets);
}

void gtk_grayscale(GtkWindow *window, app_widgets *widgets)
{
    UNUSED(window);
    SDL_Surface *image = load_image(widgets->image);
    image = grayscale(image);
    surface_to_image(image, widgets);
}

void gtk_blackwhite(GtkWindow *window, app_widgets *widgets)
{
    UNUSED(window);
    SDL_Surface *image = load_image(widgets->image);
    image = blackwhite(image);
    surface_to_image(image, widgets);
}

void gtk_segmentation(GtkWindow *window, app_widgets *widgets)
{
    UNUSED(window);
    SDL_Surface *image = load_image(widgets->image);
    image = lines_reco(image);
    image = char_reco(image);
    lines_and_char_storage(image);
    surface_to_image(image, widgets);
}

// File --> Open
void on_menuitm_open_activate(GtkMenuItem *menuitem, app_widgets *widgets)
{
    UNUSED(menuitem);
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
            activate_buttons(widgets);
        }
    }

    // Finished with the "Open Image" dialog box, so hide it
    gtk_widget_hide(widgets->w_dlg_file_choose);
}

// File --> Quit
void on_menuitm_close_activate(GtkMenuItem *menuitem)
{
    UNUSED(menuitem);
    gtk_main_quit();
}

void on_about_item_activate(GtkMenuItem *menuitem, app_widgets *widgets)
{ 
    UNUSED(menuitem);
    gtk_widget_show(widgets->about);
}

void on_dlg_about_response(GtkMenuItem *menuitem, gint response_id, app_widgets *widgets)
{
    UNUSED(response_id);
    UNUSED(menuitem);
    gtk_widget_hide(widgets->about);
}

void on_window_main_destroy()
{
    gtk_main_quit();
}

void on_text_clicked(GtkMenuItem *menuitem, app_widgets *widgets)
{
    UNUSED(menuitem);
    gtk_widget_show(widgets->text);
    //gtk_text_buffer_set_text(widgets->buffer, ocrtext, -1); //ocrtext
}

void on_app_close(GtkMenuItem *menuitem, app_widgets *widgets)
{
    UNUSED(menuitem);
    gtk_widget_hide(widgets->text);
}

void gtk_train(GtkWindow *window)
{
    UNUSED(window);
    train_ocr();
}

void gtk_ocr(GtkWindow *window, app_widgets *widgets)
{
    UNUSED(window);
    ocr(widgets->image);
    
    gchar *file_name = "text.txt";
    gchar *file_content = NULL;
    gboolean file_success = FALSE;

    file_success = g_file_get_contents(file_name, &file_content, NULL, NULL);
    if (file_success) 
        gtk_text_buffer_set_text(widgets->buffer, file_content, -1);
    g_free(file_content);

    gtk_widget_show(widgets->text);
}

int main ()
{
    // Initializes GTK.
    gtk_init(NULL, NULL);

    // Constructs a GtkBuilder instance.
    GtkBuilder* builder = gtk_builder_new();

    // Loads the UI description.
    // (Exits if an error occurs.)
    GError* error = NULL;
    if (gtk_builder_add_from_file(builder, "GTK/window.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    app_widgets *widgets = g_slice_new(app_widgets);
    //Save *save = widgets->save;

    css();
    
    // Gets the widgets.
    GtkWidget* window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    widgets->w_dlg_file_choose = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_file_choose"));
    //save->dlg_file_save = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_file_save"));
    widgets->about = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_about"));
    widgets->w_img_main = GTK_IMAGE(gtk_builder_get_object(builder, "img_main"));

    widgets->text = GTK_WIDGET(gtk_builder_get_object(builder, "text_window"));
    //save->name = GTK_WIDGET(gtk_builder_get_object(builder, "save_text"));
    widgets->buffer = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "textbuffer1"));

    widgets->btn.rotate = GTK_BUTTON(gtk_builder_get_object(builder, "rotate"));
    widgets->btn.grayscale = GTK_BUTTON(gtk_builder_get_object(builder, "grayscale"));
    widgets->btn.blackandwhite = GTK_BUTTON(gtk_builder_get_object(builder, "blackandwhite"));
    widgets->btn.segmentation = GTK_BUTTON(gtk_builder_get_object(builder, "segmentation"));
    widgets->btn.ocr = GTK_BUTTON(gtk_builder_get_object(builder, "ocr"));
    widgets->btn.text = GTK_BUTTON(gtk_builder_get_object(builder, "text"));
    widgets->btn.train = GTK_BUTTON(gtk_builder_get_object(builder, "train"));
    GtkButton* quit = GTK_BUTTON(gtk_builder_get_object(builder, "quit"));

    gtk_builder_connect_signals(builder, widgets);
    g_object_unref(builder);

    //CONNECT SIGNAL
    g_signal_connect(window, "destroy",G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(widgets->btn.rotate, "clicked", G_CALLBACK(gtk_rotate), widgets);
    g_signal_connect(widgets->btn.grayscale, "clicked", G_CALLBACK(gtk_grayscale), widgets);
    g_signal_connect(widgets->btn.blackandwhite, "clicked", G_CALLBACK(gtk_blackwhite), widgets);
    g_signal_connect(widgets->btn.segmentation, "clicked", G_CALLBACK(gtk_segmentation), widgets);
    g_signal_connect(widgets->btn.ocr, "clicked", G_CALLBACK(gtk_ocr), widgets);
    g_signal_connect(widgets->btn.train, "clicked", G_CALLBACK(gtk_train),NULL);
    g_signal_connect(quit, "clicked",G_CALLBACK(gtk_main_quit), G_OBJECT(window));

    gtk_main();
    g_slice_free(app_widgets, widgets);

    return 0;
}

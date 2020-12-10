#include <stdlib.h>
#include <gtk/gtk.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../SDL/sdl.h"
#include "../SDL/pixel_operations.h"
#include "../SDL/paragraph.h"
#include <math.h>
#include <stdio.h>

void open_file(GtkWindow *window, GtkWidget *image)
{
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Open File", NULL,
                action, ("_Cancel"), GTK_RESPONSE_CANCEL,("_Open"),
                GTK_RESPONSE_ACCEPT,NULL);
    
    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        printf("%s", filename);
        image = gtk_image_new_from_file(filename);
        g_free (filename);
    } 
    gtk_widget_destroy (dialog);
}

void css(void)
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

void gtk_grayscale(GtkWindow *window, char *file)
{
    SDL_Surface *image = load_image(file);
    image = grayscale(image);
    display_image(image);
}

void gtk_blackwhite(GtkWindow *window, char *file)
{
    SDL_Surface *image = load_image(file);
    image = blackwhite(image);
    display_image(image);
}

void gtk_segmentation(GtkWindow *window, char *file)
{
    SDL_Surface *image = load_image(file);
    image = lines_reco(image);
    //lines_and_char_storage(image);
    display_image(image);
}

int main(int argc, char *argv[])
{
    //Areas
    GtkWindow *window;
    GtkWidget *vbox;
    GtkWidget *hpaned;

    GtkWidget *image;

    //Buttons
    GtkWidget *openfile;
    GtkWidget *grayscale;
    GtkWidget *blackandwhite;
    GtkWidget *segmentation;
    GtkWidget *OCR;
    GtkWidget *text;
    GtkWidget *save;
    GtkWidget *quit;

    char *img = "OCRtext3.bmp";
    
    init_sdl();
    gtk_init(NULL, NULL);

    css();

    //SET CONTAINERS
    window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
    gtk_window_set_title(GTK_WINDOW(window), "OCR");
    gtk_container_set_border_width(GTK_CONTAINER(window), 5);

    vbox = gtk_box_new(TRUE, 10);
    hpaned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);

    gtk_paned_pack1(GTK_PANED(hpaned), vbox, TRUE, FALSE);

    image = gtk_image_new_from_file(img);
    gtk_paned_pack2 (GTK_PANED(hpaned), image, TRUE, FALSE);

    gtk_container_add(GTK_CONTAINER(window), hpaned);

    //DEFINE BUTTONS
    openfile = gtk_button_new_with_label("Open File");
    grayscale = gtk_button_new_with_label("Grayscale");
    blackandwhite = gtk_button_new_with_label("Black and White");
    segmentation = gtk_button_new_with_label("Segmentation");
    OCR = gtk_button_new_with_label("OCR");
    text = gtk_button_new_with_label("View Text");
    save = gtk_button_new_with_label("Save");
    quit = gtk_button_new_with_label("Quit");
    gtk_widget_set_name(quit, "quit");

    //PACK BUTTONS TO BOX
    gtk_box_pack_start(GTK_BOX(vbox), openfile, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), grayscale, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), blackandwhite, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), segmentation, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), OCR, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), text, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), save, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), quit, TRUE, TRUE, 0);

    //CONNECT SIGNAL
    g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), G_OBJECT(window));
    g_signal_connect(openfile, "clicked", G_CALLBACK(open_file), image);
    g_signal_connect(grayscale, "clicked", G_CALLBACK(gtk_grayscale), img);
    g_signal_connect(blackandwhite, "clicked", G_CALLBACK(gtk_blackwhite), img);
    g_signal_connect(segmentation, "clicked", G_CALLBACK(gtk_segmentation), img);
    g_signal_connect(OCR, "clicked", G_CALLBACK(open_file), img);
    g_signal_connect(text, "clicked", G_CALLBACK(open_file), image);
    g_signal_connect(save, "clicked", G_CALLBACK(open_file), image);
    g_signal_connect(quit, "clicked",G_CALLBACK(gtk_main_quit), G_OBJECT(window));

    gtk_widget_show_all(GTK_WIDGET(window));

    gtk_main();

    return 0;
}

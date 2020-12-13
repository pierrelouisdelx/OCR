#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sdl.h"
#include "pixel_operations.h"
#include "paragraph.h"
#include "rotation.h"

void print_image(SDL_Surface *image)
{
    int w = image->w;
    int h = image->h;
    printf("width : %i\n",w);
    printf("height : %i\n",h);
    printf("format :  %s\n",image->format);
    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
        {
            Uint32 pixel = get_pixel(image,j,i);
            Uint8 r,g,b;
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            if(r == 0 && g == 0 && b == 0)
                printf("1");
            if(r == 255 && g == 255 && b == 255)
                printf("0");
        }
        printf("\n");
    }
}


int main(int argc,char **argv)
{
    if(argc == 1 || argc > 2) {
        printf("Usage: program image.bmp\n");
        return 0;
    }

    init_sdl();
    SDL_Surface* image = load_image(argv[1]);
    //double angle = 12;
    //image = rotate(image,angle);
    //image = grayscale(image);
    //image = blackwhite(image);
    //image = lines_reco(image);
    //lines_and_char_storage(image);
    //image = resize(image);
    display_image(image);
    //double angle = find_angle(image);
    //printf("angle : %lf\n",angle);
    SDL_RotateImage(image,50);
    display_image(image);
    //angle = find_angle(image);
    //printf("angle : %lf\n",angle);
    display_image(image);
    return 0;
}

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "pixel_operations.h"

SDL_Surface* paragraph_reco(SDL_Surface* image)
{
    int h = image->h;
    int w = image->w;
    int min_i;
    int min_j;
    int max_i;
    int max_j;
    for(int i=0; i < w; i++)
    {
        for(int j=0; j < h; j++)
        {
            Uint32 pixel = get_pixel (image,i,j);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            if (r > 0 && i < min_i)
                min_i = i;
            if (r > 0 && j < min_j)
                min_j = j;
            if (r > 0 && i > max_i)
                max_i = i;
            if (r > 0 && i > max_j)
                max_j = j;
        }
    }
    for(int i=min_i; i < max_i ; i++)
    {
        Uint32 new_pixel = SDL_MapRGB(image->format, 255, 0, 0);
        put_pixel(image,i,min_j,new_pixel);
        put_pixel(image,i,max_j,new_pixel);
    }
    for(int j=min_j; j < max_j ; j++)
    {
        Uint32 new_pixel = SDL_MapRGB(image->format, 255, 0, 0);
        put_pixel(image,min_i,j,new_pixel);
        put_pixel(image,max_i,j,new_pixel);
    }
    return image;
}








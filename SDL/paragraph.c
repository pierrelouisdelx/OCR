#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "pixel_operations.h"

SDL_Surface* paragraph_reco(SDL_Surface* image)
{
    int h = image->h;
    int w = image->w;
    int min_i = h - 1;
    int min_j = w - 1;
    int max_i = 0;
    int max_j = 0;
    int black = 0;
    printf("h : %i,\n w: %i\n",h,w); //prints h and w
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            Uint32 pixel = get_pixel (image,i,j);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            if (r == 0 && g == 0 && b == 0)
                black = 1;
            else
                black = 0;
            if (black && i < min_i && j < h)
            {
                min_i = i;
            }
            if (black && j < min_j && i < w)
            {
                min_j = j;
            }
            if (black && i > max_i && i < w)
            {
                max_i = i;
            }
            if (black && j > max_j && j < h)
            {
                max_j = j;
            }
        }
    }
    printf("\nimax: %i, \njmax: %i, \n imin: %i, \n jmin: %i \n",max_i,max_j,min_i,min_j);
    for(int i = min_i; i <= max_i; i++)
    {
        Uint32 new_pixel = SDL_MapRGB(image->format, 255, 0, 0);
        put_pixel(image,i,min_j,new_pixel);
        put_pixel(image,i,max_j,new_pixel);
    }
    for(int j=min_j; j <= max_j; j++)
    {
        Uint32 new_pixel = SDL_MapRGB(image->format, 255, 0, 0);
        put_pixel(image,min_i,j,new_pixel);
        put_pixel(image,max_i,j,new_pixel);
    }

    return image;
}








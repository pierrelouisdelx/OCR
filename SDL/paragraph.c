#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "pixel_operations.h"

int *mins_maxs(SDL_Surface* image)
{
    int h = image->h;
    int w = image->w;
    Uint32 pixel;
    Uint8 r,g,b;
    int min_i = w - 1;
    int min_j = h - 1;
    int max_i = 0;
    int max_j = 0;
    int black;
    int *four = malloc(sizeof(int)*4);
    for (int i = 0; i < w; i++)
    {
        for(int j = 0; j < h; j++)
        {
            black = 0;
            pixel = get_pixel(image,i,j);
            SDL_GetRGB(pixel, image -> format, &r, &g, &b);
            if (r == g && g == b && b == 0)
                black = 1;
            if (black)
            {
                if (i < min_i)
                    min_i = i;
                if (j < min_j)
                    min_j = j;
            }
        }
    }
    for (int i = w -1; i > -1; i--)
    {
        for (int j = h-1; j > -1; j--)
        {
            black = 0;
            pixel = get_pixel(image,i,j);
            SDL_GetRGB(pixel, image -> format, &r, &g, &b);
            if (r == g && g == b && b == 0)
                black = 1;
            if (black)
            {
                if (i > max_i)
                    max_i = i;
                if (j > max_j)
                    max_j = j;
            }

        }
    }
    four[0] = min_i;
    four[1] = min_j;
    four[2] = max_i;
    four[3] = max_j;
    return four;

}

SDL_Surface* paragraph_reco(SDL_Surface* image)
{
    int * four = mins_maxs(image);
    int min_i = four[0];
    int min_j = four[1];
    int max_i = four[2];
    int max_j = four[3];
    /*Uint32 pixel = SDL_MapRGB(image->format,255,0,0);

    for (int i = min_i; i < max_i ; i++)
    {
        put_pixel(image, i, min_j, pixel);
        put_pixel(image, i, max_j, pixel);
    }
    for (int j = min_j; j < max_j ; j++)
    {
        put_pixel(image, min_i, j, pixel);
        put_pixel(image, max_i, j, pixel);
    }*/
    int w = max_i - min_i;
    int h = max_j - min_j;
    Uint32 pixel2;
    Uint8 r, g, b;
    SDL_Surface* new_image = SDL_CreateRGBSurface(0,w,h,32,0,0,0,0);
    for (int i = 0; i < w; i++)
    {
        for (int j = 0;j < h; j++)
        {
            pixel2 = get_pixel(image,i+min_i,j+min_j);
            SDL_GetRGB(pixel2, image -> format, &r, &g, &b);
            put_pixel(new_image, i, j, pixel2);
        }
    }
    return new_image;
}

SDL_Surface* lines_reco(SDL_Surface* image)
{
    image = paragraph_reco(image);
    /*int * four = mins_maxs(image);
    int min_i = four[0];
    int min_j = four[1];
    int max_i = four[2];
    int max_j = four[3];*/
    Uint32 pixel;
    Uint8 r,g,b;
    int color = 0;
    int h = image->h;
    int w = image->w;
    for (int j = 0; j < h; j++)
    {
        for(int i = 0; i < w; i++)
        {
            pixel = get_pixel(image,i,j);
            SDL_GetRGB(pixel, image -> format, &r, &g, &b);
            if (i == w-1 && g != 0)
            {
                i = 0;
                color = 1;
            }
            if (color)
                put_pixel(image,i,j,(SDL_MapRGB(image->format,255,0,0)));
            if (g == 0)
                break;

        }
        color = 0;
    }
    return image;
}



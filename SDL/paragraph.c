#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    int w = max_i - min_i;
    int h = max_j - min_j;
    Uint32 pixel;
    Uint8 r, g, b;
    SDL_Surface* new_image = SDL_CreateRGBSurface(0,w,h,32,0,0,0,0);
    for (int i = 0; i < w; i++)
    {
        for (int j = 0;j < h; j++)
        {
            pixel = get_pixel(image,i+min_i,j+min_j);
            SDL_GetRGB(pixel, image -> format, &r, &g, &b);
            put_pixel(new_image, i, j, (SDL_MapRGB(image->format,r,g,b)));
        }
    }
    return new_image;
}

SDL_Surface* lines_reco(SDL_Surface* image)
{
    image = paragraph_reco(image);
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

void lines_storage(SDL_Surface* image)
{
    int h = image->h;
    int w = image->w;
    Uint32 pixel;
    Uint8 r,g,b;
    int lines_counter = 0;
    int nb_bmp = 0;
    for (int j = 0; j < h; j++)
    {

        pixel = get_pixel(image,10,j);
        SDL_GetRGB(pixel, image -> format, &r, &g, &b);
        if (lines_counter > 0 && g == r)
        {
            lines_counter += 1;
        }
        if ((lines_counter > 0 && r != b) || j == h-1)
        {
            printf("condition");
            //create a new bitmap (w,new_h) and storing it in /lines
            Uint32 pixel;
            Uint8 r1, g1, b1;
            SDL_Surface* new_image = SDL_CreateRGBSurface(0,w,lines_counter,32,0,0,0,0);
            for (int i = 0; i < w; i++)
            {
                int new_j = 0;
                for (int k = j-lines_counter ;k < j; k++)
                {
                    pixel = get_pixel(image,i,k);
                    SDL_GetRGB(pixel, image -> format, &r1, &g1, &b1);
                    put_pixel(new_image, i, new_j, (SDL_MapRGB(new_image->format,r1,g1,b1)));
                    new_j++;
                }
            }
            //save
            if (nb_bmp < 10)
            {
                char file[] = "SDL/bmp/lines/bmpX";
                file[17] = nb_bmp + '0';
                SDL_SaveBMP(new_image,file);
            }
            if (nb_bmp > 9)
            {
                char file[] = "SDL/bmp/lines/bmpXX";
                file[17] = nb_bmp/10 + '0';
                file[18] = nb_bmp%10 + '0';
                SDL_SaveBMP(new_image,file);
            }
            nb_bmp += 1;
            lines_counter = 0;
        }
        if (g == r && lines_counter == 0)
        {
            lines_counter = 1;
        }
        if (r != b)
            lines_counter = 0;
        printf("%d %d %d %d\n",r,g,b,lines_counter);
    }
}



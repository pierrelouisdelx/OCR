#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "pixel_operations.h"
#include <sys/stat.h>
#include <sys/types.h>
#include "sdl.h"


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

SDL_Surface* char_reco(SDL_Surface* image)
{
    Uint32 pixel;
    Uint8 r,g,b;
    int color = 0;
    int h = image->h;
    int w = image->w;
    for (int i = 0; i < w; i++)
    {
        for(int j = 0; j < h; j++)
        {
            pixel = get_pixel(image,i,j);
            SDL_GetRGB(pixel, image -> format, &r, &g, &b);
            if (j == h-1 && g != 0)
            {
                j = 0;
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

void char_storage(SDL_Surface* image, int line)
{

    int length;
    if (line < 10)
        length = 6;
    else
        length = 7;
    char* this_line = "line_";
    char* path = "SDL/bmp/chars/";
    int h = image->h;
    int w = image->w;
    Uint32 pixel;
    Uint8 r,g,b;
    int char_counter = 0;
    int nb_char = 0;
    for (int i = 0; i < w; i++)
    {
        pixel = get_pixel(image,i,0);
        SDL_GetRGB(pixel, image -> format, &r, &g, &b);
        if (char_counter > 0 && g == r)
            char_counter += 1;
        if ((char_counter > 0 && r != b))
        {
            Uint32 pixel;
            Uint8 r1, g1, b1;
            SDL_Surface* new_image = SDL_CreateRGBSurface(0,char_counter,h,
                    32,0,0,0,0);
            for (int j = 0; j < h; j++)
            {
                int new_i = 0;
                for (int k = i-char_counter ;k < i; k++)
                {
                    pixel = get_pixel(image,k,j);
                    SDL_GetRGB(pixel, image -> format, &r1, &g1, &b1);
                    put_pixel(new_image, new_i, j, (SDL_MapRGB(new_image->
                                    format,r1,g1,b1)));
                    new_i++;
                }
            }
            char line_str[length];
            for (int p = 0; p < 6;p++)
                line_str[p] = this_line[p];
            if(length == 6)
                line_str[5] = line + '0';
            else
            {
                line_str[5] = line/10 + '0';
                line_str[6] = line%10 + '0';
            }

            if (nb_char < 10)
            {
                int len = strlen(path) + strlen(line_str) + 1;
                char file[len];
                for (int s = 0; s < len ; s++)
                    file[s] = path[s];
                for (int s = strlen(path) ; s < len - 1;s++)
                    file[s] = line_str[s-strlen(path)];
                file[len] = nb_char +'0';
                printf("file : %s\n",file);
                SDL_SaveBMP(new_image,file);
            }
            if (nb_char > 9)
            {
                int len = strlen(path) + strlen(line_str) + 2;
                char file[len];
                for (int s = 0; s < len; s++)
                    file[s] = path[s];
                for (int s = strlen(path) ; s < len - 1;s++)
                    file[s] = line_str[s-strlen(path)];
                file[len-2] = ':';
                file[len-1] = nb_char/10 + '0';
                file[len] = nb_char%10 + '0';
                printf("file : %s\n",file);
                SDL_SaveBMP(new_image,file);
            }
            nb_char += 1;
            char_counter = 0;
        }
        if (g == r && char_counter == 0)
            char_counter = 1;
        if (r != b)
            char_counter = 0;
    }
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

        pixel = get_pixel(image,0,j);
        SDL_GetRGB(pixel, image -> format, &r, &g, &b);
        if (lines_counter > 0 && g == r)
        {
            lines_counter += 1;
        }
        if ((lines_counter > 0 && r != b) || j == h-1)
        {
            Uint32 pixel;
            Uint8 r1, g1, b1;
            if (j == h-1)
                lines_counter -= 1;
            SDL_Surface* new_image = SDL_CreateRGBSurface(0,w,lines_counter,
                    32,0,0,0,0);
            for (int i = 0; i < w; i++)
            {
                int new_j = 0;
                for (int k = j-lines_counter ;k < j; k++)
                {
                    pixel = get_pixel(image,i,k);
                    SDL_GetRGB(pixel, image -> format, &r1, &g1, &b1);
                    put_pixel(new_image, i, new_j, (SDL_MapRGB(new_image->
                                    format,r1,g1,b1)));
                    new_j++;
                }
            }
            SDL_Surface* new_new_image = char_reco(new_image);
            char_storage(new_new_image,nb_bmp);
            nb_bmp += 1;
            lines_counter = 0;
        }
        if (g == r && lines_counter == 0)
        {
            lines_counter = 1;
        }
        if (r != b)
            lines_counter = 0;
    }
}







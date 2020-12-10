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
    image = paragraph_reco(image);
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

    char* path = "SDL/bmp/chars/";
    int length;
    if (line < 10)
        length = 6;
    else
        length = 7;
    char* this_line = "line_";
    int h = image->h;
    int w = image->w;
    Uint32 pixel;
    Uint8 r,g,b;
    int char_counter = 0;
    int nb_of_red = 0;
    int nb_char = 0;
    int old_white_space = 0;
    for (int j = 0; j < h; j++)
    {
        put_pixel(image,w-1,j,(SDL_MapRGB(image->format,255,0,0)));
    }
    for (int i = 0; i < w; i++)
    {
        pixel = get_pixel(image,i,0);
        SDL_GetRGB(pixel, image -> format, &r, &g, &b);
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
        if (char_counter > 0 && g == r)
            char_counter += 1;
        if ((char_counter > 0 && r != b))
        {
            Uint32 pixel;
            Uint8 r1, g1, b1;
            if (nb_of_red > old_white_space * 2)
            {
                SDL_Surface* space_image = SDL_CreateRGBSurface(0,nb_of_red,h,
                    32,0,0,0,0);
                for (int j = 0; j < h; j++)
                {
                    int new_i = 0;
                    for (int k = i-char_counter -nb_of_red ;k < i -
                            char_counter; k++)
                    {
                        pixel = get_pixel(image,k,j);
                        SDL_GetRGB(pixel, image -> format, &r1, &g1, &b1);
                        put_pixel(space_image, new_i, j, (SDL_MapRGB(
                                        space_image->format,r1,g1,b1)));
                        new_i++;
                    }
                }
                //save the white space between 2 char
                if (nb_char < 10)
                {
                    int len = strlen(path) + length + 2;
                    char file_space[len];
                    for (int s = 0; s < len ; s++)
                        file_space[s] = path[s];
                    for (int s = strlen(path); s < len - 2;s++)
                        file_space[s] = line_str[s-strlen(path)];
                    file_space[len-2] = ':';
                    file_space[len-1] = nb_char +'0';
                    SDL_SaveBMP(space_image,file_space);
                }
                else if (nb_char > 9 && nb_char < 100)
                {
                    int len = strlen(path) + length + 3;
                    char file_space[len];
                    for (int s = 0; s < len; s++)
                        file_space[s] = path[s];
                    for (int s = strlen(path); s < len;s++)
                        file_space[s] = line_str[s-strlen(path)];

                    char last1 = (nb_char/10 + '0');
                    char last2 = (nb_char%10 + '0');
                    char last11[1];
                    last11[0] = last1;
                    char last22[1];
                    last22[0] = last2;
                    strcat(file_space,":");
                    strcat(file_space,last11);
                    SDL_SaveBMP(space_image,file_space);
                    strcat(file_space,last22);
                }
                else
                {
                    int len = strlen(path) + length + 3;
                    char file_space[len];
                    for (int s = 0; s < len; s++)
                        file_space[s] = path[s];
                    for (int s = strlen(path); s < len;s++)
                        file_space[s] = line_str[s-strlen(path)];
                    char last1 = ((nb_char/10)%10 + '0');
                    char last2 = (nb_char%10 + '0');

                    char last11[1];
                    last11[0] = last1;
                    char last22[1];
                    last22[0] = last2;
                    strcat(file_space,":");
                    strcat(file_space,"1");
                    strcat(file_space,last11);
                    SDL_SaveBMP(space_image,file_space);
                    strcat(file_space,last22);
                }
                nb_char += 1;
            }
            //Uint8 r1, g1, b1;
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
            //save the character

            if (nb_char < 10)
            {
                int len = strlen(path) + length + 2;
                char file[len];
                for (int s = 0; s < len ; s++)
                    file[s] = path[s];
                for (int s = strlen(path); s < len - 2;s++)
                    file[s] = line_str[s-strlen(path)];
                file[len-2] = ':';
                file[len-1] = nb_char +'0';
                SDL_SaveBMP(new_image,file);
            }
            else if (nb_char > 9 && nb_char < 100)
            {
                int len = strlen(path) + length + 3;
                char file[len];
                for (int s = 0; s < len; s++)
                    file[s] = path[s];
                for (int s = strlen(path); s < len;s++)
                    file[s] = line_str[s-strlen(path)];

                char last1 = (nb_char/10 + '0');
                char last2 = (nb_char%10 + '0');
                char last11[1];
                last11[0] = last1;
                char last22[1];
                last22[0] = last2;
                strcat(file,":");
                strcat(file,last11);
                SDL_SaveBMP(new_image,file);
                strcat(file,last22);
            }
            else
            {

                int len = strlen(path) + length + 3;
                char file[len];
                for (int s = 0; s < len; s++)
                    file[s] = path[s];
                for (int s = strlen(path); s < len;s++)
                    file[s] = line_str[s-strlen(path)];

                char last1 = ((nb_char/10)%10 + '0');
                char last2 = (nb_char%10 + '0');

                char last11[1];
                last11[0] = last1;
                char last22[1];
                last22[0] = last2;
                strcat(file,":");
                strcat(file,"1");
                strcat(file,last11);
                SDL_SaveBMP(new_image,file);
                strcat(file,last22);

            }
            nb_char += 1;
            char_counter = 0;
            old_white_space = nb_of_red;
            nb_of_red = 0;
        }
        if (g == r && char_counter == 0)
        {
            char_counter = 1;
        }
        if (r != b)
        {
            char_counter = 0;
            nb_of_red +=1;
        }
    }
}

void lines_and_char_storage(SDL_Surface* image)
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
        {
            lines_counter = 0;
        }
    }
}

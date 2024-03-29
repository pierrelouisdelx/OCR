#include "SDL2/SDL.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pixel_operations.h"
#include "sdl.h"

#define M_PI 3.14159265358979323846

double convert_to_rad(double angle_in_deg)
{
    double angle_in_rad;
    angle_in_rad = (angle_in_deg * M_PI) / 180;
    return angle_in_rad;
}

SDL_Surface *Rotate(SDL_Surface *image, double angle)
{
    angle = convert_to_rad(-angle);
    double cos_ang = cos(angle);
    double sin_ang = sin(angle);
    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    int new_height = fabs(-image->w * sin_ang) + fabs(image->h * cos_ang);
    int new_width = fabs(image->w * cos_ang) + fabs(image->h * sin_ang);
    SDL_Surface *output = SDL_CreateRGBSurface(SDL_SWSURFACE, new_width, new_height, 32, rmask, gmask, bmask, amask);

    for (int h = 0; h < output->h; h++)
    {
        for (int w = 0; w < output->w; w++)
        {
            int nh =
                (h - output->h / 2) * cos_ang - (w - output->w / 2) * sin_ang;
            int nw =
                (w - output->w / 2) * cos_ang + (h - output->h / 2) * sin_ang;

            nh += image->h / 2;
            nw += image->w / 2;

            if (nh > 0 && nh < image->h && nw > 0 && nw < image->w)
            {
                Uint32 pixel = get_pixel(image, nh, nw);
                put_pixel(output, h, w, pixel);
            }
            else
            {
                Uint32 white_pixel = SDL_MapRGB(output->format, 255, 255, 255);
                put_pixel(output, h, w, white_pixel);
            }
        }
    }
    return output;
}

int is_white_pixel(SDL_Surface *image, int h, int w)
{
    Uint8 r, g, b;
    Uint32 pixel = get_pixel(image, h, w);
    SDL_GetRGB(pixel, image->format, &r, &g, &b);
    if (r == 255 && g == 255 && b == 255)
        return 1;
    else
        return 0;
}

int compute_raycast_sum(SDL_Surface *image, int h, double angle)
{
    angle = convert_to_rad(angle);
    int ray = fabs(cos(angle) * image->w);
    int w_start = (image->w - ray) / 2;

    int sum = 0;
    for (int w = w_start; w < w_start + ray; w++)
    {
        int nh = h + tan(angle) * w;
        if (nh >= 0 && nh < image->h && !is_white_pixel(image, nh, w))
            sum++;
    }
    return sum;
}

double compute_variance(SDL_Surface *image, double angle)
{
    // Less accuracy, but faster result
    int h_start = image->h / 8;
    int h_len = (7 * image->h) / 8;
    double k = image->w / 15.;

    double sum = 0.;
    double sum_sq = 0.;
    for (int h = h_start; h < h_start + h_len; h += 4)
    {
        int s = compute_raycast_sum(image, h, angle);
        sum += s - k;
        sum_sq += (s - k) * (s - k);
    }
    return (sum_sq - (sum * sum) / h_len) / (h_len - 1);
}

double find_skew_angle(SDL_Surface *image,double lower_bound, double upper_bound, double precision)
{
    double skew_angle = 0.;
    double max_variance = 0.;

    for (double angle = lower_bound; angle <= upper_bound; angle += precision)
    {
        double variance = compute_variance(image, angle);
        if (variance > max_variance)
        {
            max_variance = variance;
            skew_angle = angle;
        }
    }

    return skew_angle;
}

SDL_Surface *image_deskew(SDL_Surface *image)
{
    double skew_angle = find_skew_angle(image, -15., +15., 1.);
    skew_angle = find_skew_angle(image, skew_angle - 3, skew_angle + 3, 0.1);
    image = Rotate(image, skew_angle);
    printf("%f", skew_angle);
    return image;
}

//tranforms an image into a square dimension (it is still the same image)
SDL_Surface* resizeSquare(SDL_Surface* image)
{
    Uint32 rmask, gmask, bmask, amask;
    int newDim = 0;
    if(image->h > image->w)
    {
        newDim = image->h;
    }
    else
    {
        newDim = image->w;
    }
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    int h = image->h;
    int w = image->w;
    SDL_Surface* new_image = SDL_CreateRGBSurface(0, newDim, newDim, 32, rmask, gmask, bmask, amask);
    SDL_FillRect(new_image, 0, (SDL_MapRGB(new_image->format, 255, 255, 255)));
    for(int i = 0; i < w ; i++)
    {
        for(int j = 0; j < h ; j++)
        {
            Uint32 pixelValue = get_pixel(image, i, j);
            put_pixel(new_image, i, j, pixelValue);
        }
        for(int j = h; j < newDim; j++)
        {
            put_pixel(new_image, i, j, (SDL_MapRGB(new_image->format, 255, 255, 255)));
        }
    }
    for(int i = w; i < newDim; i++)
    {
        for(int j = 0; j < newDim; j++)
        {
            put_pixel(new_image, i, j, (SDL_MapRGB(new_image->format, 255, 255, 255)));
        }
    }
   /* for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            x = i * (newDim / w);
            y = j * (newDim / h);
            pixel = get_pixel(image, i, j);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image -> format, &r, &g, &b);
            if (r != 255)
            {
                array[x][y] += 1;
            }            nb_per_cell[x][y] += 1;
        }
    }
       for (int i = 0; i < newDim; i++)
    {
        for (int j = 0; j < newDim; j++)
        {
            int average;
            if (nb_per_cell[i][j] > 0)
            {
                average = array[i][j]/nb_per_cell[i][j];
            }
            else
            {   average = 0;
            }
            if (average == 1)
            { put_pixel(new_image, i, j, (SDL_MapRGB(image->format,0,0,0)));
            }
            else
            {
                put_pixel(new_image, i, j, (SDL_MapRGB(image->format,255,255,255)));
            }
        }
    }*/
    SDL_FreeSurface(image);
    return new_image;
}


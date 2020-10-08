#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "pixel_operations.h"

SDL_Surface* blackwhite(SDL_Surface* image) {
    int h = image->h;
    int w = image->w;
    for(int i=0; i < w; i++) {
        for(int j=0; j < h; j++) {
            Uint32 pixel = get_pixel(image,i,j);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            Uint8 average = (r+g+b)/3;
            if (average < 128){
                average = 0;
            }
            else {
                average = 255;
            }
            Uint32 new_pixel = SDL_MapRGB(image->format, average, average, average);
            put_pixel(image,i,j,new_pixel);
        }
    }
    return image;
}


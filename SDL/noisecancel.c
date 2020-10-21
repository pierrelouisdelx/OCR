#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "pixel_operations.h"

SDL_Surface* noisecancel(SDL_Surface* image) {
    int h = image->h;
    int w = image->w;
    for(int i=0; i < w; i++) {
        for(int j=0; j < h; j++) {
            Uint32 pixel = get_pixel(image,i,j);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            if (r == 0 || r == 255)
            {
                

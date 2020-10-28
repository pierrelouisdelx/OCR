#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "pixel_operations.h"

SDL_Surface* noisecancel(SDL_Surface* image) 
{
    int h = image->h;
    int w = image->w;
    for(int i=1; i < w-1; i++)
    {
        for(int j=1; j < h-1; j++)
        {
            Uint32 pixel = get_pixel(image,i,j);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            if (r == 255)
            {
                int meanf = 0;
                int flag = 0;
                for (int k = i-1; k<=i+1; k++) {
                    for (int l = j-1; l<= j+1; l++) {
                        if (k==i && l==j)
                            continue;
                        Uint32 pixelcheck = get_pixel(image,k,l);
                        Uint8 rr, gg, bb;
                        SDL_GetRGB(pixelcheck, image->format, &rr, &gg, &bb);
                        if (rr == 255)
                        {
                            flag += 1;
                        }
                        else
                        {
                            meanf += rr;
                        }
                    }
                }
                if (flag < 3)
                {
                    r = meanf/(8-flag);
                    Uint32 new_pixel = SDL_MapRGB(image->format, r, r, r);
                    put_pixel(image, i, j,new_pixel);
                }
            }
        }
    }
    return image;
}

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "pixel_operations.h"
#include <math.h>

void init_sdl() {
    if(SDL_Init(SDL_INIT_VIDEO) == -1) {
        printf("Error while loading sdl: %s\n", SDL_GetError());
    }
}

SDL_Surface* load_image(char *file) {
    return SDL_LoadBMP(file);
}

void on_keypress()
{
    SDL_Event event;

    // Wait for a key to be down.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYDOWN);

    // Wait for a key to be up.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYUP);
}

void display_image(SDL_Surface* image) {
    SDL_Window *window;

    window = SDL_CreateWindow("OCR",SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,image->w,image->h,0);

    if(window == NULL) {
        printf("Error while loading window");
        SDL_GetError();
    }

    //Display image in window
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);

    //SDL_RenderCopyEx(renderer, texture, NULL, NULL, 50,NULL,SDL_FLIP_NONE);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    on_keypress();
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

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

SDL_Surface* grayscale(SDL_Surface* image) {
    int h = image->h;
    int w = image->w;
    for(int i=0; i < w; i++) {
        for(int j=0; j < h; j++) {
            Uint32 pixel = get_pixel(image,i,j);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            Uint8 average = 0.3 * r + 0.59 * g + 0.11 * b;
            r = average;
            g = average;
            b = average;
            Uint32 new_pixel = SDL_MapRGB(image->format, r, g, b);
            put_pixel(image,i,j,new_pixel);
        }
    }
    return image;
}

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

/*SDL_Surface* rotate(SDL_Surface* image, float angle) {
    int h = image->h;
    int w = image->w;

    for(int i=0; i<w; i++) 
    {
        for(int j=0; j<h; j++) 
        {
            Uint32 pixel = get_pixel(image,i,j);
            int x = i*cos(angle) - j*sin(angle);
            int y = i*sin(angle) + j*cos(angle);
            if(x < w && y < h) 
            {
                put_pixel(image,x,y,pixel);
            }
        }
    }
    return image;
}

int houghtransform() {
    //Detect image rotation angle
    return 0;
}*/

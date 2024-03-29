#ifndef PIXEL_OPERATION_H_
#define PIXEL_OPERATION_H_

#include <SDL2/SDL.h>
#include <stdio.h>

Uint32 get_pixel(SDL_Surface *surface,unsigned x, unsigned y);
void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
void update_surface(SDL_Surface* screen,SDL_Surface* image);

#endif

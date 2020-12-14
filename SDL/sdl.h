#ifndef SDL_H
#define SDL_H

#include <SDL2/SDL.h>

void init_sdl();
void on_keypress();
SDL_Surface* load_image(char *file);
void image_to_matrix(SDL_Surface *image, double matrix[]);
SDL_Surface* display_image(SDL_Surface *image);
SDL_Surface* blackwhite(SDL_Surface* image);
SDL_Surface* grayscale(SDL_Surface* image);
SDL_Surface* noisecancel(SDL_Surface* image);
SDL_Surface* rotate(SDL_Surface* image, int angle);
SDL_Surface* resize(SDL_Surface* image);

#endif

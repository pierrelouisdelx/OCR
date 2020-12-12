#ifndef SDL_H
#define SDL_H

void init_sdl();
void on_keypress();
SDL_Surface* load_image(char *file);
SDL_Surface* display_image(SDL_Surface *image);
SDL_Surface* blackwhite(SDL_Surface* image);
SDL_Surface* grayscale(SDL_Surface* image);
SDL_Surface* noisecancel(SDL_Surface* image);
SDL_Surface* resize(SDL_Surface *Surface);
SDL_Surface* rotate(SDL_Surface* image, int angle);

#endif

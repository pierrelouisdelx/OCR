void init_sdl();
SDL_Surface* load_image(char *file);
SDL_Surface* display_image(SDL_Surface *image);
void on_keypress();
SDL_Surface* rotate(SDL_Surface* image, int angle);

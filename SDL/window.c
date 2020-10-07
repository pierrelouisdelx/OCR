#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void open_window(const char *img) {
    SDL_Window *window;
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("OCR",SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,640,480,0);

    if(window == NULL) {
        printf("Error while loading window");
        SDL_GetError();
    }

    //Display image in window
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface *image = SDL_LoadBMP(img);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);

    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

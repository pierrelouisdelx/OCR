#include <stdlib.h>
#include <SDL2/SDL.h>

int main(int argc,char **argv)
{
    SDL_Window *window;
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("OCR",SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,640,480,0);

    if(window == NULL) {
        printf("Error while loading window");
        SDL_GetError();
        return 0;
    }

    //Display image in window
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface *image = SDL_LoadBMP("image.bmp");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);

    SDL_Rect dstrect = {5, 5, 10, 10};
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "window.h"

int main(int argc,char **argv)
{
    if(argc == 1 || argc > 2) {
        printf("Usage: program image.bmp\n");
        return 0;
    }
    open_window(argv[1]);
    return 0;
}

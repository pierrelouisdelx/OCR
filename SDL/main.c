#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sdl.h"
#include "pixel_operations.h"
#include "grayscale.h"
#include "blackwhite.h"
#include "paragraph.h"

int main(int argc,char **argv)
{
    if(argc == 1 || argc > 2) {
        printf("Usage: program image.bmp\n");
        return 0;
    }

    init_sdl();
    SDL_Surface* image = load_image(argv[1]);
    image = grayscale(image);
    image = blackwhite(image);
    //image = rotate(image, 2);
    image = paragraph_reco(image);
    display_image(image);

    return 0;
}

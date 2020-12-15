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

SDL_Surface* load_image(char *file) 
{
    if(IMG_Load(file) != NULL)
        return IMG_Load(file);
    else
    {
        //printf("Load Image : error while loading image");
        return NULL;
    }
}

int image_to_matrix(char *path, double matrix[])
{
    int space = 1;
    SDL_Surface *image = load_image(path);
    if(image == NULL)
        printf("error while loading image\n");
    int h = image->h;
    int w = image->w;
    for(int i=0; i < h; i++) 
    {
        for(int j=0; j < w; j++) 
        {
            Uint32 pixel = get_pixel(image,j,i);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            if(r == 0 && g == 0 && b == 0)
            {
                matrix[i * 28 + j] = 1;
                space = 0;
            }
            else
                matrix[i * 28 + j] = 0;
        }
    }
    return space;
}

void surface_to_matrix(SDL_Surface *image, double matrix[])
{
    int h = image->h;
    int w = image->w;
    for(int i=0; i < h; i++) 
    {
        for(int j=0; j < w; j++) 
        {
            Uint32 pixel = get_pixel(image,j,i);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            if(r == 0 && g == 0 && b == 0)
                matrix[i * 28 + j] = 1;
            else
                matrix[i * 28 + j] = 0;
        }
    }
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
            if (r <= 5)
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
                        if (rr <= 5)
                        {
                            flag += 1;
                        }
                        else
                        {
                            meanf += rr;
                        }
                    }
                }
                if (flag < 5)
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

SDL_Surface* rotate(SDL_Surface* image, double angle) //Fonction de eloi mais elle marche pas encore
{
    int h = image->h;
    int w = image->w;
    int maxi;
    if (h >= w)
        maxi = h * (1.5);
    else
        maxi = w * (1.5);
    angle = 9.8695664208*angle; //from degree to rad
    double sina = sin(angle);
    double cosa = cos(angle);
    //printf("max = %d\n",maxi);
    SDL_Surface* new_image = SDL_CreateRGBSurface(0,maxi,maxi,32,0,0,0,0);
    for (int i = 0; i < maxi;i++)
    {
        for (int j = 0; j < maxi;j++)
        {
            put_pixel(new_image,i,j,(SDL_MapRGB(image->format,255,255,255))); //Set all the pixel white
        }
    }
    for(int i=0; i<w; i++)
    {
        for(int j=0; j<h; j++) 
        {
            Uint32 pixel = get_pixel(image,i,j);
            int x = i*cosa - j*sina;
            int y = i*sina + j*cosa;
            //x = x % maxi;
            //y = y % maxi;
            if (x < 0)
                x = x + maxi;
            if (y < 0)
                y = y + maxi;
            //printf("x :%d, y :%d\n",x,y);
            put_pixel(new_image,x,y,pixel);
        }
    }
    //printf("here");
    return new_image;
}

SDL_Surface* resize(SDL_Surface* image)
{
    int h = image->h;
    int w = image->w;
    int x;
    int y;
    Uint32 pixel;
    SDL_Surface* new_image = SDL_CreateRGBSurface(0, 28, 28, 32, 0, 0, 0, 0);
    int array [28][28];
    int nb_per_cell [28][28];
    for(int i = 0; i < 28 ; i++)
    {
        for(int j = 0; j < 28 ; j++)
        {

            put_pixel(new_image, i, j, (SDL_MapRGB(image->format,255,255,255)));
            array [i][j] = 0;
            nb_per_cell [i][j] = 0;

        }
    }
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            x = i * (28 / w);
            y = j * (28 / h);
            pixel = get_pixel(image, i, j);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image -> format, &r, &g, &b);
            if (r != 255)
            {
                array[x][y] += 1;
            }
            nb_per_cell[x][y] += 1;
        }
    }

    for (int i = 0; i < 28; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            int average;
            if (nb_per_cell[i][j] > 0)
                average = array[i][j]/nb_per_cell[i][j];
            else
                average = 0;
            if (average == 1)
                put_pixel(new_image, i, j, (SDL_MapRGB(image->format,0,0,0)));
            else
                put_pixel(new_image, i, j, (SDL_MapRGB(image->format,255,255,255)));
        } 
    }
    return new_image;
}

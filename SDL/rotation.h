#include <SDL2/SDL.h>

#ifndef ROTATION_H
#define ROTATION_H

struct result {
    double rho;
    double theta;
};

//return rho and theta values
struct result *winner(int maxRho, int maxIndexTheta, int maxIndexRho, int acc[maxIndexTheta][maxIndexRho]);

//help to compute the angle
void help_rotate(int x, int y, int maxRho, int maxIndexTheta, int maxIndexRho, int acc[maxIndexTheta][maxIndexRho],SDL_Surface *img);

//gives the angle to rotate
double find_angle(SDL_Surface *image);

//just rotates the image
SDL_Surface *SDL_RotateImage(SDL_Surface *origine, float angle);
#endif

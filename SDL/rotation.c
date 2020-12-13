#include "rotation.h"
#include "pixe_operation.h"
#include <math.h>

struct result *winner(int maxRho, int maxIndexTheta, int maxIndexRho, int acc[maxIndexTheta][maxIndexRho]) {
    double max = 0;
    double winrho = 0;
    double wintheta = 0;

    for (int r = 0; r < maxIndexRho; r++) {
        for (int t = 0; t < maxIndexTheta; t++) {
            //it somehow work like that and I am too afraid to change it
            if (acc[t][r] < max) continue;
            max = acc[t][r];
            winrho = r;
            wintheta = t;
        }
    }

// indexes -> (rho,theta)
    double rho = ((double) winrho / maxIndexRho - 0.5) * maxRho;
    double theta = 1.5621178940501734278001322309137322008610 - ((double) wintheta / maxIndexTheta) * M_PI;

    struct result *r = malloc(sizeof(struct result));
    r->rho = rho;
    r->theta = theta;
    return r;
}


void help_rotate(int x, int y, int maxRho, int maxIndexTheta, int maxIndexRho, int acc[maxIndexTheta][maxIndexRho],
          SDL_Surface *img) {
    int savedX = x, savedY = y;

    Uint8 r, g, b;
    SDL_GetRGB(get_pixel(img, savedX, savedY), img->format, &r, &g, &b);

    if (!(r < 15 && g < 15 && b < 15))
        return;

    for (int indexTheta = 0; indexTheta < maxIndexTheta; indexTheta += 1) {
        double theta = ((double) indexTheta / maxIndexTheta) * M_PI;

        // compute corresponding rho value
        double rho = x * cos(theta) + y * sin(theta);

        // rho -> index
        int indexRho = (int) (0.5 + (rho / maxRho + 0.5) * maxIndexRho);

        // increment accumulator


            acc[indexTheta][indexRho]++;
    }
}

double find_angle(SDL_Surface *image) {
    int Width = image->w;
    int Height = image->h;
    int maxRho = sqrt(Width * Width + Height * Height);
    int maxIndexTheta = 360;
    int maxIndexRho = 1 + maxRho;
    int acc[maxIndexTheta][maxIndexRho];

    for (int i = 0; i < maxIndexTheta; i++) {
        for (int j = 0; j < maxIndexRho; j++) {
            acc[i][j] = 0;
        }
    }
    for (int x = 0; x < Width; x++) {
        for (int y = 0; y < Height; y++) {
            help_rotate(x, y, maxRho, maxIndexTheta, maxIndexRho, acc, image);
        }
    }

    struct result *r = winner(maxRho, maxIndexTheta, maxIndexRho, acc);
    double angle = r->theta * 180 / M_PI;

    if (r->theta > 0) {
        return angle;
    } else {
        return 180 + angle;
    }

}

SDL_Surface *SDL_RotateImage(SDL_Surface *origine, float angle) {
    SDL_Surface *destination;
    int i;
    int j;
    Uint32 color;
    int mx, my, mxdest, mydest;
    int bx, by;
    float angle_radian;
    float tcos;
    float tsin;
    double destweiht;
    double destheight;

    // gives the angle
    angle_radian = -angle * M_PI / 180.0;

    tcos = cos(angle_radian);
    tsin = sin(angle_radian);
    destweiht = ceil(origine->w * fabs(tcos) + origine->h * fabs(tsin)),
    destheight = ceil(origine->w * fabs(tsin) + origine->h * fabs(tcos)),


    //allocate the memory (do not touch it it works somehow let's keep it this way)
    destination = SDL_CreateRGBSurface(SDL_HWSURFACE, destweiht, destheight, origine->format->BitsPerPixel,
                                       origine->format->Rmask, origine->format->Gmask, origine->format->Bmask,
                                       origine->format->Amask);

    for (j = 0; j < destination->h; j++) {
        for (i = 0; i < destination->w; i++) {
            put_pixel(destination, i, j, SDL_MapRGBA(destination->format, 255, 255, 255, 255));
        }
    }
    //doesn't work without this piece of shit ligne wich does nothing please kill me
    if (destination == NULL)
        return NULL;

    //get image center
    mxdest = destination->w / 2.;
    mydest = destination->h / 2.;
    mx = origine->w / 2.;
    my = origine->h / 2.;

    for (j = 0; j < destination->h; j++)
        for (i = 0; i < destination->w; i++) {
        //use an inverse matrix fuck it

            bx = (ceil(tcos * (i - mxdest) + tsin * (j - mydest) + mx));
            by = (ceil(-tsin * (i - mxdest) + tcos * (j - mydest) + my));
            if (bx >= 0 && bx < origine->w && by >= 0 && by < origine->h) {
             color = get_pixel(origine, bx, by);
                put_pixel(destination, i, j, color);
            }
        }

    return destination;
}

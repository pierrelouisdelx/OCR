#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "neuralnetwork.h"
#include "row_matrix.h"
#include "../SDL/sdl.h"
#include "../SDL/paragraph.h"

void train_ocr()
{
    struct Neurones N;
    N.inputs = 784;
    N.hidden = 400;
    N.output = 256;

    srand(time(NULL));

    double output[N.output];
    memset(output,0,N.output*sizeof(double));

    double weights_oh[N.output * N.hidden];
    double weights_ih[N.hidden * N.inputs];
    double bias_i[N.hidden];
    double bias_o[N.output];
    int epochs = 1;

    init(N.hidden, N.inputs, weights_ih);
    init(N.output, N.hidden, weights_oh);
    init(N.hidden, 1, bias_i);
    init(N.output, 1, bias_o);

    train(N, output, weights_ih, weights_oh, bias_i, bias_o, epochs);
 
    SaveData(N,weights_ih,weights_oh,bias_i,bias_o);
}

void ocr(char *file)
{
    printf("OCR\n\n");
    struct Neurones N;
    N.inputs = 784;
    N.hidden = 400;
    N.output = 256;

    srand(time(NULL));

    double output[N.output];
    memset(output,0,N.output*sizeof(double));

    double weights_ih[N.hidden * N.inputs];
    double weights_oh[N.output * N.hidden];
    double bias_i[N.hidden];
    double bias_o[N.output];
    
    double hidden[N.hidden];
    double inputs[N.inputs];

    LoadData(N,weights_ih,weights_oh,bias_i,bias_o);

    SDL_Surface *image = load_image(file);
    image = grayscale(image);
    image = noisecancel(image);
    image = blackwhite(image);
    image = lines_reco(image);
    int nchars = lines_and_char_storage(image);

    char text[nchars];

    char img_f[50] = "SDL/bmp/chars/line_";

    int i=0; 
    while(i < 50)
    {   
        char tmp[50];
        char n[13];
        strcpy(tmp,img_f);
        sprintf(n,"%i",i);
        strcat(tmp,n);
        strcat(tmp,":");

        char tm[50];
        strcpy(tm, tmp);
        strcat(tm,"0");

        if(load_image(tm) != NULL)
        { 
            int j=0;
            while(j < 250)
            {
                char tmp2[50];
                strcpy(tmp2,tmp);
                sprintf(n,"%i",j);
                strcat(tmp2,n);
                if(load_image(tmp2) != NULL)
                {
                    image_to_matrix(tmp2, inputs);
                    feedForward(N, inputs, weights_ih, weights_oh, bias_i, bias_o, hidden, output);
                    char t[10];
                    sprintf(t,"%c",getoutput(N,output));
                    strcat(text,t);
                }
                else
                    break;
                j++;
            }
            strcat(text,"\n");
            i++;
        }
        else
            break;
    }
    save_output(text);
}


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
    printf("TRAINING OCR");
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
    int epochs = 10000;

    init(N.hidden, N.inputs, weights_ih);
    init(N.output, N.hidden, weights_oh);
    init(N.hidden, 1, bias_i);
    init(N.output, 1, bias_o);

    train(N, output, weights_ih, weights_oh, bias_i, bias_o, epochs);
 
    //print_matrix(N.hidden,1,bias_i);
    SaveData(N,weights_ih,weights_oh,bias_i,bias_o);
}

void ocr(char *file)
{
    printf("OCR");
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
    lines_and_char_storage(image);

    image_to_matrix(image, inputs); //Matrix from image

    feedForward(N, inputs, weights_ih, weights_oh, bias_i, bias_o, hidden, output);

    //char letter[] = getoutput(N,output);
    //save_output(letter); 
}

int main()
{
    train_ocr();
    ocr("training/c/line_1:6");
    return 0;
}


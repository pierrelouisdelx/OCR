#include <stdio.h>
#include <math.h>
#include "row_matrix.h"
#include <dirent.h>
#include <string.h>
#include "../SDL/sdl.h"

double sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double dsigmoid(double x)
{
    return x*(1-x);
}

void get_folders(char *dirs)
{
    struct dirent *de;
    DIR *d = opendir("training/");
    if(d == NULL)
        printf("Could not open current directory");
    else
    {
        int i=0;
        while ((de = readdir(d)) != NULL)
        {
            if(strcmp(de->d_name,".") && strcmp(de->d_name,".."))
            {
                dirs[i] = *(de->d_name);
                //printf("%s\n",dirs);
                i++;
            }
        }
        closedir(d);
        free(de);
    }
}

void feedForward(struct Neurones N, 
        double inputs[N.inputs], 
        double weights_ih[N.hidden * N.inputs], 
        double weights_oh[N.output * N.hidden],
        double bias_i[N.hidden], 
        double bias_o[N.output],
        double hidden[N.hidden],
        double output[N.output])
{
    mult(N.hidden, N.inputs, N.inputs, 1, weights_ih, inputs, hidden);
    add(N.hidden, 1, hidden, bias_i, hidden);
    function(N.hidden, 1, sigmoid, hidden);

    mult(N.output, N.hidden, N.hidden, 1, weights_oh, hidden, output);
    add(N.output, 1, output, bias_o, output);
    function(N.output, 1, sigmoid, output);
}

void backPropagation(struct Neurones N, 
        double inputs[N.inputs], 
        double weights_oh[N.output * N.hidden], 
        double weights_ih[N.hidden * N.inputs],
        double bias_i[N.hidden], 
        double bias_o[N.output],
        double output[N.output],
        double target[N.output])
{

    float lr = 0.3;

    double hidden[N.hidden];
	feedForward(N, inputs, weights_ih, weights_oh, bias_i, bias_o, hidden, output);

	//Calculate error
	double error_output[N.output]; 
	sub(N.output, 1, target, output, error_output);
	
    double error_hidden[N.hidden];
    double transpose_weights_oh[N.hidden * N.output];
	transpose(N.output, N.hidden, weights_oh, transpose_weights_oh);
	mult(N.hidden, N.output, N.output, 1, transpose_weights_oh, error_output, error_hidden);

    //Output
	//Calculate deltas
    double gradient_output[N.output];
	function(N.output, 1, dsigmoid, output);
	multeach(N.output, 1, output, error_output, gradient_output);
	factor(N.output, 1, gradient_output, lr, gradient_output);

	//Delta weight_ho
	double d_weight_oh[N.output * N.hidden];
    double transpose_hidden[1 * N.hidden];//CHANGED
	transpose(N.hidden, 1, hidden, transpose_hidden);
	mult(N.output, 1, 1, N.hidden, gradient_output, transpose_hidden, d_weight_oh);

	//Adjust weights and bias
	add(N.output, N.hidden, weights_oh, d_weight_oh, weights_oh);
	add(N.output, 1, bias_o, gradient_output, bias_o);

    //Hidden
	//Calculate deltas
	double gradient_hidden[N.hidden * 1];
	function(N.hidden, 1, dsigmoid, hidden);
	multeach(N.hidden, 1, hidden, error_hidden, gradient_hidden);
	factor(N.hidden, 1, gradient_hidden, lr, gradient_hidden);

	//Gradient weight_ih
	double d_weight_ih[N.hidden * N.inputs];
    double transpose_input[1 * N.inputs]; 
	transpose(N.inputs, 1, inputs, transpose_input);
	mult(N.hidden, 1, 1, N.inputs, gradient_hidden, transpose_input, d_weight_ih);

	//Adjust weights and bias
	add(N.hidden, N.inputs, weights_ih, d_weight_ih, weights_ih);
	add(N.hidden, 1, bias_i, gradient_hidden, bias_i);
}

void set_target(double target[], char dir)
{
    int c = dir;
    for(int i=0; i<256; i++)
    {
        if(i == c)
            target[i] = 1;
        else
            target[i] = 0;
    }
}

void train(struct Neurones N, 
        double output[N.output], 
        double weights_ih[N.hidden * N.inputs], 
        double weights_oh[N.output * N.hidden],
        double bias_i[N.hidden], 
        double bias_o[N.output], 
        int epochs)
{ 
    char dir_p[12] = "training/ /"; //training/letter
    char *img_p = dir_p; //training/letter/image

    char *dirs = malloc(4 * sizeof(char)); //For testing only with a b c d
    get_folders(dirs);

    double input[784] = {0}; //28x28 pixels/bmp

    struct dirent *de;
    DIR *d;

    for(int i=0; i<1; i++)  //epochs
    {
        shuffle(3,1,dirs);  //Shuffle letters order
        for(int j=0; j<4; j++)  //dirs
        {
            dir_p[9] = dirs[j]; //Get each directory in training/ directories
            printf("dir : %s\n",dir_p);
            
            d = opendir(dir_p);
            while((de = readdir(d)) != NULL)
            {

                if(de->d_type == DT_REG)
                {
                    char *img = malloc(strlen(dir_p) + strlen(de->d_name));
                    strcpy(img, dir_p);
                    strcat(img,de->d_name);
                    printf("%s\n",img);

                    image_to_matrix(img, input);//Matrix from image
                    printf("dirs[%i] %c\n\n",j,dirs[j]);

                    double target[N.output];
                    set_target(target, dirs[j]); //Set 1 on letter
                    backPropagation(N, input, weights_oh, weights_ih, bias_i, bias_o, output, target);
                }
            }
            closedir(d);
        }
        printf("\n");
    }
    print_matrix(1,256,output);

    print_matrix(1,784,input);
    test(N, output, weights_ih, weights_oh, bias_i, bias_o);
}

char getoutput(struct Neurones N, double output[N.output])
{
    double max = 0;
    char pos = 0;
    for(int i=0; i<N.output; i++)
    {
        if(max < output[i])
        {
            max = output[i];
            pos = i;
        }
    }
    return pos;
}

void test(struct Neurones N,
        double output[N.output],
        double weights_ih[N.hidden * N.inputs],
        double weights_oh[N.output * N.hidden],
        double bias_i[N.hidden],
        double bias_o[N.output])
{
    double hidden[N.hidden];
    double inputs[N.inputs];

    print_matrix(256,1,output);

    image_to_matrix("training/a/line_0:12", inputs);//Matrix from image
    feedForward(N, inputs, weights_ih, weights_oh, bias_i, bias_o, hidden, output);

    char letter = getoutput(N,output);
    printf("letter : %i\n\n", letter);

    //SaveData(N,weights_ih,weights_oh,bias_i,bias_o);
    //LoadData(N,weights_ih,weights_oh,bias_i,bias_o);
}

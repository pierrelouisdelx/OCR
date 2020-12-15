#include <stdio.h>
#include <math.h>
#include "row_matrix.h"
#include "../SDL/sdl.h"
#include <time.h>

double sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double dsigmoid(double x)
{
    return x*(1-x);
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

void set_target(struct Neurones N, double target[], char dir)
{
    int c = dir;
    for(int i=0; i<N.output; i++)
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
    char training[50] = "NeuralNetwork/training/"; //training/letter

    double input[N.inputs]; //28x28 pixels/bmp

    int dir[93];
    for(int tmp=33; tmp<=125; tmp++)
    {
        dir[tmp-33] = tmp;
    }

    for(int e=0; e<epochs; e++)
    {
        printf("Epochs %i on %i\n", e, epochs);
        for(int j=0; j<409; j++)
        {
            shuffle(dir, 93);
            for(int i=0; i<93; i++) //going through all folders
            {
                char tmp[100];
                char n[15];
                strcpy(tmp,training);
                sprintf(n,"%i",dir[i]);
                strcat(tmp,n);
                strcat(tmp,"/");
                sprintf(n,"%i",j);
                strcat(tmp,n);
                strcat(tmp,".jpg");
                image_to_matrix(tmp, input);//Matrix from image
                
                double target[N.output];
                set_target(N,target, dir[i]);

                backPropagation(N, input, weights_oh, weights_ih, bias_i, bias_o, output, target);
            }
        }
    }
}

int getoutput(struct Neurones N, double output[N.output])
{
    double max = 0;
    int pos = 0;
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

void save_output(char c[])
{
    FILE *fp;
    fp = fopen("text.txt","w");
    fprintf(fp,"%s\n",c);
    fclose(fp);
}

void statistics(struct Neurones N,
        double output[N.output],
        double weights_ih[N.hidden * N.inputs],
        double weights_oh[N.output * N.hidden],
        double bias_i[N.hidden],
        double bias_o[N.output])
{
    double hidden[N.hidden];
    double inputs[N.inputs];
    memset(inputs, 0, N.inputs*sizeof(double));

    image_to_matrix("training/c/line_1:6", inputs); //Matrix from image
    feedForward(N, inputs, weights_ih, weights_oh, bias_i, bias_o, hidden, output);

    char letter = getoutput(N,output);
    char text[5] = "hello";
    save_output(text);
    printf("letter : %i %c\n\n",letter, letter);

    //SaveData(N,weights_ih,weights_oh,bias_i,bias_o);
    //LoadData(N,weights_ih,weights_oh,bias_i,bias_o);
}

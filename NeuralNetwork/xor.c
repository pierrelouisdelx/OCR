#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "matrix.h"

#define nInputs 2

struct Neurones {
    int inputs;
    int hidden;
    int weights;
    int bias;
    int outputs;
};

double sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double dsigmoid(double x)
{
    return x*(1-x);
}

int xor(int inputs[1][nInputs])
{
    int x = inputs[1][0];
    int y = inputs[1][1];
    if(x == y) 
        return 0;
    return 1;
}

double feedForward(int inputs[1][nInputs], double weights_ih[][nInputs], double weights_oh[][nInputs],
        double bias_i[][nInputs], double bias_o[][nInputs], double hidden[][nInputs])
{ 
    for(int i=0; i<nInputs; i++)
    {
        for(int j=0; j<nInputs; j++)
        {
            
            hidden[i][j] = sigmoid(weights_ih[i][j] * inputs[i][0] + bias_i[i][j]);
        }
    }

    double output;
    for(int i=0; i<nInputs; i++)
    {
        for(int j=0; j<nInputs; j++)
        {
            output += sigmoid(weights_oh[i][j] * hidden[i][j] +  bias_o[i][j]);
        }
    }
    return output;
}

void backPropagation(int inputs[][nInputs], double weights_oh[][nInputs], double weights_ih[][nInputs],
        double bias_i[][nInputs], double bias_o[][nInputs], double hidden[][nInputs], int epochs)
{
    double output, error_output, error_hidden;
    double gradient_output, d_weight_oh[nInputs][nInputs], d_bias_o;
    double gradient_hidden, d_weight_ih[nInputs][nInputs], d_bias_h;

    float lr = 0.1;
    int target = xor(inputs);

    for(int i=0; i < epochs; i++)
    {
        output = feedForward(inputs, weights_ih, weights_oh, bias_i, bias_o, hidden);
        error_output = target - output;
        error_output = transpose_matrix(weights_oh) * error_output;

        gradient_output = lr * (error_output * dsigmoid(output));
        factor_matrix(transpose_matrix(hidden), gradient_output, d_weight_oh);

        add_matrix(weights_oh, d_weight_oh, weights_oh);
        add_matrix(bias_o, d_bias_o, bias_o);

        gradient_hidden = lr * (error_hidden * function_matrix(dsigmoid(hidden)));
        factor_matrix(transpose_matrix(inputs), gradient_hidden, d_weight_ih);

        add_matrix(weights_ih, d_weight_ih, weights_ih);
        add_matrix(bias_i, d_bias_h, bias_i);
    }
}

int main()
{
    struct Neurones Neurone;
    Neurone.inputs = 2;
    Neurone.hidden = 2;
    Neurone.weights = 4;
    Neurone.bias = 4;
    Neurone.outputs = 1;

    int inputs[1][Neurone.inputs];
    double weights_ih[nInputs][nInputs];
    double weights_oh[nInputs][nInputs];
    double bias_h[nInputs][nInputs];
    double bias_o[nInputs][nInputs];
    double hidden[nInputs][nInputs];
    double result;

    init_matrix(weights_ih);
    init_matrix(weights_oh);
    init_matrix(bias_h);
    init_matrix(bias_o);
    print_matrix(weights_ih, 2, 4);

    result = feedForward(inputs, weights_ih, weights_oh, bias_h, bias_o, hidden);
    printf("Feed forward : %lf\n", result);
    printf("Expected value : %d\n", xor(inputs));

    return 0;
}


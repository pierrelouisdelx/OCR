#include <stdio.h>
#include <math.h>
#include "matrix.h"
#include "xor.h"

double sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double dsigmoid(double x)
{
    return x*(1-x);
}

int xor(struct Neurones N, double inputs[][N.inputs])
{
    int x = inputs[0][0];
    int y = inputs[0][1];
    if(x == y)
        return 0;
    return 1;
}

void feedForward(struct Neurones N, double inputs[][N.inputs], 
        double weights_ih[][N.inputs], double weights_oh[][N.inputs],
        double bias_i[][N.inputs], double bias_o[][N.inputs], 
        double hidden[][N.inputs], double output[][N.inputs])
{ 

    mult_matrix(weights_ih, inputs, hidden, N.inputs, N.inputs, N.inputs, N.inputs);
    //print_matrix(hidden,2,2);

    add_matrix(N, hidden, bias_i, hidden);
    //print_matrix(hidden,2,2);

    function_matrix(sigmoid, hidden);
    //print_matrix(hidden,2,2);

    mult_matrix(weights_oh, hidden, output, N.inputs, N.inputs, N.inputs, N.inputs);
    //print_matrix(output,2,2);

    add_matrix(N, output, bias_o, output);
    //print_matrix(output,2,2);

    function_matrix(sigmoid, output);
    //print_matrix(output,1,1);
}

void backPropagation(struct Neurones N, double inputs[][N.inputs], 
        double weights_oh[][N.inputs], double weights_ih[][N.inputs],
        double bias_i[][N.inputs], double bias_o[][N.inputs], 
        double hidden[][N.inputs], double output[][N.inputs], int epochs)
{
    double error_output, error_hidden;
    double gradient_output[N.inputs][N.inputs], d_weight_oh[N.inputs][N.inputs], d_bias_o[N.inputs][N.inputs];
    double gradient_hidden[N.inputs][N.inputs], d_weight_ih[N.inputs][N.inputs], d_bias_h[N.inputs][N.inputs];
    double inputs2[N.inputs][N.inputs];

    float lr = 0.1;
    int target = xor(N, inputs);
    copy_matrix(N, inputs, inputs2);

    for(int i=0; i < epochs; i++)
    {
        feedForward(N, inputs, weights_ih, weights_oh, bias_i, bias_o, hidden, output);
        printf("%f\n",output[0][0]);
        
        //Calculate error
        error_output = target - output[0][0];
        transpose_matrix(N, weights_oh, weights_oh);
        factor_matrix(N, weights_oh, error_output, weights_oh);
        error_hidden = weights_oh[0][0];

        //Calculate deltas
        function_matrix(dsigmoid, output);
        factor_matrix(N, output, error_output, gradient_output);
        factor_matrix(N, gradient_output, lr, gradient_output);

        //Delta weight_ho
        transpose_matrix(N, hidden, hidden);
        factor_matrix(N, hidden, gradient_output[0][0], d_weight_oh); 
        
        //Delta bias_o
        copy_matrix(N, gradient_output, d_bias_o);

        //Adjust weights and bias
        add_matrix(N, weights_oh, d_weight_oh, weights_oh);
        add_matrix(N, bias_o, d_bias_o, bias_o);

        //Calculate deltas
        function_matrix(dsigmoid, hidden);
        factor_matrix(N, hidden, error_hidden, gradient_hidden);
        factor_matrix(N, gradient_hidden, lr, gradient_hidden);

        //Gradient weight_ih
        transpose_matrix(N, inputs2, inputs2);
        factor_matrix(N, inputs2, gradient_hidden[0][0], d_weight_ih);

        //Delta bias_h
        copy_matrix(N, gradient_hidden, d_bias_h);

        //Adjust weights and bias
        add_matrix(N, weights_ih, d_weight_ih, weights_ih);
        add_matrix(N, bias_i, d_bias_h, bias_i);
    }
}

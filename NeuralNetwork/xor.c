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

void feedForward(struct Neurones N, double inputs[N.inputs][1], 
        double weights_ih[N.hidden][N.inputs], double weights_oh[N.output][N.inputs],
        double bias_i[N.hidden][1], double bias_o[N.output][1], 
        double hidden[N.hidden][1], double output[N.output][1])
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

void backPropagation(struct Neurones N, double inputs[N.inputs][1], 
        double weights_oh[N.output][N.hidden], double weights_ih[N.hidden][N.inputs],
        double bias_i[N.hidden][1], double bias_o[N.output][1], 
        double hidden[N.hidden][1], double output[N.output][1], int epochs)
{
    double error_output[N.output][1], error_hidden[N.hidden][1];
    double gradient_output[N.output][1], d_weight_oh[N.inputs][N.inputs], d_bias_o[N.inputs][N.inputs];
    double gradient_hidden[N.hidden][1], d_weight_ih[N.inputs][N.inputs], d_bias_h[N.inputs][N.inputs];
    double target[N.output][1], transpose_hidden[N.hidden][N.output], transpose_input[1][N.inputs];

    float lr = 0.1;
    target[0][0] = xor(N, inputs);

    for(int i=0; i < epochs; i++)
    {
        feedForward(N, inputs, weights_ih, weights_oh, bias_i, bias_o, hidden, output);
        printf("%f\n",output[0][0]);
        
        //Calculate error
        sub_matrix(N, target, output, error_output);
        transpose_matrix(N, weights_oh, transpose_hidden);
        mult_matrix(transpose_hidden, error_output, error_hidden, N.hidden, N.output, N.output, 1);

        //Calculate deltas
        function_matrix(dsigmoid, output);
        multeach_matrix(N, output, error_output, gradient_output);
        factor_matrix(N, gradient_output, lr, gradient_output);

        //Delta weight_ho
        transpose_matrix(N, hidden, transpose_hidden);
        mult_matrix(gradient_output, transpose_hidden, d_weight_oh, N.output, 1, N.hidden, N.output); 
        
        //Delta bias_o
        copy_matrix(N, gradient_output, d_bias_o);

        //Adjust weights and bias
        add_matrix(N, weights_oh, d_weight_oh, weights_oh);
        add_matrix(N, bias_o, d_bias_o, bias_o);

        //Calculate deltas
        function_matrix(dsigmoid, hidden);
        multeach_matrix(N, hidden, error_hidden, gradient_hidden);
        factor_matrix(N, gradient_hidden, lr, gradient_hidden);

        //Gradient weight_ih
        transpose_matrix(N, inputs, transpose_input);
        mult_matrix(gradient_hidden, transpose_input, d_weight_ih, N.hidden, 1, 1, N.inputs);

        //Delta bias_h
        copy_matrix(N, gradient_hidden, d_bias_h);

        //Adjust weights and bias
        add_matrix(N, weights_ih, d_weight_ih, weights_ih);
        add_matrix(N, bias_i, d_bias_h, bias_i);
    }
}

void train(struct Neurones N, double inputs[N.inputs][1], double output[N.output][2])
{
    double weights_oh[N.output][N.hidden];
    double weights_ih[N.hidden][N.inputs];
    double bias_i[N.hidden][1];
    double bias_o[N.output][1];
    double hidden[N.hidden][1];
    int epochs = 100;

    init_matrix(weights_ih);
    init_matrix(weights_oh);
    init_matrix(bias_i);
    init_matrix(bias_o);

    backPropagation(N, inputs, weights_oh, weights_ih, bias_i, bias_o, hidden, output, epochs);

}

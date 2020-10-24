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

int xor(struct Neurones N, double inputs[1][N.inputs])
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
    mult_matrix(N.inputs, 1, N.hidden, 1, weights_ih, inputs, hidden);
    add_matrix(N.hidden, 1, hidden, bias_i, hidden);
    function_matrix(N.hidden, 1, sigmoid, hidden);

    mult_matrix(N.output, N.inputs, N.hidden, 1, weights_oh, hidden, output);
    add_matrix(N.output, 1, output, bias_o, output);
    function_matrix(N.output, 1, sigmoid, output);
}

void backPropagation(struct Neurones N, double inputs[N.inputs][1], 
        double weights_oh[N.output][N.hidden], double weights_ih[N.hidden][N.inputs],
        double bias_i[N.hidden][1], double bias_o[N.output][1], 
        double hidden[N.hidden][1], double output[N.output][1],
    	double error_output[N.output][1], double error_hidden[N.hidden][1],
        double gradient_output[N.output][1], double d_weight_oh[N.inputs][N.inputs], 
        double d_bias_o[N.inputs][N.inputs], double gradient_hidden[N.hidden][1], 
        double d_weight_ih[N.inputs][N.inputs], double d_bias_h[N.inputs][N.inputs], 
        double target[N.output][1], double transpose_hidden[N.hidden][N.output], 
        double transpose_input[1][N.inputs], float lr)
{

	feedForward(N, inputs, weights_ih, weights_oh, bias_i, bias_o, hidden, output);
	printf("%f\n",output[0][0]);

	//Calculate error
	sub_matrix(N.output, 1, target, output, error_output);
	transpose_matrix(N.hidden, N.output, weights_oh, transpose_hidden);
	mult_matrix(N.hidden, N.output, N.output, 1, transpose_hidden, error_output, error_hidden);

	//Calculate deltas
	function_matrix(N.output, 1, dsigmoid, output);
	multeach_matrix(N.output, 1, output, error_output, gradient_output);
	factor_matrix(N.output, 1, gradient_output, lr, gradient_output);

	//Delta weight_ho
	transpose_matrix(N.hidden, 1, hidden, transpose_hidden);
	mult_matrix(N.output, 1, N.hidden, N.output, gradient_output, transpose_hidden, d_weight_oh);

	//Delta bias_o
	copy_matrix(N.output, 1, gradient_output, d_bias_o);

	//Adjust weights and bias
	add_matrix(N.output, N.hidden, weights_oh, d_weight_oh, weights_oh);
	add_matrix(N.output, 1, bias_o, d_bias_o, bias_o);

	//Calculate deltas
	function_matrix(N.hidden, 1, dsigmoid, hidden);
	multeach_matrix(N.hidden, 1, hidden, error_hidden, gradient_hidden);
	factor_matrix(N.hidden, 1, gradient_hidden, lr, gradient_hidden);

	//Gradient weight_ih
	transpose_matrix(N.inputs, 1, inputs, transpose_input);
	mult_matrix(N.hidden, 1, 1, N.inputs, gradient_hidden, transpose_input, d_weight_ih);

	//Delta bias_h
	copy_matrix(N.hidden, 1, gradient_hidden, d_bias_h);

	//Adjust weights and bias
	add_matrix(N.inputs, N.inputs, weights_ih, d_weight_ih, weights_ih);
	add_matrix(N.inputs, N.inputs, bias_i, d_bias_h, bias_i);
}

void train(struct Neurones N, double inputs[N.inputs][1], double output[N.output][1], 
        double weights_ih[N.hidden][N.inputs], double weights_oh[N.output][N.hidden],
        double bias_i[N.hidden][1], double bias_o[N.output][1], double hidden[N.hidden][1], int epochs)
{
    double error_output[N.output][1], error_hidden[N.hidden][1];
    double gradient_output[N.output][1], d_weight_oh[N.inputs][N.inputs], d_bias_o[N.inputs][N.inputs];
    double gradient_hidden[N.hidden][1], d_weight_ih[N.inputs][N.inputs], d_bias_h[N.inputs][N.inputs];
    double target[N.output][1], transpose_hidden[N.hidden][N.output], transpose_input[1][N.inputs];

    float lr = 0.1;
    target[0][0] = xor(N, inputs);
    
    for(int i=0; i<epochs; i++)
    {
        shuffle_matrix(N.inputs, 0, inputs, N.inputs);
        for(int j=0; j<N.inputs; j++) 
        {
            backPropagation(N, inputs, weights_oh, weights_ih, bias_i, bias_o, hidden, output,
                error_output, error_hidden, gradient_output, d_weight_oh, d_bias_o, gradient_hidden, 
                d_weight_ih, d_bias_h, target, transpose_hidden, transpose_input, lr);
        }
    }
}

#include <stdio.h>
#include <math.h>
#include "matrix.h"
#include "o_xor.h"

double sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double dsigmoid(double x)
{
    return x*(1-x);
}

double xor(struct Neurones N, double inputs[1][N.inputs])
{
    double x = inputs[0][0];
    double y = inputs[0][1];
    if(x == y)
        return 0;
    return 1;
}

void feedForward(struct Neurones N, 
        double inputs[N.inputs][1], 
        double weights_ih[N.hidden][N.inputs], 
        double weights_oh[N.output][N.hidden],
        double bias_i[N.hidden][1], 
        double bias_o[N.output][1],
        double hidden[N.hidden][1],
        double output[N.output][1])
{
    mult_matrix(N.hidden, N.inputs, N.inputs, 1, weights_ih, inputs, hidden);
    add_matrix(N.hidden, 1, hidden, bias_i, hidden);
    function_matrix(N.hidden, 1, sigmoid, hidden);

    mult_matrix(N.output, N.hidden, N.hidden, 1, weights_oh, hidden, output);
    add_matrix(N.output, 1, output, bias_o, output);
    function_matrix(N.output, 1, sigmoid, output);
}

void backPropagation(struct Neurones N, 
        double inputs[N.inputs][1], 
        double weights_oh[N.output][N.hidden], 
        double weights_ih[N.hidden][N.inputs],
        double bias_i[N.hidden][1], 
        double bias_o[N.output][1],
        double output[N.output][1],
        double target[N.output][1])
{

    float lr = 0.3;

    double hidden[N.hidden][1];
	feedForward(N, inputs, weights_ih, weights_oh, bias_i, bias_o, hidden, output);

	//Calculate error
	double error_output[N.output][1]; 
	sub_matrix(N.output, 1, target, output, error_output);
	
    double error_hidden[N.hidden][1];
    double transpose_weights_oh[N.hidden][N.output];
	transpose_matrix(N.output, N.hidden, weights_oh, transpose_weights_oh);
	mult_matrix(N.hidden, N.output, N.output, 1, transpose_weights_oh, error_output, error_hidden);

    //Output
	//Calculate deltas
    double gradient_output[N.output][1];
	function_matrix(N.output, 1, dsigmoid, output);
	multeach_matrix(N.output, 1, output, error_output, gradient_output);
	factor_matrix(N.output, 1, gradient_output, lr, gradient_output);

	//Delta weight_ho
	double d_weight_oh[N.output][N.hidden];
    double transpose_hidden[1][N.hidden];//CHANGED
	transpose_matrix(N.hidden, 1, hidden, transpose_hidden);
	mult_matrix(N.output, 1, 1, N.hidden, gradient_output, transpose_hidden, d_weight_oh);

	//Adjust weights and bias
	add_matrix(N.output, N.hidden, weights_oh, d_weight_oh, weights_oh);
	add_matrix(N.output, 1, bias_o, gradient_output, bias_o);

    //Hidden
	//Calculate deltas
	double gradient_hidden[N.hidden][1];
	function_matrix(N.hidden, 1, dsigmoid, hidden);
	multeach_matrix(N.hidden, 1, hidden, error_hidden, gradient_hidden);
	factor_matrix(N.hidden, 1, gradient_hidden, lr, gradient_hidden);

	//Gradient weight_ih
	double d_weight_ih[N.hidden][N.inputs];
    double transpose_input[1][N.inputs]; 
	transpose_matrix(N.inputs, 1, inputs, transpose_input);
	mult_matrix(N.hidden, 1, 1, N.inputs, gradient_hidden, transpose_input, d_weight_ih);

	//Adjust weights and bias
	add_matrix(N.hidden, N.inputs, weights_ih, d_weight_ih, weights_ih);
	add_matrix(N.hidden, 1, bias_i, gradient_hidden, bias_i);
}

void train(struct Neurones N, 
        double output[N.output][1], 
        double weights_ih[N.hidden][N.inputs], 
        double weights_oh[N.output][N.hidden],
        double bias_i[N.hidden][1], 
        double bias_o[N.output][1], 
        int epochs)
{
    double target[N.output][1];

    double hidden[N.hidden][1];
    double input[4][2] =
    {
        {1,1},
        {1,0},
        {0,1},
        {0,0},
    };

    double input_arr[N.inputs][1];

    for(int i=0; i<epochs; i++)
    {
        shuffle(4, 2, input);
        for(int j=0; j<4; j++) 
        {
            input_arr[0][0] = input[j][0];
            input_arr[1][0] = input[j][1];

            target[0][0] = xor(N, input_arr);
            backPropagation(N, input_arr, weights_oh, weights_ih, bias_i, bias_o, output, target);
        }
    }

    double inputs[N.inputs][1];

    printf("Test for 0 0 : ");
    inputs[0][0] = 0;
    inputs[1][0] = 0;
    feedForward(N, inputs, weights_ih, weights_oh, bias_i, bias_o, hidden, output);
    printf("%f\n", output[0][0]);

    printf("Test for 0 1 : ");
    inputs[0][0] = 0;
    inputs[1][0] = 1;
    feedForward(N, inputs, weights_ih, weights_oh, bias_i, bias_o, hidden, output);
    printf("%f\n", output[0][0]);

    printf("Test for 1 0 : ");
    inputs[0][0] = 1;
    inputs[1][0] = 0;
    feedForward(N, inputs, weights_ih, weights_oh, bias_i, bias_o, hidden, output);
    printf("%f\n", output[0][0]);

    printf("Test for 1 1 : ");
    inputs[0][0] = 1;
    inputs[1][0] = 1;
    feedForward(N, inputs, weights_ih, weights_oh, bias_i, bias_o, hidden, output);
    printf("%f\n", output[0][0]);

    //SaveData(N,weights_ih,weights_oh,bias_i,bias_o);
    //LoadData(N,weights_ih,weights_oh,bias_i,bias_o);

}


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
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
    int x = inputs[1][0];
    int y = inputs[1][1];
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
    print_matrix(hidden,2,2);
    
    add_matrix(N, hidden, bias_i, hidden);
    print_matrix(hidden,2,2);
    
    function_matrix(sigmoid, hidden);
    print_matrix(hidden,2,2);

    mult_matrix(weights_oh, hidden, output, N.inputs, N.inputs, N.inputs, N.inputs);
    print_matrix(output,2,2);

    add_matrix(N, output, bias_o, output);
    print_matrix(output,2,2);

    function_matrix(sigmoid, output);
    print_matrix(output,1,1);
}

/*void backPropagation(struct Neurones N, int inputs[][N.inputs], double weights_oh[][N.inputs], double weights_ih[][N.inputs],
        double bias_i[][N.inputs], double bias_o[][N.inputs], double hidden[][N.inputs], int epochs)
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
}*/

int main()
{
    struct Neurones N;
    N.inputs = 2;
    N.hidden = 2;
    N.output = 1;

    srand(time(NULL));

    double inputs[1][N.inputs];
    double weights_ih[N.hidden][N.hidden];
    double weights_oh[N.hidden][N.hidden];
    double bias_h[N.hidden][N.hidden];
    double bias_o[N.hidden][N.hidden];
    double hidden[N.hidden][N.hidden];
    double output[N.output][N.output];
    double result;

    init_matrix(weights_ih);
    init_matrix(weights_oh);
    init_matrix(bias_h);
    init_matrix(bias_o);
    //print_matrix(weights_ih, 2, 4);

    feedForward(N, inputs, weights_ih, weights_oh, bias_h, bias_o, 
            hidden, output);
    printf("Feed forward : %lf\n", output[0][0]);
    printf("Expected value : %d\n", xor(N,inputs));

    return 0;
}


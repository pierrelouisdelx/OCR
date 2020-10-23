#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "xor.h"
#include "matrix.h"

int main(int argc, char *argv[])
{
    struct Neurones N;
    N.inputs = 2;
    N.hidden = 2;
    N.output = 1;

    srand(time(NULL));

    double inputs[2][1] = {{0},{1}};
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

    /*feedForward(N, inputs, weights_ih, weights_oh, bias_h, bias_o,
            hidden, output);
    printf("Feed forward : %lf\n", output[0][0]);
    printf("Expected value : %d\n", xor(N,inputs));*/

    backPropagation(N, inputs, weights_ih, weights_oh, bias_h, bias_o,
            hidden, output, 10);
    printf("Back Propagation : %lf\n", output[0][0]);
    printf("Expected value : %d\n", xor(N,inputs));

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "o_xor.h"
#include "matrix.h"

int main()
{
    struct Neurones N;
    N.inputs = 2;
    N.hidden = 3;
    N.output = 1;

    srand(time(NULL));

    double output[N.output][1];

    double weights_oh[N.output][N.hidden];
    double weights_ih[N.hidden][N.inputs];
    double bias_i[N.hidden][1];
    double bias_o[N.output][1];
    int epochs = 10000;

    init_matrix(N.hidden, N.inputs, weights_ih);
    init_matrix(N.output, N.hidden, weights_oh);
    init_matrix(N.hidden, 1, bias_i);
    init_matrix(N.output, 1, bias_o);

    train(N, output, weights_ih, weights_oh, bias_i, bias_o, epochs);
   
    return 0;
}


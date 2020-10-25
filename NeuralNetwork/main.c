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

    double output[1][1];

    double weights_oh[N.output][N.hidden];
    double weights_ih[N.hidden][N.inputs];
    double bias_i[N.hidden][1];
    double bias_o[N.output][1];
    double hidden[N.hidden][1];
    int epochs = 100;

    init_matrix(N.hidden, N.output, weights_ih);
    init_matrix(N.output, N.hidden, weights_oh);
    init_matrix(N.hidden, 1, bias_i);
    init_matrix(N.output, 1, bias_o);

    //save_matrix(N.inputs, 1, inputs, "weights_oh.txt");
    //LoadData("weights_oh.txt", N.inputs, 1, inputs);
    //print_matrix(8,1,inputs);

    train(N, output, weights_ih, weights_oh, bias_i, weights_oh, hidden, epochs);

    printf("Back Propagation : %lf\n", output[0][0]);
    //printf("Expected value : %d\n", xor(N,inputs));

    return 0;
}


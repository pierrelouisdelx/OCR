#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "xor.h"
#include "matrix.h"

int main()
{
    struct Neurones N;
    N.inputs = 2;
    N.hidden = 2;
    N.output = 1;

    srand(time(NULL));

    double output[N.output][1];

    double weights_oh[N.output][N.hidden];
    double weights_ih[N.hidden][N.inputs];
    double bias_i[N.hidden][1];
    double bias_o[N.output][1];
    double hidden[N.hidden][1];
    int epochs = 10000;

    init_matrix(N.hidden, N.inputs, weights_ih);
    init_matrix(N.output, N.hidden, weights_oh);
    init_matrix(N.hidden, 1, bias_i);
    init_matrix(N.output, 1, bias_o);

    train(N, output, weights_ih, weights_oh, bias_i, weights_oh, hidden, epochs);
 
    double inputs[N.inputs][1];

    printf("Please enter 2 values : ");
    scanf("%lf %lf",&inputs[0][0], &inputs[1][0]);

    SaveData(N,weights_ih,weights_oh,bias_i,bias_o);
    //LoadData(N,weights_ih,weights_oh,bias_i,bias_o);

    feedForward(N, inputs, weights_ih, weights_oh, bias_i, bias_o, hidden, output);
    printf("%f\n", output[0][0]);
    
    return 0;
}


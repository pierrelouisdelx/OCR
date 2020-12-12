#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "neuralnetwork.h"
#include "row_matrix.h"
#include <string.h>

int main()
{
    struct Neurones N;
    N.inputs = 784;
    N.hidden = 400;
    N.output = 256;

    srand(time(NULL));

    double output[N.output * 1];
    memset(output,0,N.output*sizeof(double));

    double weights_oh[N.output * N.hidden];
    double weights_ih[N.hidden * N.inputs];
    double bias_i[N.hidden];
    double bias_o[N.output];
    int epochs = 10000;

    init(N.hidden, N.inputs, weights_ih);
    init(N.output, N.hidden, weights_oh);
    init(N.hidden, 1, bias_i);
    init(N.output, 1, bias_o);

    train(N, output, weights_ih, weights_oh, bias_i, bias_o, epochs);
  
    //SaveData(N,weights_ih,weights_oh,bias_i,bias_o);
    //LoadData(N,weights_ih,weights_oh,bias_i,bias_o);
    return 0;
}


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

    double inputs[2][1] = {{1},{1}};
    double output[2][2];

    train(N, inputs, output);

    printf("Back Propagation : %lf\n", output[0][0]);
    printf("Expected value : %d\n", xor(N,inputs));

    return 0;
}


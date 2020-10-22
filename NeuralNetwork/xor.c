#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define nInputs 2
#define nHidden 2
#define nOutput 1

double Random()
{
    return (double)rand()/(double)RAND_MAX;
}

double activation(double x)
{
    return 1 / (1 + exp(-x));
}

double init_weights(double weights[])
{
    for(int i=0; i<nInputs*2; i++)
        weights[i] = Random();
}

void print_array(double *array)
{
    int len = sizeof(array)/sizeof(array[0]);
    printf("Len : %d\n",len);
    for(int i=0; i<len; i++)
        printf("%f\n",array[i]);
}

int main()
{
    int inputs[nInputs];
    double bias;
    bias = Random();
    double weights[nInputs*2];

    init_weights(weights);
    print_array(weights);

    double hidden = 0;
    double output;

    for(int i=0; i<nInputs; i++)
    {
        hidden += inputs[i] * weights[i];
    }

    hidden += bias;

    for(int j=0; j<nHidden; j++)
    {
        hidden += activation(hidden);
    }

    for(int k=0; k<nInputs; k++)
    {
        output += hidden * weights[k];
    }

    output += bias;

    for(int j=0; j<nHidden; j++)
    {
        output += activation(output);
    }

    printf("Output : %f\n", output);
    return 0;
}


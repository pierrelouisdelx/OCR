#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define nInputs 2
#define nHidden 2
#define nOutput 1

//int inputs[nInputs];
//float weights[nInputs*2];
//double bias = random();

double Random()
{
    return ((double)rand()/((double)RAND_MAX));
}

double activation(double x)
{
    return 1 / (1 + exp(-x));
}

int main()
{
    return 0;
}

/*
double hidden = 0;

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
    output += hidden[i] * weights[i];
}

output += bias;

for(int j=0; j<nHidden; j++)
{
    output += activation(output);
}

return output;*/


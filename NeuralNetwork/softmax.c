#include <stdlib.h>
#include <math.h>

double softmax(double biais, double factor) 
{
    return exp(biais) / factor;
}

void neurons_softmax(double neurons[])
{
    double sum = 0;
    size_t len = sizeof(neurons)/sizeof(neurons[0]);
    for(int i=0; i < len; i++)
    {
        sum += exp(neurons[i]);
    }

    for(int j=0; j < n; j++)
    {
        neurons[i] = softmax(sum);
    }
}

double init_weight()
{
    return ((double)rand()/((double)RAND_MAX);
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define nInputs 2
#define nHidden 2
#define nOutput 1

double Random()
{
    srand(time(NULL));
    return (double)rand()/(double)RAND_MAX;
}

double sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double dsigmoid(double x)
{
    return (1/(1+exp(-x)))*(1-(1/(1+exp(-x))));
}

double sigmoid_matrix(double m[][nInputs])
{
    for(int i=0; i<nInputs; i++)
    {
        for(int j=0; j<nInputs; j++)
        {
            m[i][j] = sigmoid(m[i][j]);
        }
    }
}

double init_weights(double weights[][nInputs])
{
    for(int i=0; i<nInputs; i++)
    {
        for(int j=0; j<nInputs; j++)
        {
            weights[i][j] = Random();
        }
    }
}

void print_array(double *array)
{
    int len = sizeof(array)/sizeof(array[0]);
    printf("Len : %d\n",len);
    for(int i=0; i<len; i++)
        printf("%f\n",array[i]);
}

void print_matrix(double matrix[][nInputs]) 
{
    for(int i=0; i<nInputs; i++)
    {
        for(int j=0; j<nInputs; j++)
        {
            printf("%f ", matrix[i][j]);
            if(j == nInputs-1)
                printf("\n");
        }
    }
}

int xor(int inputs[1][nInputs])
{
    int x = inputs[1][0];
    int y = inputs[1][1];
    if(x == y) 
        return 0;
    return 1;
}

double feedForward(int inputs[1][nInputs], double weights[][nInputs], double bias[][nInputs])
{
    double hidden[nInputs][nInputs];
    
    for(int i=0; i<nInputs; i++)
    {
        for(int j=0; j<nInputs; j++)
        {
            
            hidden[i][j] = sigmoid(weights[i][j] * inputs[i][0] + bias[i][j]);
        }
    }

    double output;
    for(int i=0; i<nInputs; i++)
    {
        for(int j=0; j<nInputs; j++)
        {
            output += sigmoid(weights[i][j] * hidden[i][j] +  bias[i][j]);
        }
    }
    return output-2;
}

void backPropagation(int *inputs, double weights[][nInputs], double bias[][nInputs], int target)
{
    
}

int main()
{
    int inputs[1][nInputs];
    double weights[nInputs][nInputs];
    double bias[nInputs][nInputs];
    double result;

    init_weights(weights);
    print_matrix(weights);


    result = feedForward(inputs, weights, bias);
    printf("Feed forward : %lf\n", result);
    printf("Expected value : %d\n", xor(inputs));

    return 0;
}


#include <stdio.h>
#include <math.h>
#include "softmax.h"

void train()
{
    printf("Softmax: %d\n", softmax(2));
    for(int i=0; i < epochs; i++)
    {
        //Compute the hidden layer activation
        for(int j=0; j<nHiddenNodes; j++)
        {
            double activation = hiddenLayerBias[j];
            for(int k=0; k<nInputs; k++)
                activation += training_data[i][k]*hiddenWeights[k][j];
            hiddenLayer[j] = softmax(activation);
        }

        //Compute the output layer activation
        for(int j=0; j<nOutputs; j++)
        {
            double activation = outputLayerBias[j];
            for(int k=0; k<nHiddenNodes; k++)
                activation += hiddenLayer[k]*outputWeights[k][j];
            outputLayer[j] = softmax(activation);
        }

        //Compute change in output weights
        double dOutput[nOutputs];
        for(int j=0; j<nOutputs; j++)
        {
            double dError = (training_outputs[i][j]-outputLayer[j]);
            dOutput[j] = dError*dSoftmax(outputLayer[j]);
        }

        //Compute change in hidden weights
        double dHidden[nHiddenNodes];
        for(int j=0; j <numHiddenNodes; j++)
        {
            double dError = 0.0f;
            for(int k=0; k<nOutputs; k++)
                dError += dOutputs[k]*outputWeights[j][k];
            dHidden[j] = dError*dSorftmax(hiddenLayer[j]);
        }

        //Apply changes in output weights
        for (int j=0; j<nOutputs; j++) {
            outputLayerBias[j] += deltaOutput[j]*lr;
            for (int k=0; k<nHiddenNodes; k++) {
              outputWeights[k][j]+=hiddenLayer[k]*dOutput[j]*lr;
            }
        }
        // Apply change in hidden weights
        for (int j=0; j<nHiddenNodes; j++) {
            hiddenLayerBias[j] += dHidden[j]*lr;
            for(int k=0; k<nInputs; k++) {
                hiddenWeights[k][j]+=training_inputs[i][k]*dHidden[j]*lr;
            }
        }
    }
}

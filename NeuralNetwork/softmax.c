#include <stdlib.h>
#include <math.h>

void softmax_neuron(float* arr) {
    int size = sizeof(arr);
    double sum = 0;
    for(int i=0; i < size; i++) {
        sum += exp(arr[i]);
    }
}

double softmax(double factor) {
    return exp() / factor;
}


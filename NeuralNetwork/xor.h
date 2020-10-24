#ifndef XOR_H
#define XOR_H

struct Neurones {
    int inputs;
    int hidden;
    int output;
};

double sigmoid(double x);
double dsigmoid(double x);
int xor(struct Neurones N, double inputs[][N.inputs]);
void feedForward(struct Neurones N, double inputs[][N.inputs],
        double weights_ih[][N.inputs], double weights_oh[][N.inputs],
        double bias_i[][N.inputs], double bias_o[][N.inputs],
        double hidden[][N.inputs], double output[][N.inputs]);

void backPropagation(struct Neurones N, double inputs[][N.inputs], 
        double weights_oh[][N.inputs], double weights_ih[][N.inputs],
        double bias_i[][N.inputs], double bias_o[][N.inputs], 
        double hidden[][N.inputs], double output[][N.inputs],int epochs);

void train(struct Neurones N, double inputs[N.inputs][1], double output[N.output][2]);

#endif

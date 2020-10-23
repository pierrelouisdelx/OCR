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


#endif

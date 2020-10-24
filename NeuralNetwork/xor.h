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

void feedForward(struct Neurones N, double inputs[N.inputs][1],
        double weights_ih[N.hidden][N.inputs], double weights_oh[N.output][N.inputs],
        double bias_i[N.hidden][1], double bias_o[N.output][1],
        double hidden[N.hidden][1], double output[N.output][1]);

void backPropagation(struct Neurones N, double inputs[N.inputs][1],
        double weights_oh[N.output][N.hidden], double weights_ih[N.hidden][N.inputs],
        double bias_i[N.hidden][1], double bias_o[N.output][1],
        double hidden[N.hidden][1], double output[N.output][1], int epochs);

void train(struct Neurones N, double inputs[N.inputs][1], double output[N.output][1]);

#endif

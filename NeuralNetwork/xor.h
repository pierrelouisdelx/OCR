#ifndef XOR_H
#define XOR_H

struct Neurones {
    int inputs;
    int hidden;
    int output;
};

double sigmoid(double x);
double dsigmoid(double x);
double xor(struct Neurones N, double inputs[][N.inputs]);

void feedForward(struct Neurones N, double inputs[N.inputs][1],
        double weights_ih[N.hidden][N.inputs], double weights_oh[N.output][N.inputs],
        double bias_i[N.hidden][1], double bias_o[N.output][1],
        double hidden[N.hidden][1], double output[N.output][1]);

void backPropagation(struct Neurones N, double inputs[N.inputs][1], 
        double weights_oh[N.output][N.hidden], double weights_ih[N.hidden][N.inputs],
        double bias_i[N.hidden][1], double bias_o[N.output][1], 
        double hidden[N.hidden][1], double output[N.output][1],
    	double error_output[N.output][1], double error_hidden[N.hidden][1],
        double gradient_output[N.output][1], double d_weight_oh[N.inputs][N.inputs], 
        double d_bias_o[N.inputs][N.inputs], double gradient_hidden[N.hidden][1], 
        double d_weight_ih[N.inputs][N.inputs], double d_bias_h[N.inputs][N.inputs], 
        double target[N.output][1], double transpose_hidden[N.hidden][N.output], 
        double transpose_input[1][N.inputs], float lr);

void train(struct Neurones N, double output[N.output][1], 
        double weights_ih[N.hidden][N.inputs], double weights_oh[N.output][N.hidden],
        double bias_i[N.hidden][1], double bias_o[N.output][1], double hidden[N.hidden][1], int epochs);

#endif

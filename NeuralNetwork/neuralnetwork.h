#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

struct Neurones 
{
    int inputs;
    int hidden;
    int output;
};

double sigmoid(double x);
double dsigmoid(double x);
void get_folders(int *dirs);

void feedForward(struct Neurones N, 
        double inputs[N.inputs * 1], 
        double weights_ih[N.hidden * N.inputs], 
        double weights_oh[N.output * N.hidden],
        double bias_i[N.hidden * 1], 
        double bias_o[N.output * 1], 
        double hidden[N.hidden * 1], 
        double output[N.output * 1]);

void backPropagation(struct Neurones N, 
        double inputs[N.inputs * 1], 
        double weights_oh[N.output * N.hidden], 
        double weights_ih[N.hidden * N.inputs],
        double bias_i[N.hidden * 1], 
        double bias_o[N.output * 1],
        double output[N.output * 1],
        double target[N.output * 1]);

void set_target(struct Neurones N,double target[], char dir);

void train(struct Neurones N, 
        double output[N.output * 1], 
        double weights_ih[N.hidden * N.inputs], 
        double weights_oh[N.output * N.hidden],
        double bias_i[N.hidden * 1], 
        double bias_o[N.output * 1], 
        int epochs);

int getoutput(struct Neurones N, double output[N.output]);
void save_output(char c[]);

void test(struct Neurones N,
        double output[N.output * 1], 
        double weights_ih[N.hidden * N.inputs], 
        double weights_oh[N.output * N.hidden],
        double bias_i[N.hidden * 1], 
        double bias_o[N.output * 1]);

int SaveData(struct Neurones N,
    double weights_ih [N.hidden * N.inputs],
    double weights_ho [N.output * N.hidden],
    double bias_h [N.hidden * 1],
    double bias_o [N.output * 1]);

int LoadData(struct Neurones N,
    double weights_ih [N.hidden * N.inputs],
    double weights_ho [N.output * N.hidden],
    double bias_h [N.hidden * 1],
    double bias_o [N.output * 1]);

#endif

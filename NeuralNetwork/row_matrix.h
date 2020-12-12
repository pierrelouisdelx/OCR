#ifndef MATRIX_H
#define MATRIX_H
#include "neuralnetwork.h"

double Random();
void print_matrix(int rows, int cols, double m[]);
void init(int rows, int cols, double m[]);
void add(int rows, int cols, double m1[], double m2[], double r[]);
void sub(int rows, int cols, double m1[], double m2[], double r[]);
void multeach(int rows, int cols, double m1[], double m2[], double r[]);
void mult(int r1, int c1, int r2, int c2, double m1[], double m2[], double r[]);
void transpose(int rows, int cols, double m[], double r[]);
void factor(int rows, int cols, double m[], double factor, double r[]);
void function(int rows, int cols, double (*f)(double), double m[]);

void shuffle(int rows, int cols, char m[]);

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

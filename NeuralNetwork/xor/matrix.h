#ifndef MATRIX_H
#define MATRIX_H

#include "o_xor.h"

double Random();
void print_matrix(int h, int w, double mat[h][w]);
void init_matrix(int h, int w, double matrix[h][w]);
void zero_matrix(int h, int w, double matrix[h][w]);
void add_matrix(int h, int w, double mat1[h][w], double mat2[h][w], double res[h][w]);
void sub_matrix(int h, int w, double mat1[h][w], double mat2[h][w], double res[h][w]);
void multeach_matrix(int h, int w, double mat1[h][w], double mat2[h][w], double res[h][w]);
void mult_matrix(int h1, int w1, int h2, int w2, double mat1[h1][w1], double mat2[h2][w2], double res[h1][w1]);
void transpose_matrix(int h, int w, double mat[h][w], double res[h][w]);
void factor_matrix(int h, int w, double mat[h][w], double factor, double res[h][w]);
void function_matrix(int h, int w, double (*f)(double), double m[h][w]);

void shuffle(size_t h, size_t w, double array[h][w]);

int SaveData(struct Neurones N,
    double weights_ih [N.hidden][N.inputs],
    double weights_ho [N.output][N.hidden],
    double bias_h [N.hidden][1],
    double bias_o [N.output][1]);

int LoadData(struct Neurones N,
    double weights_ih [N.hidden][N.inputs],
    double weights_ho [N.output][N.hidden],
    double bias_h [N.hidden][1],
    double bias_o [N.output][1]);

#endif

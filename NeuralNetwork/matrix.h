#ifndef MATRIX_H
#define MATRIX_H
#include "xor.h"

struct Matrix
{
    //the obvious : the size
    int rows; //w
    int cols; //h

    //the obvious yet again, a pointer to the matrix in itself
    double *mat;
};

double Random();
void print_matrix(struct Matrix matrix);
void init_matrix(struct Matrix matrix);
void add_matrix(struct Matrix matrix1, struct Matrix matrix2);
void sub_matrix(struct Matrix matrix1, struct Matrix matrix2);
void multeach_matrix(struct Matrix matrix1, struct Matrix matrix2);
void mult_matrix(struct Matrix matrix1, struct Matrix matrix2);
void transpose_matrix(struct Matrix matrix1, struct Matrix matrix2);
void factor_matrix(struct Matrix matrix, double factor);
void function_matrix(struct Matrix matrix, double (*f)(double));
void copy_matrix(struct Matrix matrix);

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

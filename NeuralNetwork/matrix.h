#ifndef MATRIX_H
#define MATRIX_H
#include "xor.h"

double Random();
void print_matrix(struct Neurones N, double mat[][4]);
double init_matrix(double matrix[][4]);
void add_matrix(struct Neurones N, double mat1[][N.inputs], double mat2[][N.inputs], double res[][N.inputs]);
void mult_matrix(double mat1[][4], double mat2[][4], double res[][4], int l1, int c1, int l2, int c2);
void transpose_matrix(struct Neurones N, double mat[][4], double res[][4]);
void factor_matrix(struct Neurones N, double mat[][2], double factor, double res[][2]);
void function_matrix(double (*f)(double), double m[][4]);
void copy_matrix(struct Neurones N, double mat1[][N.inputs], double mat2[][N.inputs]);

#endif

#ifndef MATRIX_H
#define MATRIX_H
#include "xor.h"

double Random();
void print_matrix(double mat[][4], int l, int c);
double init_matrix(double matrix[][4]);
void add_matrix(struct Neurones N, double mat1[][N.inputs], double mat2[][N.inputs], double res[][N.inputs]);
void mult_matrix(double mat1[][4], double mat2[][4], double res[][4], int l1, int c1, int l2, int c2);
void transpose_matrix(double mat[][4], double res[][4], int l, int c);
void function_matrix(double (*f)(double), double m[][4]);

#endif

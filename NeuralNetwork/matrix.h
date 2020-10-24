#ifndef MATRIX_H
#define MATRIX_H
#include "xor.h"

double Random();
void init_matrix(int w, int h, double matrix[w][h]);
void add_matrix(int w, int h, double mat1[w][h], double mat2[w][h], double res[w][h]);
void sub_matrix(int w, int h, double mat1[w][h], double mat2[w][h], double res[w][h]);
void multeach_matrix(int w, int h, double mat1[w][h], double mat2[w][h], double res[w][h]);
void mult_matrix(int w1, int h1, int w2, int h2, double mat1[w1][h1], double mat2[w2][h2], double res[w1][h1]);
void transpose_matrix(int w, int h, double mat[w][h], double res[w][h]);
void factor_matrix(int w, int h, double mat[w][h], double factor, double res[w][h]);
void function_matrix(int w, int h, double (*f)(double), double m[w][h]);
void copy_matrix(int w, int h, double mat1[w][h], double mat2[w][h]);

void swap(int w, int h, double m[w][h], int i, int j);
void shuffle_matrix(int w, int h, double m[w][h], int n);

#endif

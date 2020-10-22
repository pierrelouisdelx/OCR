#ifndef MATRIX_H
#define MATRIX_H

void print_matrix(double mat[][4], int l, int c);
void add_matrix(double mat1[][], double mat2[][], double res[][], int l, int c);
void mult_matrix(double mat1[][4], double mat2[][4], double res[][4], int l1, int c1, int l2, int c2);
void transpose_matrix(double mat[][], double res[][], int l, int c);

#endif

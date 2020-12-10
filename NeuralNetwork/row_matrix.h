#ifndef MATRIX_H
#define MATRIX_H

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

#endif

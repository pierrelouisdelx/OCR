#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "softmax.h"
#include "matrix.h"
#define N 4

int main()
{
    double res[N][N];
    double mat1[N][N] = { { 1, 1, 1, 1 },
                       { 2, 2, 2, 2 },
                       { 3, 3, 3, 3 },
                       { 4, 4, 4, 4 } };
 
    double mat2[N][N] = { { 1, 1, 1, 1 },
                       { 2, 2, 2, 2 },
                       { 3, 3, 3, 3 },
                       { 4, 4, 4, 4 } };
 
    mult_matrix(mat1, mat2, res);
    print_matrix(mat1);
    return 0;
}

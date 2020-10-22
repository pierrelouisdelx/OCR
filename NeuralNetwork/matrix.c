#include <stdio.h>
#define N 4

void print_matrix(double mat[][N])
{
    int l = sizeof(mat)/sizeof(mat[0]);
    int c = sizeof(mat[0])/sizeof(mat[0][0]);
    for(int i=0; i < 4; i++)
    {
        for(int j=0; j < 4; j++)
            printf("%d\n",mat[i][j]);
            if(j == 3)
                printf("\n");
    }
}

void add_matrix(double mat1[][N], double mat2[][N], double res[][N])
{
    int l1 = sizeof(mat1)/sizeof(mat1[0]);
    int c1 = sizeof(mat1[0])/sizeof(mat1[0][0]);

    int l2 = sizeof(mat2)/sizeof(mat2[0]);
    int c2 = sizeof(mat2[0])/sizeof(mat2[0][0]);

    for(int i=0; i<l1; i++)
    {
        for(int j=0; j<c2; j++)
        {
            res[i][j] += mat1[i][j] + mat2[i][j];
        }
    }
}

void mult_matrix(double mat1[][N], double mat2[][N], double res[][N])
{
    int l1 = sizeof(mat1)/sizeof(mat1[0]);
    int c1 = sizeof(mat1[0])/sizeof(mat1[0][0]);

    int l2 = sizeof(mat2)/sizeof(mat2[0]);
    int c2 = sizeof(mat2[0])/sizeof(mat2[0][0]);

    if(c1 == l2)
    {
        for(int i=0; i<l1; i++)
        {
            for(int j=0; j<c2; j++)
            {
                for(int k=0; k<l2; k++)
                {
                    res[i][j] += mat1[i][k] * mat2[k][j];
                }
            }
        }
    }
}

void transpose_matrix(double mat[][N], double res[][N])
{
    int l = sizeof(mat)/sizeof(mat[0]);
    int c = sizeof(mat[0])/sizeof(mat[0][0]);

    for(int i=0; i<l; i++)
    {
        for(int j=0; j<c; j++)
        {
            res[j][i] += mat[i][j];
        }
    }
}


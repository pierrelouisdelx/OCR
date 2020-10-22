#include <stdio.h>
#define N 4

void print_matrix(double mat[][N], int l , int c)
{
    for(int i=0; i < l; i++)
    {
        for(int j=0; j < c; j++)
        {
            printf("%f ",mat[i][j]);
            if(j == c-1)
                printf("\n");
        }

    }
}

void add_matrix(double mat1[][N], double mat2[][N], double res[][N], int l1, int c1, int l2, int c2)
{
    for(int i=0; i<l1; i++)
    {
        for(int j=0; j<c2; j++)
        {
            res[i][j] += mat1[i][j] + mat2[i][j];
        }
    }
}

void mult_matrix(double mat1[][N], double mat2[N][2], double res[][N], int l1, int c1, int l2, int c2)
{
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

void transpose_matrix(double mat[][N], double res[][N], int l, int c)
{
    for(int i=0; i<l; i++)
    {
        for(int j=0; j<c; j++)
        {
            res[j][i] += mat[i][j];
        }
    }
}

void factor_matrix(double mat[][N], double factor, double res[][N], int l, int c)
{
    for(int i=0; i<l; i++)
    {
        for(int j=0; j<c; j++)
        {
            res[i][j] = factor*mat[i][j];
        }
    }
}

int main()
{
    double res[2][N] = {0};
    double m1[2][4] = {
        {10, 11, 12, 13},
        {14, 15, 16, 17}
    };

    double m2[4][2] = {
        {10,11},
        {12,13},
        {14,15},
        {16,17}
    };


    transpose_matrix(m1,res,2,4);
    print_matrix(res, 2, 4);


    return 0;
}

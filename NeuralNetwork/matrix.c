#include <stdio.h>
#include <stdlib.h>
#include "xor.h"

#define nInputs 2

double Random()
{
    return (double)rand()/(double)RAND_MAX;
}

void print_matrix(struct Neurones N, double mat[][2])
{
    for(int i=0; i < N.inputs; i++)
    {
        for(int j=0; j < N.inputs; j++)
        {
            printf("%f ",mat[i][j]);
            if(j == N.inputs-1)
                printf("\n");
        }
    }
    printf("\n");
}

double init_matrix(double matrix[][nInputs])
{
    for(int i=0; i<nInputs; i++)
    {
        for(int j=0; j<nInputs; j++)
        {
            matrix[i][j] = Random();
        }
    }
}

void add_matrix(struct Neurones N, double mat1[][N.inputs], double mat2[][N.inputs], double res[][N.inputs])
{
    for(int i=0; i<N.inputs; i++)
    {
        for(int j=0; j<N.inputs; j++)
        {
            res[i][j] += mat1[i][j] + mat2[i][j];
        }
    }
}

void mult_matrix(double mat1[][2], double mat2[][2], double res[][2], int l1, int c1, int l2, int c2)
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

void transpose_matrix(struct Neurones N, double mat[][2], double res[][2])
{
    for(int i=0; i<N.inputs; i++)
    {
        for(int j=0; j<N.inputs; j++)
        {
            res[j][i] += mat[i][j];
        }
    }
}

void factor_matrix(struct Neurones N, double mat[][2], double factor, double res[][2])
{
    for(int i=0; i<N.inputs; i++)
    {
        for(int j=0; j<N.inputs; j++)
        {
            res[i][j] = factor*mat[i][j];
        }
    }
}

void function_matrix(double (*f)(double), double m[][2])
{
    for(int i=0; i<nInputs; i++)
    {
        for(int j=0; j<nInputs; j++)
        {
            m[i][j] = (*f)(m[i][j]);
        }
    }
}

void copy_matrix(struct Neurones N, double mat1[][N.inputs], double mat2[][N.inputs])
{
    for(int i=0; i<N.inputs; i++)
    {
        for(int j=0; j<N.inputs; j++)
            mat2[i][j] = mat1[i][j];
    }
}

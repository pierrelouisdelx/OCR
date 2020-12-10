#include <stdio.h>
#include <stdlib.h>
#include "xor.h"

double Random()
{
    return (double)rand()/(double)RAND_MAX;
}

void print_matrix(int rows, int cols, double m[])
{
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            printf("%4g", m[i*cols+j]);
        }
        printf("\n");
    }
}

void init(int rows, int cols, double m[])
{
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
           m[i*cols+j] = Random(); 
        }
    }
}

void add(int rows, int cols, double m1[], double m2[], double r[])
{
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
           r[i*cols+j] = m1[i*cols+j] + m2[i*cols+j]; 
        }
    }
}

void sub(int rows, int cols, double m1[], double m2[], double r[])
{
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
           r[i*cols+j] = m1[i*cols+j] - m2[i*cols+j]; 
        }
    }
}

void multeach(int rows, int cols, double m1[], double m2[], double r[])
{
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
           r[i*cols+j] = m1[i*cols+j] * m2[i*cols+j]; 
        }
    }
}

void mult(int r1, int c1, int r2, int c2, double m1[], double m2[], double r[])
{
    if(c1 == r2)
    {
        for(int i=0; i<r1; i++)
        {
            for(int j=0; j<c2; j++)
            {
                r[i*c2+j] = 0;
                for(int k=0; k<c1; k++)
                    r[i*c2+j] += m1[i*c1+k] * m2[k*c2+j];
            }
        }
    }
    else
        printf("error");
}

void transpose(int rows, int cols, double m[], double r[])
{
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
           r[j*rows+i] = m[i*cols+j]; 
        }
    }
}

void factor(int rows, int cols, double m[], double factor, double r[])
{
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
           r[i*cols+j] = factor * m[i*cols+j]; 
        }
    }
}

void function(int rows, int cols, double (*f)(double), double m[])
{
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
           m[i*cols+j] = (*f)(m[i*cols+j]); 
        }
    }
}

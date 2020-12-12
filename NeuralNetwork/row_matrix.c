#include <stdio.h>
#include <stdlib.h>
#include "neuralnetwork.h"
#include <time.h>

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
            printf("%f", m[i*cols+j]);
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

void shuffle(int rows, int cols, char m[])
{
    if (rows > 1) 
    {
        int i;
        for (i = 0; i < rows - 1; i++) 
        {
          int j = i + rand() / (RAND_MAX / (rows - i) + 1);
          int t1 = m[j * cols];
          int t2 = m[j * cols + 1];
          m[j * cols] = m[i * cols];
          m[j * cols + 1] = m[i * cols + 1];
          m[i * cols] = t1;
          m[i * cols + 1] = t2;
        }
    }
}

int SaveData(struct Neurones N,
    double weights_ih [N.hidden * N.inputs],
    double weights_ho [N.output * N.hidden],
    double bias_h [N.hidden * 1],
    double bias_o [N.output * 1])
{
    FILE *fp;
    fp = fopen ("data.txt","w");

    for (int i = 0; i < N.hidden; ++i)
    {
        for (int j = 0; j < N.inputs; ++j)
        {
            fprintf(fp, "%f\n", weights_ih[i*N.inputs + j]);
        }
    }

    for (int i = 0; i < N.output; ++i)
    {
        for (int j = 0; j < N.hidden; ++j)
        {
            fprintf(fp, "%f\n", weights_ho[i * N.hidden + j]);
        }
    }

    for (int i = 0; i < N.hidden; ++i)
    {
        fprintf(fp, "%f\n", bias_h[i * N.hidden]);
    }

    for (int i = 0; i < N.output; ++i)
    {
        fprintf(fp, "%f\n", bias_o[i * N.hidden]);
    }


    fclose(fp);
    return 0;
}

int LoadData(struct Neurones N,
    double weights_ih [N.hidden * N.inputs],
    double weights_ho [N.output * N.hidden],
    double bias_h [N.hidden * 1],
    double bias_o [N.output * 1])
{
    FILE * fp;
    fp = fopen ("data.txt","r");

    char str[1000];

    for (int i = 0; i < N.hidden; ++i)
    {
        for (int j = 0; j < N.inputs; ++j)
        {
            fgets(str, 1000, fp);
            weights_ih[i * N.inputs + j] = (double) atof(str);
        }
    }

    for (int i = 0; i < N.output; ++i)
    {
        for (int j = 0; j < N.hidden; ++j)
        {
            fgets(str, 1000, fp);
            weights_ho[i * N.hidden + j] = (double) atof(str);
        }
    }

    for (int i = 0; i < N.hidden; ++i)
    {
        fgets(str, 1000, fp);
        bias_h[i * N.hidden] = (double) atof(str);
    }

    for (int i = 0; i < N.output; ++i)
    {
        fgets(str, 1000, fp);
        bias_o[i * N.output] = (double) atof(str);
    }

    fclose(fp);
    return 0;
}


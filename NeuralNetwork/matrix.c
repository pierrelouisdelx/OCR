#include <stdio.h>
#include <stdlib.h>
#include "xor.h"

double Random()
{
    return (double)rand()/(double)RAND_MAX;
}

void print_matrix(int w, int h, double mat[w][h])
{
    for(int i=0; i < w; i++)
    {
        for(int j=0; j < h; j++)
        {
            printf("%f ",mat[i][j]);
            if(j == h-1)
                printf("\n");
        }
    }
    printf("\n");
}

void init_matrix(int w, int h, double matrix[w][h])
{
    for(int i=0; i<w; i++)
    {
        for(int j=0; j<h; j++)
        {
            matrix[i][j] = Random();
        }
    }
}

void add_matrix(int w, int h, double mat1[w][h], double mat2[w][h], double res[w][h])
{
    for(int i=0; i<w; i++)
    {
        for(int j=0; j<h; j++)
        {
            res[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

void sub_matrix(int w, int h, double mat1[w][h], double mat2[w][h], double res[w][h])
{
    for(int i=0; i<w; i++)
    {
        for(int j=0; j<h; j++)
        {
            res[i][j] = mat1[i][j] - mat2[i][j];
        }
    }
}

void multeach_matrix(int w, int h, double mat1[w][h], double mat2[w][h], double res[w][h])
{
    for(int i=0; i<w; i++)
    {
        for(int j=0; j<h; j++)
        {
            res[i][j] = mat1[i][j] * mat2[i][j];
        }
    }
}

void mult_matrix(int w1, int h1, int w2, int h2, double mat1[w1][h1], double mat2[w2][h2], double res[w1][h1])
{
    if(h1 == w2)
    {
        for(int i=0; i<w1; i++)
        {
            for(int j=0; j<h2; j++)
            {
                for(int k=0; k<w2; k++)
                {
                    res[i][j] = mat1[i][k] * mat2[k][j];
                }
            }
        }
    }
}

void transpose_matrix(int w, int h, double mat[w][h], double res[w][h])
{
    for(int i=0; i<w; i++)
    {
        for(int j=0; j<h; j++)
        {
            res[j][i] = mat[i][j];
        }
    }
}

void factor_matrix(int w, int h, double mat[w][h], double factor, double res[w][h])
{
    for(int i=0; i<w; i++)
    {
        for(int j=0; j<h; j++)
        {
            res[i][j] = factor*mat[i][j];
        }
    }
}

void function_matrix(int w, int h, double (*f)(double), double m[w][h])
{
    for(int i=0; i<w; i++)
    {
        for(int j=0; j<h; j++)
        {
            m[i][j] = (*f)(m[i][j]);
        }
    }
}

void copy_matrix(int w, int h, double mat1[w][h], double mat2[w][h])
{
    for(int i=0; i<w; i++)
    {
        for(int j=0; j<h; j++)
            mat2[i][j] = mat1[i][j];
    }
}

/*
void SaveData(double matrix,long path) //path must be absolute
{
  FILE* file = fopen(path, "w"); //w allows us to write in the file
  if(file == NULL)
  {
    printf("matrix.c : SaveData, no such file exists");
    exit(1);
  }
  fprintf(file, "%f\n", line)
  fprintf(file, "%f\n", column) 
  for(int i = 0; i < 2; ++i) //writes each bits of data in the file
  {
    for(int h = 0; h < 2; ++h)
    {
      fprintf(file, "%f\n", matrix[i][h]);
    }
  }
  fclose(file);
  //in the for loop the 2 represents the number of input and hidden layers
}
//the first two lines are the dimension of the matrix, the following lines are just
//the values stored inside of it

double LoadData(long path)
{
  FILE* file = fopen(path, 'r');
  int SizeLineMax = 15;//this should be changed later on
  char  *line = calloc(15, sizeof(char)); //this should be changed later as the needs changes
  double matrix[2][2];

  if(file == NULL)
  {
    printf("matrix.c : LoadData, no such file exists");
    exit(1);
  }
  for(int i = 0; i < 2; ++i)
  {
    for(int h = 0; i < 2; ++h)
    {
      fgets(line, SizeLineMax, file);
      strok(line, "\n");
      matrix[i][h] = atof(line);
    }
  }

  fclose(file);
  return matrix;
}*/

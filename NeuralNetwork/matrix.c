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

void shuffle(size_t h, size_t w, double array[h][w])
{
    if (h > 1)
    {
        size_t i;
        for (i = 0; i < h - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (h - i) + 1);
          double tmp1 = array[j][0];
          double tmp2 = array[j][1];
          array[j][0] = array[i][0];
          array[j][1] = array[i][1];
          array[i][0] = tmp1;
          array[i][1] = tmp2;
        }
    }
}

void save_matrix(int w, int h, double mat[w][h], const char *path) 
{
    FILE *f;
    if(f=fopen(path,"wb"))
    {
        for(int i=0; i<w; i++)
        {
            for(int j=0; j<h; j++)
            {
                fprintf(f, "%f", mat[i][j]);
            }
            fprintf(f, "\n");
        }
    }
    fclose(f);
}

void LoadData(const char * path, int line, int column, double mat[line][column])
{
  FILE* file = fopen(path, "r");

  char save[line + column];
  if(file == NULL)
  {
    printf("matrix.c : LoadData, no such file exists");
    exit(1);
  }
    int c=0; //index of letter in save
    fgets(save, sizeof(save), file);
    for (int i = 0; i < line ; i++)
    {
      for(int n=0; n < column; n++)
      {
        mat[i][n] = save[c];
      }
    }

  fclose(file);
}


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

void transpose_matrix(int w, int h, double mat[w][h], double res[h][w])
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

int SaveData(struct Neurones N,
    double weights_ih [N.hidden][N.inputs],
    double weights_ho [N.output][N.hidden],
    double bias_h [N.hidden][1],
    double bias_o [N.output][1])
{
    FILE * fp;
    fp = fopen ("data.txt","w");

    for (int i = 0; i < N.hidden; ++i)
    {
        for (int j = 0; j < N.inputs; ++j)
        {
            fprintf(fp, "%f\n", weights_ih[i][j] );
        }
    }

    for (int i = 0; i < N.output; ++i)
    {
        for (int j = 0; j < N.hidden; ++j)
        {
            fprintf(fp, "%f\n", weights_ho[i][j] );
        }
    }

    for (int i = 0; i < N.hidden; ++i)
    {
        fprintf(fp, "%f\n", bias_h[i][0] );
    }

    for (int i = 0; i < N.output; ++i)
    {
        fprintf(fp, "%f\n", bias_o[i][0] );
    }
   

    fclose(fp);
    return 0;
}

int LoadData(struct Neurones N,
    double weights_ih [N.hidden][N.inputs],
    double weights_ho [N.output][N.hidden],
    double bias_h [N.hidden][1],
    double bias_o [N.output][1])
{
    FILE * fp;
    fp = fopen ("data.txt","r");

    char str[1000];


    for (int i = 0; i < N.hidden; ++i)
    {
        for (int j = 0; j < N.inputs; ++j)
        {
            fgets(str, 1000, fp);
            weights_ih[i][j] = (double) atof(str);
        }
    }

    for (int i = 0; i < N.output; ++i)
    {
        for (int j = 0; j < N.hidden; ++j)
        {
            fgets(str, 1000, fp);
            weights_ho[i][j] = (double) atof(str);
        }
    }

    for (int i = 0; i < N.hidden; ++i)
    {
        fgets(str, 1000, fp);
        bias_h[i][0] = (double) atof(str);
    }

    for (int i = 0; i < N.output; ++i)
    {
        fgets(str, 1000, fp);
        bias_o[i][0] = (double) atof(str);
    }
   

    fclose(fp);
    return 0;
}

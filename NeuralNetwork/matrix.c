#include <stdio.h>
#include <stdlib.h>
#include "xor.h"
#include "matrix.h"

double Random()
{
    return (double)rand()/((double)RAND_MAX/2) - 1;
}

//return 0 if the coords are impossible, 1 otherwise
int safeCoord_matrix(struct Matrix matrix, int i, int j)
{
    return(i < matrix.rows && j < matrix.cols);
}

void print_matrix(struct Matrix matrix)
{
    for(int i = 0; i < matrix.rows; i++)
    {
        for(int j = 0; j < matrix.cols; j++)
        {
            printf(" %f |", *(matrix.mat + i * matrix.cols + j));
        }
        printf("\n");
    }
}

//create an empty matrix
struct Matrix create_matrix(int rows, int cols)
{
    struct Matrix matrix;

    matrix.rows = rows;
    matrix.cols = cols;

    matrix.mat = malloc(sizeof(double)*cols*rows);

    return matrix;
}

void putValue_matrix(struct Matrix matrix, int rows, int cols, double value)
{
    if(safeCoord_matrix(matrix, rows, cols))
    {
        *(matrix.mat + rows * matrix.cols + cols) = value;
    }
    else
    {
        printf("error in coordinates \n");
    }
}


//fills the matrix with random values
void init_matrix(struct Matrix matrix)
{
    for(int i = 0; i < matrix.rows;i++)
    {
        for(int j=0; j< matrix.cols; j++)
        {
            putValue_matrix(matrix, i, j, Random())
        }
    }
}

//Adds two matrixes, creates the resulting matrix, exit with code error 0 if the matrixes aren't of same dimension
struct Matrix add_matrix(struct Matrix mat1, struct Matrix mat2)
{
    if(mat1.cols!=mat2.cols || mat1.cols!=mat2.cols)
    {
        printf("matrix.c : add_matrix : the two matrixes must be of same dimension");
        exit(0);
    }
    struct Matrix matRES = create_matrix(mat1.cols, mat1.rows);
    for(int i=0; i<mat1.rows; i++)
    {
       for(int j=0; j<mat1.cols; j++)
        {
            double value = *(mat1.mat + i * mat1.cols + j) + *(mat2.mat + i * mat2.cols + j);
            putValue_matrix(matRES, i, j, value);
        }
    }
    return matRES;
}

struct Matrix sub_matrix(struct Matrix mat1, struct Matrix mat2)
{
    if(mat1.cols!=mat2.cols || mat1.cols!=mat2.cols)
    {
        printf("matrix.c : sub_matrix : the two matrixes must be of same dimension");
        exit(0);
    }
    struct Matrix matRES = create_matrix(mat1.cols, mat1.rows);
    for(int i=0; i<mat1.rows; i++)
    {
       for(int j=0; j<mat1.cols; j++)
        {
            double value = *(mat1.mat + i * mat1.cols + j) - *(mat2.mat + i * mat2.cols + j);
            putValue_matrix(matRES, i, j, value);
        }
    }
    return matRES; 
}

//multiply mat1[x][y] with mat2[x][y]
struct Matrix multeach_matrix(struct Matrix mat1, struct Matrix mat2)
{
    if(mat1.cols!=mat2.cols || mat1.cols!=mat2.cols)
    {
        printf("matrix.c : multeach_matrix : the two matrixes must be of same dimension");
        exit(0);
    }
    struct Matrix matRES = create_matrix(mat1.cols, mat1.rows);
    for(int i=0; i<mat1.rows; i++)
    {
       for(int j=0; j<mat1.cols; j++)
        {
            double value = *(mat1.mat + i * mat1.cols + j) * *(mat2.mat + i * mat2.cols + j);
            putValue_matrix(matRES, i, j, value);
        }
    }
    return matRES;
}

//classic matrix multiplication mat1*mat2
struct Matrix mult_matrix(struct Matrix mat1, struct Matrix mat2)
{
    if(mat1.rows!=mat2.cols)
    {
        printf("matrix.c : mult_matrix : the two matrixes must be compatible");
        exit(0);
    }
    struct Matrix matRES = create_matrix(mat1.rows, mat2.cols);
    for(int a=0; a < matRES.rows; a++)
    {
        for(int b=0; b < matRES.cols; b++)
        {
            putValue_matrix(matRES, a, b, 0);
        }
    }
    for(int i=0; i<mat1.rows; i++)
    {
       for(int j=0; j<mat2.cols; j++)
        {
            for(int k=0; k<mat2.rows;k++)
            {
                printf("%f, %f \n", *(mat1.mat + i * mat1.cols + k), *(mat2.mat + k * mat2.cols + j));
                double value = *(mat1.mat + i * mat1.cols + k) * *(mat2.mat + k * mat2.cols + j);
                *(matRES.mat + i * matRES.cols + j) += value;
            }
        }
    }
    return matRES;
}


struct Matrix transpose_matrix(struct Matrix mat)
{
    struct Matrix matRES = create_matrix(mat.cols, mat.rows);
    for(int i=0; i<mat.rows; i++)
    {
        for(int j=0; j<mat.cols; j++)
        {
             putValue_matrix(matRES, j, i, *(mat.mat + i * mat.cols + j));
        }
    }
    return matRES;
}

struct Matrix factor_matrix(struct Matrix matrix, double factor)
{
    struct Matrix matRES = create_matrix(matrix.rows, matrix.cols);
    for(int i=0; i<matrix.rows; i++)
    {
        for(int j=0; j<matrix.cols; j++)
        {
            putValue_matrix(matRES, i, j, factor*(matrix + i * matrix.cols + j);
        }
    }
    return matRES;
}

struct Matrix function_matrix(struct Matrix matrix, double (*f)(double))
{

    struct Matrix matRES = create_matrix(matrix.rows, matrix.cols);
    for(int i=0; i<matrix.rows; i++)
    {
        for(int j=0; j<matrix.cols; j++)
        {
            putValue_matrix(matRES, i, j, (*f)*(matrix + i * matrix.cols + j);
        }
    }
    return matRES;
}

struct Matrix copy_matrix(struct Matrix matrix)
{
    struct Matrix matRES = create_matrix(matrix.rows, matrix.cols);
    for(int i=0; i<matrix.rows; i++)
    {
        for(int j=0; j<matrix.cols; j++)
        {
            putValue_matrix(matRES, i, j,*(matrix + i * matrix.cols + j);
        }
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

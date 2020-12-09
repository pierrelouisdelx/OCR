#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "xor.h"
#include "matrix.h"

#define getName(var)  #var 

void red(char *s)
{
    printf("\033[1;31m%s\033[0m\n",s);
}

void green(char *s)
{
    printf("\033[1;32m%s\033[0m\n",s);
}

void yellow(char *s)
{
    printf("\033[1;33m%s\033[0m\n",s);
}

void alert(char *s)
{
    printf("\033[1;36m%s\033[0m\n",s);
}

int main()
{
    struct Neurones N;
    N.inputs = 2;
    N.hidden = 3;
    N.output = 1;

    srand(time(NULL));

    double output[N.output][1];

    double weights_oh[N.output][N.hidden];
    double weights_ih[N.hidden][N.inputs];
    double bias_i[N.hidden][1];
    double bias_o[N.output][1];
    double hidden[N.hidden][1];
    int epochs = 1;

    init_matrix(N.hidden, N.inputs, weights_ih);
    init_matrix(N.output, N.hidden, weights_oh);
    init_matrix(N.hidden, 1, bias_i);
    init_matrix(N.output, 1, bias_o);
 
    red(getName(output));
    print_matrix(N.output, 1, output);   

    red(getName(weights_ih));
    print_matrix(N.hidden, N.inputs, weights_ih);

    red(getName(weights_oh));
    print_matrix(N.output, N.hidden, weights_oh);

    red(getName(bias_i));
    print_matrix(N.hidden, 1, bias_i);
    
    red(getName(bias_o));
    print_matrix(N.output, 1, bias_o);

    red(getName(hidden));
    print_matrix(N.hidden, 1, hidden);

    printf("\033[1;32m########################TRAIN########################\033[0m\n\n");
    train(N, output, weights_ih, weights_oh, bias_i, bias_o, epochs);
    printf("\n\n\033[1;32m########################TRAIN########################\033[0m\n\n");
 
    return 0;
}


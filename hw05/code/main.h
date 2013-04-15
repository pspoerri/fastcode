#ifndef _MAIN_H_
#define _MAIN_H_

#ifndef NB
#error NB is not defined
#endif

#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

bool validate()
{
    for (uint i=0; i<NB; i++)
    {
        for (uint j=0; j<NB; j++)
        {
            C[i*NB+j] = -C[i*NB+j];
        }
    }
   
}

double* create_zero(uint s)
{
    return (double*) calloc(s*s, sizeof(double));
}

double* create_random(uint s)
{
    double *M = (double*) malloc(s*s*sizeof(double));
    for (uint i=0; i<s*s; i++)
    {
        M[s] = rand() / (double)RAND_MAX;
    }
}

double *create_banded(
#endif

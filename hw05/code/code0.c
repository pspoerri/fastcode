#ifndef N
#ifndef NB
#error NB is not defined
#endif
#else
#undef NB
#define NB N
#endif


double *A, *B, *C;

//The following code implements C = A B + C 
//with A, B and C being NB x NB matrices
//This is done by definition
void compute() {
    int i,j,k;
    for (i=0; i<NB; i++)
    {
        for (j=0; j<NB; j++)
        {
            for (k=0; k<NB; k++)
            {
                C[i*NB+j] += A[i*NB+k] * B[k*NB+j];
            }
        }
    }
}


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef NB
#error NB is not defined
#endif

double *A, *B, *C, *Cref;

void verifier() {
  int i, j, k;
  for(i = 0; i < NB; ++i) {
    for(j = 0; j < NB; ++j) {
      double out = 0;
      for(k = 0; k < NB; ++k) {
        out = out + A[i*NB+k] * B[k*NB+j];
      }
      Cref[i*NB+j] += out;
    }
  }
}

int main(){
  int i;
  int nb = NB;
  A = (double*)malloc(NB*NB*sizeof(double));
  B = (double*)malloc(NB*NB*sizeof(double));
  C = (double*)malloc(NB*NB*sizeof(double));
  Cref = (double*)malloc(NB*NB*sizeof(double));

  srand ( time(NULL) );

  for(i = 0; i<NB*NB; i++) { 
    A[i] = ((double)rand()/((double)(RAND_MAX)+(double)(1)));
    B[i] = ((double)rand()/((double)(RAND_MAX)+(double)(1)));
    C[i] = ((double)rand()/((double)(RAND_MAX)+(double)(1)));
    Cref[i] = C[i];
  }
  
  compute();
  verifier();

  for(i = 0; i<NB*NB; i++) {
    if (abs(Cref[i]-C[i])>10e-7) {
      printf("error\n");
      return -1;
    }
  }

  return 0;
}

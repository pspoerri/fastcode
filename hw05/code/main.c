#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_RUNS 1
#define CYCLES_REQUIRED 1E8
#include "rdtsc.h"

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

void initData()
{
    int i;
    for(i = 0; i<NB*NB; i++) { 
        C[i] = Cref[i];
    }
}


void microbench()
{
    int i, num_runs;
    double cycles;
    tsc_counter start, end;
    
    // limit cycles
    num_runs = NUM_RUNS;
    

    CPUID(); RDTSC(start); RDTSC(end);
    CPUID(); RDTSC(start); RDTSC(end);
    CPUID(); RDTSC(start); RDTSC(end);

    while (1) {
        initData();
        CPUID(); RDTSC(start);
        for (i=0; i<num_runs; i++)
        {
            compute();
        }
        RDTSC(end); CPUID();

            
        cycles = ((double)COUNTER_DIFF(end, start));

        if(cycles >= CYCLES_REQUIRED) break;

        num_runs *= 2;
    }
    
    //initData();
    CPUID(); RDTSC(start);    
    for (i=0; i<num_runs; i++)
    {
        compute();
    }
    RDTSC(end); CPUID();
    
    cycles = ((double)COUNTER_DIFF(end, start)) / ((double) num_runs);

    double sum = 0.0;
    for (i=0; i<NB*NB; i++)
    {
        sum += C[i];
    }
    printf("{'block_size': %d, 'cycles': %f, 'total_sum': %f, 'num_runs': %d }", NB, cycles, sum, num_runs); 
    
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
  
#ifndef VERIFY
  microbench();
#else
  compute();
  verifier();
  for(i = 0; i<NB*NB; i++) {
    if (abs(Cref[i]-C[i])>10e-7) {
      printf("error\n");
      return -1;
    }
  }
#endif
  return 0;
}

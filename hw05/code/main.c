#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_RUNS 1
#define CYCLES_REQUIRED 1E8
#include "rdtsc.h"
#include "ftimer.h"
#define CLOCK_SPEED 2600000000

#ifndef NB
#error NB is not defined
#endif

double *A, *B, *C, *Cref;

void verifier() {
  int i, j, k;
#ifndef N
  for(i = 0; i < NB; ++i) {
    for(j = 0; j < NB; ++j) {
      double out = 0;
      for(k = 0; k < NB; ++k) {
        out = out + A[i*NB+k] * B[k*NB+j];
      }
      Cref[i*NB+j] += out;
    }
  }
#else
#ifndef N
#error N not defined
#endif

  for(i = 0; i < N; ++i) {
    for(j = 0; j < N; ++j) {
      double out = 0;
      for(k = 0; k < N; ++k) {
        out = out + A[i*N+k] * B[k*N+j];
      }
      Cref[i*N+j] += out;
    }
  }
#endif
}

void initData()
{
    int i;
    for(i = 0; i<NB*NB; i++) { 
        C[i] = Cref[i];
    }
}

void timebench()
{
    int i, num_runs;
    double sum;
    double start, tmeas;
    
    num_runs = NUM_RUNS;
    // fill cache
    for (i = 0; i < num_runs; i++)
        compute();

    // make measurement
    init_etime();
    start = get_etime();
    for (i = 0; i < num_runs; i++)
        compute();
    tmeas = get_etime();
    tmeas = tmeas-start;
    
//    double time_run = tmeas/((double) num_runs);
//    double cycles = time_run*((double) CLOCK_SPEED);

    double cycles = tmeas*(((double) CLOCK_SPEED)/((double) num_runs));
    double time_run = tmeas/((double) num_runs);
    double block_size = (double) NB;
    double total_flops = 2.0*block_size*block_size*block_size;
    double flops_cycle = total_flops/cycles;
    
    for (i=0; i<NB*NB; i++)
    {
        sum += C[i];
    }
    printf("{'block_size': %d, 'time': %f, 'cycles': %f, 'total_sum': %f, 'num_runs': %d, 'flops_cycle': %f }", NB, time_run, cycles, sum, num_runs, flops_cycle); 
}

void microbench()
{
    int i, num_runs;
    double cycles;
    double sum;
    tsc_counter start, end;
    
    // limit cycles
    num_runs = NUM_RUNS;

    CPUID(); RDTSC(start); RDTSC(end);
    CPUID(); RDTSC(start); RDTSC(end);
    CPUID(); RDTSC(start); RDTSC(end);
    
    initData();
    while (1) {
        CPUID(); RDTSC(start);
        for (i=0; i<num_runs; i++)
        {
            compute();
        }
        RDTSC(end); CPUID();
        
        
//       for (i=0; i<NB*NB; i++)
//        {
//            sum += C[i];
//        }
            
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
    double block_size = (double) NB;
    double total_flops = 2.0*block_size*block_size*block_size;
    double flops_cycle = total_flops/cycles;
    //sum = 0.0;
    for (i=0; i<NB*NB; i++)
    {
        sum += C[i];
    }
    printf("{'block_size': %d, 'cycles': %f, 'total_sum': %f, 'num_runs': %d, 'flops_cycle': %f }", NB, cycles, sum, num_runs, flops_cycle); 
    
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
//    printf("{'microbench': ");
    microbench();
//    printf(", 'timebench': ");
//    timebench();
//    printf("}"); 
#else
  compute();
  verifier();

#ifndef N
  for(i = 0; i<NB*NB; i++) {
#else
  for(i = 0; i<N*N; i++) {
#endif
    if (abs(Cref[i]-C[i])>10e-7) {
      printf("error\n");
      return -1;
    }
  }
  printf("Verified\n");
#endif
  return 0;
}

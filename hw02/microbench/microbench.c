#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "rdtsc.h" // Timing macros

#define NUM_RUNS 50
#define CYCLES_REQUIRED 1E8

#include "funcs.h" // Reduction functions

/*
 * microbench: timing setup
 * x: input vector
 * y: output vector
 * n: length of the input vector
 * dest: used to avoid deadcode eliminiation
 */
double microbench( double * x, double * y, double *dest, size_t n) {
  int i, num_runs;
  double cycles;
  tsc_counter start, end;
  
  num_runs = NUM_RUNS;
  
  // Cache warm-up for at least CYCLES_REQUIRED cycles,
  // recording the required number of executions

  CPUID(); RDTSC(start); RDTSC(end);
  CPUID(); RDTSC(start); RDTSC(end);
  CPUID(); RDTSC(start); RDTSC(end);

  while(1) {


    CPUID(); RDTSC(start);

    for(i = 0; i < num_runs; i++) {
	cos_bench(x,y,n);		     
    }
    
    RDTSC(end); CPUID();

    for (i = 0; i< n; i++)
	*dest += y[i]; //this is done to avoid dead code eliminiation    

    
    cycles = ((double)COUNTER_DIFF(end, start));

    if(cycles >= CYCLES_REQUIRED) break;

    num_runs *= 2;

  }
  
  //Measurement of the selected function
  CPUID(); RDTSC(start);

  for(i = 0; i < num_runs; i++) {
	cos_bench(x,y,n);
    }

  
  
  RDTSC(end); CPUID();
 
  for (i = 0; i< n; i++)
     *dest += y[i]; //this is done to avoid dead code eliminiation

 
  cycles = ((double)COUNTER_DIFF(end, start)) / ((double) num_runs);

  return cycles;
}


int main(int argc, char **argv){
  
  long int i, j, n;
  double *x,*y, dest, r;
  
  
  
  n = 32*1024/8/2;
  x = (double*)malloc(n*sizeof(double));
  y = (double*)malloc(n*sizeof(double));
  for(j = 0; j < n; j++) x[j] = 0.0;
  for(j = 0; j < n; j++) y[j] = 0.0;
  
  // Positions with no measurements are filled with 0s.
  r = microbench(x,y,&dest, n);
  printf("dest = %f\n", dest); //this again to avoid dead code eliminiation
  
  printf("Time for Cos(1.1): ");
  printf("cycles %f\n,", r/n);
 
  free(x);
  free(y); 
  return 0;
}

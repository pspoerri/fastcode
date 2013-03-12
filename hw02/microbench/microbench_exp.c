#include "main.h"

/*
 * microbench: timing setup
 * x: input vector
 * y: output vector
 * n: length of the input vector
 * dest: used to avoid deadcode eliminiation
 */
double microbench_exp( double * x, double * y, double *dest, size_t n) {
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
	exp_bench(x,y,n);		     
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
	exp_bench(x,y,n);
  }

  
  
  RDTSC(end); CPUID();
 
  for (i = 0; i< n; i++)
     *dest += y[i]; //this is done to avoid dead code eliminiation

 
  cycles = ((double)COUNTER_DIFF(end, start)) / ((double) num_runs);

  return cycles;
}

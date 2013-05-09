#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_RUNS 1
#define CYCLES_REQUIRED 1E8
#include "rdtsc.h"
#include "ftimer.h"
#define CLOCK_SPEED 2600000000

#ifndef N
#error N not defined
#endif 

float *x, *y, alpha; 

void warmup(float *x, float *y, int size, float alpha);


void microbench()
{
    int i, num_runs, n;
    double cycles;
    double sum;
    tsc_counter start, end;
    
    n = N;
    // limit cycles
    num_runs = NUM_RUNS;

    CPUID(); RDTSC(start); RDTSC(end);
    CPUID(); RDTSC(start); RDTSC(end);
    CPUID(); RDTSC(start); RDTSC(end);
    
    while (1) {
        CPUID(); RDTSC(start);
        for (i=0; i<num_runs; i++)
        {
            warmup(x,y, n, alpha);
        }
        RDTSC(end); CPUID();
        
        cycles = ((double)COUNTER_DIFF(end, start));

        if(cycles >= CYCLES_REQUIRED) break;

        num_runs *= 2;
    }
    
    CPUID(); RDTSC(start);    
    for (i=0; i<num_runs; i++)
    {
        warmup(x,y, n, alpha);
    }
    RDTSC(end); CPUID();
    
    cycles = ((double)COUNTER_DIFF(end, start)) / ((double) num_runs);

    sum = 0.0;

    sum = y[0];
    double total_flops = n*3;
    double flops_cycle = total_flops/cycles;
    printf("{'size': %d, 'cycles': %f, 'total_sum': %f, 'num_runs': %d, 'flops_cycle': %f }", n, cycles, sum, num_runs, flops_cycle); 
}

int main(){
    int i;
    int n = N;
    alpha = 1000.0; 
    y = (float*)malloc(n*sizeof(float));
    x = (float*)malloc(2*n*sizeof(float));

    srand ( time(NULL) );

    for(i = 0; i<2*n; i++) {
        x[i] = ((float)rand()/((float)(RAND_MAX)+(float)(1)));
        if (i < n) 
        {
            y[i] = ((float)rand()/((float)(RAND_MAX)+(float)(1)));
        }
    }
  
    microbench();
    return 0;
}

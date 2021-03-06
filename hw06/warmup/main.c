#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define NUM_RUNS 1
#define CYCLES_REQUIRED 1E8
#include "rdtsc.h"
#include "ftimer.h"
#define CLOCK_SPEED 2600000000

#ifndef N
#error N not defined
#endif 

#include <assert.h>

float *x, *y, alpha; 

void warmup(float *x, float *y, int size, float alpha);

void verify(int n)
{
    int i, k;
    for (i=0; i<n; i++)
    {
       if (fabs(y[i] - x[2*i]+x[2*i]+x[2*i+1]/alpha)>1e-6)
       {
            printf("Error at %d\n", i);

            for (k=0; k<n; k++)
            {
                printf("Got: %f, expected: %f\n", y[k], (x[2*k]+x[2*k]+x[2*k+1]/alpha));
            }
            exit(1);
       }
    }
}

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
//verify(n);
    return 0;
}

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

float *x, *y, h0, h1, h2, h3; 

void FIR(float *y, float *x, float h0, float h1, float h2, float h3, int size);


void verify(int n)
{
    int i, k;
    for (i=0; i<size-3; i++)
    {
       if (fabs(y[i] - (h3*x[i] + h2*x[i+1] + h1*x[i+2] + h0*x[i+3]))>1e-6)
       {
            printf("Error at %d\n", i);

            for (k=0; k<n; k++)
            {
                printf("Got: %f, expected: %f\n", y[k], h3*x[i] + h2*x[i+1] + h1*x[i+2] + h0*x[i+3]);
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
    x = (float*)malloc(n*sizeof(float));

    
    srand ( time(NULL) );

    h0 = ((float)rand()/((float)(RAND_MAX)+(float)(1)));
    h1 = ((float)rand()/((float)(RAND_MAX)+(float)(1)));
    h2 = ((float)rand()/((float)(RAND_MAX)+(float)(1)));
    h3 = ((float)rand()/((float)(RAND_MAX)+(float)(1)));
    
    for(i = 0; i<n; i++) {
        x[i] = ((float)rand()/((float)(RAND_MAX)+(float)(1)));
    }
  
    microbench();
    verify(n);
    return 0;
}

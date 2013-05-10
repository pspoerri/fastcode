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
#include <malloc.h>

float *x, *y, h0, h1, h2, h3; 

void FIR(float *y, float *x, float h0, float h1, float h2, float h3, int size);


void verify(int n)
{
    int i, k;
    for (i=0; i<n-3; i++)
    {
       float val = fabs(y[i] - (h3*x[i] + h2*x[i+1] + h1*x[i+2] + h0*x[i+3]));
       if (val >1e-6)
       {
            printf("Error at %d with %f\n", i, val);

            for (k=0; k<n-3; k++)
            {
                printf("Got: %f, expected: %f\n", y[k], h3*x[k] + h2*x[k+1] + h1*x[k+2] + h0*x[k+3]);
            }
            exit(1);
       }
    }
}

// From http://stackoverflow.com/questions/6320264/how-to-align-pointer
int roundUp(size_t a, size_t b) { return (1 + (a - 1) / b) * b; }

//We assume here that size_t and void* can be converted to each other
void *malloc_aligned(size_t size, size_t align)
{
    assert(align % sizeof(size_t) == 0);
    assert(sizeof(void*) == sizeof(size_t)); //Not sure if needed, but whatever

    void *p = malloc(size + 2 * align);
    if (p != NULL)
    {
        size_t base = (size_t)p;
        p = (char*)roundUp(base, align) + align;
        ((size_t*)p)[-1] = (size_t)p - base;
    }
    return p;
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
            FIR(y,x, h0,h1,h2,h3,n);
        }
        RDTSC(end); CPUID();
        
        cycles = ((double)COUNTER_DIFF(end, start));

        if(cycles >= CYCLES_REQUIRED) break;

        num_runs *= 2;
    }
    
    CPUID(); RDTSC(start);    
    for (i=0; i<num_runs; i++)
    {
        FIR(y,x, h0,h1,h2,h3,n);
    }
    RDTSC(end); CPUID();
    
    cycles = ((double)COUNTER_DIFF(end, start)) / ((double) num_runs);

    sum = 0.0;

    sum = y[0];
    double total_flops = n*7;
    double flops_cycle = total_flops/cycles;
    printf("{'size': %d, 'cycles': %f, 'total_sum': %f, 'num_runs': %d, 'flops_cycle': %f }", n, cycles, sum, num_runs, flops_cycle); 
}

int main(){
    int i;
    int n = N;
    
    y = (float*) malloc_aligned( n*sizeof(float), 32);
    x = (float*) malloc_aligned( n*sizeof(float), 32);
//    y = (float*) malloc(n*sizeof(float));
//    x = (float*) malloc(n*sizeof(float));
    srand ( time(NULL) );

    h0 = ((float)rand()/((float)(RAND_MAX)+(float)(1)));
    h1 = ((float)rand()/((float)(RAND_MAX)+(float)(1)));
    h2 = ((float)rand()/((float)(RAND_MAX)+(float)(1)));
    h3 = ((float)rand()/((float)(RAND_MAX)+(float)(1)));
    
    h0 = 1.0;
    h1 = 2.0;
    h2 = 3.0;
    h3 = 4.0;
    for(i = 0; i<n; i++) {
    //    x[i] = ((float)rand()/((float)(RAND_MAX)+(float)(1)));
        x[i] = (float) i;
    }
  
    microbench();
    verify(n);
    return 0;
}

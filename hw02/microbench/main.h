#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "rdtsc.h" // Timing macros

#define NUM_RUNS 50
#define CYCLES_REQUIRED 1E8

#include "funcs.h" // Reduction functions

#ifdef __cplusplus
extern "C" {
#endif

double microbench_cos( double * x, double * y, double *dest, size_t n);
double microbench_sin( double * x, double * y, double *dest, size_t n);
double microbench_exp( double * x, double * y, double *dest, size_t n);
double microbench_log( double * x, double * y, double *dest, size_t n);
double microbench_oneover( double * x, double * y, double *dest, size_t n);
double microbench_squared( double * x,double * y, double *dest, size_t n);

#ifdef __cplusplus
}
#endif
//#error Please comment out the next two lines under linux, then comment this error
//#include "stdafx.h" //Visual studio expects this line to be the first one, comment out if different compiler
//#include <windows.h> // Include if under windows

#ifndef WIN32
#include <sys/time.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "rdtsc.h"

#define NUM_RUNS 1
#define CYCLES_REQUIRED 1e8
#define FREQUENCY 2.6e9

#define CALIBRATE

int m, n, k;
double *A, *B, *C;

/* 
 * Straightforward implementation of matrix-matrix multiplication:
 * C = AB + C
 */

void compute() {
  int i,j,h;
  for(i = 0; i < m; ++i) {
    for(j = 0; j < n; ++j) {
      for(h = 0; h < k; ++h) {
        C[i*n+j] += A[i*k+h] * B[h*n+j];
      }
    }
  }
}

/* 
 * Timing function based on the TimeStep Counter of the CPU.
 */

double rdtsc() {
  int i, num_runs;
  double cycles;
  tsc_counter start, end;
  
  num_runs = NUM_RUNS;

/* 
 * The CPUID instruction serializes the pipeline.
 * Using it, we can create execution barriers around the code we want to time.
 * The calibrate section is used to make the computation large enough so as to 
 * avoid measurements bias due to the timing overhead.
 */
#ifdef CALIBRATE
  while(num_runs < (1 << 14)) {
      CPUID(); RDTSC(start);
      for (i = 0; i < num_runs; ++i) {
          compute();
      }
      RDTSC(end); CPUID();

      cycles = (double)(COUNTER_DIFF(end, start));

      if(cycles >= CYCLES_REQUIRED) break;

      num_runs *= 2;
  }
#endif

  CPUID(); RDTSC(start);
  for (i = 0; i < num_runs; ++i) {
    compute();
  }
  RDTSC(end); CPUID();

  cycles = (double)(COUNTER_DIFF(end, start))/num_runs;
  return cycles;
}

double c_clock() {
  int i, num_runs;
  double cycles;
  clock_t start, end;

  num_runs = NUM_RUNS;
#ifdef CALIBRATE
  while(num_runs < (1 << 14)) {
      start = clock();
      for (i = 0; i < num_runs; ++i) {
          compute();
      }
      end = clock();

      cycles = (double)(end-start);

      // Same as in c_clock: CYCLES_REQUIRED should be expressed accordingly to the order of magnitude of CLOCKS_PER_SEC
      if(cycles >= CYCLES_REQUIRED/(FREQUENCY/CLOCKS_PER_SEC)) break;

      num_runs *= 2;
  }
#endif

  start = clock();
  for(i=0; i<num_runs; ++i)
    { compute(); }
  end = clock();

  return (double)(end-start)/num_runs;
}

#ifndef WIN32
double timeofday() {
  int i, num_runs;
  double cycles;
  struct timeval start, end;

  num_runs = NUM_RUNS;
#ifdef CALIBRATE
  while(num_runs < (1 << 14)) {
      gettimeofday(&start, NULL);
      for (i = 0; i < num_runs; ++i) {
          compute();
      }
      gettimeofday(&end, NULL);

      cycles = (double)((end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1e6)*FREQUENCY;

      if(cycles >= CYCLES_REQUIRED) break;

      num_runs *= 2;
  }
#endif

  gettimeofday(&start, NULL);
  for(i=0; i < num_runs; ++i) {
    compute(); 
  }
  gettimeofday(&end, NULL);
  
  return (double)((end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1e6)/ num_runs;
}

#else

double gettickcount() {
  int i, num_runs;
  double cycles, start, stop;

  num_runs = NUM_RUNS;
#ifdef CALIBRATE
  while(num_runs < (1 << 14)) {
      start = (double)GetTickCount();
      for (i = 0; i < num_runs; ++i) {
          compute();
      }
      end = (double)GetTickCount();

      cycles = (end-start)*FREQUENCY/1e3; // end-start provides a measurement in the order of milliseconds

      if(cycles >= CYCLES_REQUIRED) break;

      num_runs *= 2;
  }
#endif

  start = (double)GetTickCount();
  for(i=0; i < num_runs; ++i) {
    compute(); 
  }
  end = (double)GetTickCount();

  return (start-end)/num_runs;
}

double queryperfcounter(LARGE_INTEGER f) {
  int i, num_runs;
  double cycles;
  LARGE_INTEGER start, end;

  num_runs = NUM_RUNS;
#ifdef CALIBRATE
  while(num_runs < (1 << 14)) {
      QueryPerformanceCounter(&start);
      for (i = 0; i < num_runs; ++i) {
          compute();
      }
      QueryPerformanceCounter(&end);

      cycles = (double)(end.QuadPart - start.QuadPart);
      
      // Same as in c_clock: CYCLES_REQUIRED should be expressed accordingly to the order of magnitude of f
      if(cycles >= CYCLES_REQUIRED/(FREQUENCY/f)) break; 

      num_runs *= 2;
  }
#endif

  QueryPerformanceCounter(&start);
  for(i=0; i < num_runs; ++i) {
    compute(); 
  }
  QueryPerformanceCounter(&end);

  return (double)(end.QuadPart - start.QuadPart)/num_runs;
}

#endif

int main(int argc, char **argv){

  int i;
  double r;
  double c;
  double t;
#ifdef WIN32  
  __int64 f;
#endif
  double p;
  if (argc!=4) {printf("usage: mmm <m> <k> <n>\n"); return -1;}
  m = atoi(argv[1]);
  k = atoi(argv[2]);
  n = atoi(argv[3]);
  printf("m=%d k=%d n=%d\n",m,k,n);

  A = (double*)malloc(m*k*sizeof(double));
  B = (double*)malloc(k*n*sizeof(double));
  C = (double*)malloc(m*n*sizeof(double));

  for(i =0; i<m*k;i++) A[i]=i;
  for(i =0; i<k*n;i++) B[i]=i;

  r = rdtsc();
  printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n\n", r, r/(FREQUENCY), (FREQUENCY)/1e6);

  c = c_clock();
  printf("C clock() function:\n %lf cycles measured. On some systems, this number seems to be actually computed from a timer in seconds then transformed into clock ticks using the variable CLOCKS_PER_SEC. Unfortunately, it appears that CLOCKS_PER_SEC is sometimes set improperly. (According to this variable, your computer should be running at %lf MHz). In any case, dividing by this value should give a correct timing: %lf seconds. \n\n",c, (double) CLOCKS_PER_SEC/1e6, c/CLOCKS_PER_SEC);

#ifndef WIN32
  t = timeofday();
  printf("C gettimeofday() function:\n %lf seconds measured\n\n",t);
#else
  t = gettickcount();
  printf("Windows getTickCount() function:\n %lf milliseconds measured\n\n",t);

  QueryPerformanceFrequency((LARGE_INTEGER *)&f);

  p = queryperfcounter(f);
  printf("Windows QueryPerformanceCounter() function:\n %lf cycles measured => %lf seconds, with reported CPU frequency %lf MHz\n\n",p,p/f,(double)f);
#endif

 // printf("Type anything to leave\n");
 // scanf("%d",&i);
  return 0;
}

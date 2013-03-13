/*
* comp.c - contains the function superslow that you need to optimize
*
* How to write fast numerical code, spring 2013
* Georg Ofenbeck, Daniele Spampinato, Markus Pueschel
* ETH Zurich
*
*/

#include <math.h>
#include <stdio.h>
#include "comp.h"
#include "perf.h"

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif


/* f(x1,x2, i, j) rotates the input vector
*/
double f(double x1, double x2, double* y1, double * y2, int i, int j)
{
	double m[2][2];	

	if (i %4 == 0)
	{
		m[0][0] = cos(i);
		m[0][1] = sin(i);
		m[1][0] = -sin(i);
		m[1][1] = cos(i);
	}
	else
	{
		m[0][0] = cos(-i);
		m[0][1] = sin(-i);
		m[1][0] = -sin(-i);
		m[1][1] = cos(-i);

	}

	*y1 = m[0][0] * x1 + m[0][1]* x2;
	*y2 = m[1][0] * x1 + m[1][1]* x2;
}

/* This is the function you need to optimize. It takes one
square matrix as input
*/
void superslow(smat_t *a)
{
	int i, j;
	double x1,x2,y1,y2;
	double sum1, sum2;


	// j is the column of a we're computing right now
	for(j = 0; j < a->n; j++)
	{

		// i is the row of a we're computing right now
		for(i = 0; i < a->n; i=i+2)        
		{            
			// First, compute f(A) for the element of a in question
			x1 = get_elt(a,i,j);
			x2 = get_elt(a,i+1,j);
			f(x1,x2,&y1,&y2, i, j);

			// Add this to the value of a we're computing and store it                
			sum1 = get_elt(a, i, j) + y1;
			sum2 = get_elt(a, i+1, j) + y2;
			set_elt(a, i, j, sum1);
			set_elt(a, i+1, j, sum2);            
		}
	}
}





/* 
* Called by the driver to register your functions
* Use add_function(func, description) to add your own functions
*/
void register_functions()
{
	// Registers comp_superslow with the driver
	add_function(&superslow, "superslow: original function");
//	add_function(&fast, "fast: optimized version 1");
	//Add your functions here
	//add_function(&superslow2, "superslow: Optimization X");


}

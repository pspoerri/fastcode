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

void v1_localized_variables(smat_t *a)
{
	int i, j;
	double x1,x2,y1,y2;
	double sum1, sum2;

    int n = a->n;
	// j is the column of a we're computing right now
	for(j = 0; j < n; j++)
	{

		// i is the row of a we're computing right now
		for(i = 0; i < n; i=i+2)        
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

void v2_inline_f(smat_t *a)
{
	int i, j;
	double x1,x2,y1,y2;
	double sum1, sum2;

    int n = a->n;
	// j is the column of a we're computing right now
	for(j = 0; j < n; j++)
	{

		// i is the row of a we're computing right now
		for(i = 0; i < n; i=i+2)        
		{            
			// First, compute f(A) for the element of a in question
			x1 = get_elt(a,i,j);
			x2 = get_elt(a,i+1,j);


            // added f
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
	       
	       	y1 = m[0][0] * x1 + m[0][1]* x2;
	       	y2 = m[1][0] * x1 + m[1][1]* x2;
            // end f

			// Add this to the value of a we're computing and store it                
			sum1 = get_elt(a, i, j) + y1;
			sum2 = get_elt(a, i+1, j) + y2;
			set_elt(a, i, j, sum1);
			set_elt(a, i+1, j, sum2);            
		}
	}
}

void v3_replace_inner_functions(smat_t *a)
{
	int i, j;
	double x1,x2,y1,y2;
	double sum1, sum2;

    int n = a->n;
	// j is the column of a we're computing right now
	for(j = 0; j < n; j++)
	{

		// i is the row of a we're computing right now
		for(i = 0; i < n; i=i+2)        
		{            
			// First, compute f(A) for the element of a in question
			x1 = get_elt(a,i,j);
			x2 = get_elt(a,i+1,j);


            // added f
            double m[2][2];	

            int p = i;
            if (i%4 != 0) {
                p = -i;
            }
            double cosp = cos(p);
            double sinp = sin(p);
	       
	       	y1 = cosp * x1 + sinp * x2;
	       	y2 = cosp * x2 - sinp * x1;
            // end f

			// Add this to the value of a we're computing and store it                
			sum1 = get_elt(a, i, j) + y1;
			sum2 = get_elt(a, i+1, j) + y2;
			set_elt(a, i, j, sum1);
			set_elt(a, i+1, j, sum2);            
		}
	}
}

void v4_reorder_inner_loop(smat_t *a)
{
	int i, j;
	double x1,x2,y1,y2;
	double sum1, sum2;

    int n = a->n;
	// j is the column of a we're computing right now
	for(i = 0; i < n; i=i+2)        
	{   
	    for(j = 0; j < n; j++)
		// i is the row of a we're computing right now
		{            
			// First, compute f(A) for the element of a in question
			x1 = get_elt(a,i,j);
			x2 = get_elt(a,i+1,j);


            // added f
            double m[2][2];	

            int p = i;
            if (i%4 != 0) {
                p = -i;
            }
            double cosp = cos(p);
            double sinp = sin(p);
	       
	       	y1 = cosp * x1 + sinp * x2;
	       	y2 = cosp * x2 - sinp * x1;
            // end f

			// Add this to the value of a we're computing and store it                
			sum1 = get_elt(a, i, j) + y1;
			sum2 = get_elt(a, i+1, j) + y2;
			set_elt(a, i, j, sum1);
			set_elt(a, i+1, j, sum2);            
		}
	}
}

void v5_reorder_computations(smat_t *a)
{
	int i, j;
	double x1,x2,y1,y2;
	double sum1, sum2;

    int n = a->n;
	// j is the column of a we're computing right now
	for(i = 0; i < n; i=i+2)        
	{   
        int p = i;
        if (i%4 != 0) {
            p = -i;
        }
        double cosp = cos(p);
        double sinp = sin(p);

	    for(j = 0; j < n; j++)
		// i is the row of a we're computing right now
		{            
			// First, compute f(A) for the element of a in question
			x1 = get_elt(a,i,j);
			x2 = get_elt(a,i+1,j);

	       	y1 = cosp * x1 + sinp * x2;
	       	y2 = cosp * x2 - sinp * x1;
            // end f

			// Add this to the value of a we're computing and store it                
			sum1 = get_elt(a, i, j) + y1;
			sum2 = get_elt(a, i+1, j) + y2;
			set_elt(a, i, j, sum1);
			set_elt(a, i+1, j, sum2);            
		}
	}
}

void v6_reorder_variables(smat_t *a)
{
	int i, j;
	double x1,x2,y1,y2;
	double sum1, sum2;

    int n = a->n;
	// j is the column of a we're computing right now
	for(i = 0; i < n; i=i+2)        
	{   
        int p = i;
        if (i%4 != 0) {
            p = -i;
        }
        double cosp = cos(p);
        double sinp = sin(p);

	    for(j = 0; j < n; j++)
		// i is the row of a we're computing right now
		{            
			// First, compute f(A) for the element of a in question
			x1 = get_elt(a,i,j);
			x2 = get_elt(a,i+1,j);

	       	y1 = cosp * x1 + sinp * x2;
	       	y2 = cosp * x2 - sinp * x1;
            // end f

			// Add this to the value of a we're computing and store it                
			sum1 = x1 + cosp * x1 + sinp * x2;
			sum2 = x2 + cosp * x2 - sinp * x1;
			set_elt(a, i, j, sum1);
			set_elt(a, i+1, j, sum2);            
		}
	}
}

void v7_restructure_cos_sin(smat_t *a)
{
	int i, j;
	double x1,x2,y1,y2;
	double sum1, sum2;

    int n = a->n;
	// j is the column of a we're computing right now
    int factor = 1;
	for(i = 0; i < n; i=i+2)        
	{   
        int p = i;
        if (i%4 != 0) {
            p = -i;
        }
        double cosp = cos(i);
        double sinp = sin(factor*i);
        factor = -factor;

        for(j = 0; j < n; j++)
		// i is the row of a we're computing right now
		{            
			// First, compute f(A) for the element of a in question
			x1 = get_elt(a,i,j);
			x2 = get_elt(a,i+1,j);

	       	y1 = cosp * x1 + sinp * x2;
	       	y2 = cosp * x2 - sinp * x1;
            // end f

			// Add this to the value of a we're computing and store it                
			sum1 = x1 + cosp * x1 + sinp * x2;
			sum2 = x2 + cosp * x2 - sinp * x1;
			set_elt(a, i, j, sum1);
			set_elt(a, i+1, j, sum2);            
		}
	}
}

void v8_inline_get_and_set(smat_t *a)
{
	int i, j;
	double x1,x2,y1,y2;
	double sum1, sum2;

    double *mat = a->mat;

    int n = a->n;
	// j is the column of a we're computing right now
    int factor = 1;
	for(i = 0; i < n; i=i+2)        
	{   
        int p = i+1;
        double cosp = cos(i);
        double sinp = sin(factor*i);
        factor = -factor;

        for(j = 0; j < n; j++)
		// i is the row of a we're computing right now
		{            
			// First, compute f(A) for the element of a in question
			x1 = mat[i * n + j];
			x2 = mat[p * n + j];

	       	y1 = cosp * x1 + sinp * x2;
	       	y2 = cosp * x2 - sinp * x1;
            // end f

			// Add this to the value of a we're computing and store it                
			mat[i * n + j] = x1 + cosp * x1 + sinp * x2;
			mat[p * n + j] = x2 + cosp * x2 - sinp * x1;      
		}
	}
}

void v9_remove_add_op_cos(smat_t *a)
{
	int i, j;
	double x1,x2,y1,y2;
	double sum1, sum2;

    double *mat = a->mat;

    int n = a->n;
	// j is the column of a we're computing right now
    int factor = 1;
	for(i = 0; i < n; i=i+2)        
	{   
        int p = i+1;
        double cosp = cos(i)+1;
        double sinp = sin(factor*i);
        factor = -factor;

        for(j = 0; j < n; j++)
		// i is the row of a we're computing right now
		{            
			// First, compute f(A) for the element of a in question
			x1 = mat[i * n + j];
			x2 = mat[p * n + j];

			// Add this to the value of a we're computing and store it                
			mat[i * n + j] = cosp * x1 + sinp * x2;
			mat[p * n + j] = cosp * x2 - sinp * x1;      
		}
	}
}

void v10_inner_loop_unrolling(smat_t *a)
{
	int i, j;
	double x1,x2,y1,y2;
	double sum1, sum2;

    double *mat = a->mat;

    int n = a->n;
	// j is the column of a we're computing right now
    int factor = 1;
	for(i = 0; i < n; i=i+2)        
	{   
        double cosp = cos(i)+1;
        double sinp = sin(factor*i);
        factor = -factor;

        int p = i+1;        
        for(j = 0; j < n; j=j+2)
		// i is the row of a we're computing right now
		{            
			// First, compute f(A) for the element of a in question
			x1 = mat[i * n + j];
            y1 = mat[i * n + j+1]; 
			x2 = mat[p * n + j];
            y2 = mat[p * n + j+1];

			// Add this to the value of a we're computing and store it                
			mat[i * n + j] = cosp * x1 + sinp * x2;
			mat[i * n + j+1] = cosp * y1 + sinp * y2;
			mat[p * n + j] = cosp * x2 - sinp * x1;      
			mat[p * n + j+1] = cosp * y2 - sinp * y1;  
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
    add_function(&v1_localized_variables, "v1_localized_variables: Localized Loop variables");
    add_function(&v2_inline_f, "v2_inline_f: Inline f");
    add_function(&v3_replace_inner_functions, "v3_replace_inner_functions: Replace Inner functions");
    add_function(&v4_reorder_inner_loop, "v4_reorder_inner_loop: Reorder Inner Loops");
    add_function(&v5_reorder_computations, "v5_reorder_computations: Reorder COS and SIN");
    add_function(&v6_reorder_variables, "v6_reorder_variables: Move x1 and x2 into sum");
    add_function(&v7_restructure_cos_sin, "v7_restructure_cos_sin: Restructure cos and sin and remove modulo operation");
    add_function(&v8_inline_get_and_set, "v8_inline_get_and_set: Inline get and set functions");
    add_function(&v9_remove_add_op_cos, "v9_remove_add_op_cos: Replace x1+cosp*x1 with x1*(cosp+1)");
    add_function(&v10_inner_loop_unrolling, "v10_inner_loop_unrolling: Unroll inner loop");
//	add_function(&fast, "fast: optimized version 1");
	//Add your functions here
	//add_function(&superslow2, "superslow: Optimization X");


}

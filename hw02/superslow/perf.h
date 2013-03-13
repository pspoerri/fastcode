/*
 * perf.h - function for measuring the performance of an MMM function
 *
 * How to write fast numerical code, spring 2013
 * Georg Ofenbeck, Daniele Spampinato, Markus Pueschel
 * ETH Zurich
 */

#ifndef __PERF_H 
#define __PERF_H

#include "comp.h"

#define MAX_FUNCS 32

void add_function(comp_func, char *);

#endif /*  __PERF_H */

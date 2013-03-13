/*
 * comp.h - function to be optimized
 * matrices.
 *
 * How to write fast numerical code, spring 2013
 * Georg Ofenbeck, Daniele Spampinato, Markus Pueschel
 * ETH Zurich
 */

#ifndef __COMP_H
#define __COMP_H

#include <math.h>
#include "smat.h"

/* prototype of the function you need to optimize */
typedef void (*comp_func)(smat_t*);

void register_functions();
void superslow(smat_t *a);

#endif /* __COMP_H */

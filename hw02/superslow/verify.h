/*
 * verify.h - checker functional equivalence of two MMM
 *   implementations
 *
 *
 * How to write fast numerical code, spring 2013
 * Georg Ofenbeck, Daniele Spampinato, Markus Pueschel
 * ETH Zurich
 */

#ifndef __VERIFY_H
#define __VERIFY_H

#include "comp.h"

int check_valid(comp_func checkFunc, int size);

#endif /* __VERIFY_H */

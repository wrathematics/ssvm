// This file is free and unencumbered software released into the public domain.
// You may modify it for any purpose with or without attribution.
// See the Unlicense specification for full details http://unlicense.org/

// To make ssvm useable outside of R, you need to modify every definition in
// this file appropriately, and delete the R header files.  Comments in this
// file are to help someone porting this to another (non-R) system.

#ifndef SSVM_UTILS_DEFS_H_
#define SSVM_UTILS_DEFS_H_

// ----------------------------------------------------------------------------
// RNG
// ----------------------------------------------------------------------------

#include <R.h>      // delete me
#include <Rmath.h>  // delete me

// rng initializer and ender; probably sufficient to set the second def to a blank
#define STARTRNG GetRNGstate()
#define ENDRNG PutRNGstate()

// generate a single random uniform number
#define RUNIF unif_rand()


#endif

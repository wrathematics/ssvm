/*  Copyright (c) 2017 Drew Schmidt
    All rights reserved.
    
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    
    1. Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
    
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
    TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
    PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#ifndef SSVM_SAMPLERS_H
#define SSVM_SAMPLERS_H

#include "defs.h"
#include "quicksort.h"
#include "safeomp.h"


/**
 * Sample a single value from "low" to "high-1" (inclusive of each), i.e.
 * [low, high)
 * 
 * @param low,high (input) boundaries for the sampling interval
 */
static inline int sample_unif(const int low, const int high)
{
  return (int) low + (high - low)*RUNIF ;
}



/**
 * Reservoir sampler.
 * 
 * @param maxval (input) determines the values sampled from: [0, maxval)
 * @param samplen (input) number of values of [0, maxval) sampled
 * @param samp (output) sampled values
 */
static inline void sample_res(const len_t maxval, const len_t samplen, len_t *const restrict samp)
{
  SAFE_FOR_SIMD
  for (int i=0; i<samplen; i++)
    samp[i] = i+1;
  
  for (int i=samplen; i<maxval; i++)
  {
    int flip = sample_unif(0, i);
    if (flip < samplen)
      samp[flip] = i+1;
  }
  
  sorted_qs(samplen, samp);
}


#endif

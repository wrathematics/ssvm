/*  Copyright (c) 2016 Drew Schmidt
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


#ifndef SSVM_BLAS_H
#define SSVM_BLAS_H

#include "types.h"

#define ROW_MAJOR 0
#define COL_MAJOR 1

void dlassq_(const int *n, const double *x, const int *incx, const double *scale, double *sumsq);

static inline double vecvecprod(cint storage, cbool intercept, cint n, cint p, cdbl_r x, cdbl_r w)
{
  double tmp = 0.0;
  
  if (intercept)
    tmp += w[0];
  
  if (storage == COL_MAJOR)
  {
    for (len_t i=0; i<p-intercept; i++)
      tmp += w[i+intercept] * x[n*i];
  }
  else
  {
    for (len_t i=0; i<p-intercept; i++)
      tmp += w[i+intercept] * x[i];
  }
  
  return tmp;
}

// C translation of level 1 BLAS function DNRM2
static inline double C_dnrm2(cint n, cdbl_r x, cint incx)
{
  double norm, scale, ssq;
  
  
  if (n < 1 || incx < 1)
    norm = 0.;
  else if (n == 1)
    norm = fabs(x[0]);
  else
  {
    scale = 0.;
    ssq = 1.;
    
    dlassq_(&n, x, &incx, &scale, &ssq);
    norm = scale * sqrt(ssq);
  }
  
  return norm;
}

static inline double vecnorm(cint n, cdbl_r x)
{
  return C_dnrm2(n, x, 1);
}


#endif

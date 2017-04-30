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


#ifndef SSVM_TYPES_H
#define SSVM_TYPES_H

#include <stdint.h>
#include <stdbool.h>

typedef const bool    cbool;
typedef const char    cchar;
typedef const int     cint;
typedef const double  cdbl;

typedef char *const restrict char_r;
typedef const char *const restrict cchar_r;

typedef int *const restrict int_r;
typedef const int *const restrict cint_r;

typedef double *const restrict dbl_r;
typedef const double *const restrict cdbl_r;


typedef struct svmparam_t
{
  bool init_w;          // should w be initialized to 0, or is this an update?
  bool intercept;       // include an intercept in the model?
  uint32_t k;           // currently ignored
  double lambda;        // regularization parameter
  uint64_t niter;       // number of iterations
} svmparam_t;

typedef struct svmdata_t
{
  uint32_t nr;          // number of rows
  uint32_t nc;          // number of cols
  double *restrict x;   // predictors
  int *restrict y;      // response
  double *restrict w;   // weights
} svmdata_t;


#endif

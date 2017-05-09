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


#ifndef LIBSSVM_H_
#define LIBSSVM_H_


#include "utils/types.h"

#define SSVM_OK         0
#define SSVM_BADMALLOC -1



static inline int svm_pegasos_setparams_(svmparam_t *p, svmparam_t args)
{
  // TODO add param checks, on fail return position
  
  p->intercept = !args.intercept ? false : true;
  p->init_w = !args.init_w ? false : true;
  p->k = args.k ? args.k : 5;
  p->lambda = args.lambda ? args.lambda : 0.1;
  p->niter = args.niter ? args.niter : 1e5;
  
  return 0;
}

#define svm_pegasos_setparams(p,...) svm_pegasos_setparams_(p, (svmparam_t){__VA_ARGS__});



static inline int svm_pegasos_setdata_(svmdata_t *d, svmdata_t args)
{
  if (args.nr)
    d->nr = args.nr;
  else
    return(-1);
  
  if (args.nc)
    d->nc = args.nc;
  else
    return(-2);
  
  if (args.x)
    d->x = args.x;
  else
    return(-3);
  
  if (args.y)
    d->y = args.y;
  
  if (args.w)
    d->w = args.w;
  
  return 0;
}

#define svm_pegasos_setdata(d,...) svm_pegasos_setdata_(d, (svmdata_t){__VA_ARGS__});



// void svm_pegasos_fit(cint nrows, cint ncols, cdbl_r x, cdbl_r y, const svmparam_t *const restrict params, dbl_r w);
int svm_pegasos_fit(const svmdata_t *const restrict data, const svmparam_t *const restrict params);
void svm_pegasos_predict(cbool intercept, const svmdata_t *const restrict newdata);


#endif

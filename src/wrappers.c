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


#include <R.h>
#include <Rinternals.h>

#include "ssvm.h"

#define INT(x) INTEGER(x)[0]
#define DBL(x) REAL(x)[0]


SEXP R_svm_pegasos_fit(SEXP intercept, SEXP k, SEXP lambda, SEXP niter, SEXP x, SEXP y)
{
  SEXP w;
  const int nr = nrows(x);
  const int nc = ncols(x);
  
  if (nr != LENGTH(y))
    error("number of rows of 'x' should match the length of 'y'");
  
  svmparam_t p;
  svm_pegasos_setparams(&p, .intercept=INT(intercept), .init_w=true, .k=INT(k), .lambda=DBL(lambda), .niter=INT(niter));
  
  svmdata_t data;
  svm_pegasos_setdata(&data, .nr=nr, .nc=nc, .x=REAL(x), .y=INTEGER(y));
  
  PROTECT(w = allocVector(REALSXP, nc+INT(intercept)));
  data.w = REAL(w);
  
  
  // R_PreserveObject(x);
  // xpose_inplace(nr, nc, REAL(x));
  
  svm_pegasos_fit(&data, &p);
  
  // xpose_inplace(nc, nr, REAL(x));
  // R_ReleaseObject(x);
  
  
  UNPROTECT(1);
  return w;
}



SEXP R_svm_pegasos_pred(SEXP x_new, SEXP w, SEXP intercept)
{
  const int nr = nrows(x_new);
  const int nc = ncols(x_new);
  SEXP pred;
  PROTECT(pred = allocVector(INTSXP, nr));
  
  svmdata_t newdata;
  svm_pegasos_setdata(&newdata, .nr=nr, .nc=nc, .x=REAL(x_new), .y=INTEGER(pred), .w=REAL(w));
  
  svm_pegasos_pred(INT(intercept), &newdata);
  
  UNPROTECT(1);
  return pred;
}



SEXP R_svm_recode_response(SEXP response, SEXP validate_)
{
  const int len = LENGTH(response);
  
  if (len == 1)
    return ScalarInteger(1);
  
  const int validate = INT(validate_);
  const int *const pt = INTEGER(response);
  int min = pt[0];
  int max = pt[0];
  
  if (!validate)
  {
    for (int i=1; i<len; i++)
    {
      if (pt[i] < min)
        min = pt[i];
      else if (pt[i] > max)
        max = pt[i];
      
      if (max - min != 0)
        break;
    }
  }
  else
  {
    for (int i=1; i<len; i++)
    {
      if (max - min > 0  &&  pt[i] - max != 0  &&  pt[i] - min != 0)
        error("response vector is not 2-class\n");
      if (pt[i] < min)
        min = pt[i];
      else if (pt[i] > max)
        max = pt[i];
    }
  }
  
  
  SEXP ret;
  PROTECT(ret = allocVector(INTSXP, len));
  int *const pt_ret = INTEGER(ret);
  for (int i=0; i<len; i++)
  {
    if (pt[i] == min)
      pt_ret[i] = 1;
    else
      pt_ret[i] = -1;
  }
  
  
  UNPROTECT(1);
  return ret;
}

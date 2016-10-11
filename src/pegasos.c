/*  Copyright (c) 2016, Schmidt
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


// Reference:  http://ttic.uchicago.edu/~nati/Publications/PegasosMPB.pdf

#include <math.h>

#include "ssvm.h"

#include "utils/blas.h"
#include "utils/defs.h"
#include "utils/safeomp.h"


// TODO coinflip of x==0 ?
#define SIGN(x) ((x) > 0 ? 1 : -1)
#define MIN(a,b) ((a) < (b) ? (a) : (b))


static inline uint32_t draw(uint32_t n)
{
  // draw digit 0 to (n-1)
  return (uint32_t) ((int) n*RUNIF);
}


/**
 * @param n,p (input) dim of x
 * @param x (input) data
 * @param y (input) response
 * @param params (input) pegasos params
 * @param w (output) p-length vector if intercept=false; p+1 otherwise
 */
void svm_pegasos_fit(const svmdata_t *const restrict data, const svmparam_t *const restrict params)
{
  const int n = data->nr;
  const int p = data->nc;
  const double *const x = data->x;
  const int *const y = data->y;
  double *const w = data->w;
  
  // const int k = params->k; // TODO
  const bool intercept = params->intercept;
  const int w_len = intercept ? p+1 : p;
  
  const double invlambda = 1.0/params->lambda;
  const double rtinvlambda = sqrt(invlambda);
  
  
  if (params->init_w)
    memset(w, 0, w_len*sizeof(*w));
  
  
  STARTRNG;
  
  for (uint32_t t=1; t<=params->niter; t++)
  {
    const double invt = 1.0 / ((double) t);
    const uint32_t index = draw(n);
    
    // NOTE to self: if x is transposed...
    // const double tmp = y[index] * vecvecprod(ROW_MAJOR, intercept, n, w_len, x+(index*p), w);
    const double tmp = y[index] * vecvecprod(COL_MAJOR, intercept, n, w_len, x+index, w);
    
    if (tmp < 1)
    {
      double eta_t = invlambda * invt;
      
      // w = (1-1/t)*w + eta_t*y[index] * x[index, ]
      if (intercept)
        w[0] = (1.0 - invt)*w[0] + eta_t*y[index];
      for (int i=0; i<p; i++)
        w[i+intercept] = (1.0 - invt)*w[i+intercept] + eta_t*y[index]*x[index + n*i];
        // NOTE to self: if x is transposed...
        // w[i+intercept] = (1.0 - invt)*w[i+intercept] + eta_t*y[index]*x[index*p + i];
    }
    else
    {
      // w = (1-1/t)*w
      SAFE_FOR_SIMD
      for (int i=0; i<w_len; i++)
        w[i] *= 1.0 - invt;
    }
    
    double coef = rtinvlambda / vecnorm(w_len, w);
    coef = MIN(coef, 1.0);
    if (coef < 1)
    {
      SAFE_FOR_SIMD
      for (int i=0; i<w_len; i++)
        w[i] *= coef;
    }
  }
  
  
  ENDRNG;
}



/* 
 * @param 
 * @param pred (output); n-length vector
 */
void svm_pegasos_pred(cbool intercept, const svmdata_t *const restrict newdata)
{
  const int n = newdata->nr;
  const int p = newdata->nc;
  const double *const x_new = newdata->x;
  int *const pred = newdata->y;
  const double *const w = newdata->w;
  
  #pragma omp parallel for default(none) if(n>OMP_MIN_SIZE)
  for (int i=0; i<n; i++)
  {
    double tmp = vecvecprod(COL_MAJOR, intercept, n, p, x_new+i, w);
    pred[i] = SIGN(tmp);
  }
}

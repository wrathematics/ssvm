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


#include <math.h>

#include "utils/blas.h"
#include "utils/safeomp.h"


// TODO coinflip of x==0 ?
#define SIGN(x) ((x) > 0 ? 1 : -1)


/* 
 * @param 
 * @param pred (output); n-length vector
 */
void svm_pegasos_predict(cbool intercept, const svmdata_t *const restrict newdata)
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

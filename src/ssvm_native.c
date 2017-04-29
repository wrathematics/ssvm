/* Automatically generated. Do not edit by hand. */

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <stdlib.h>

extern SEXP R_svm_pegasos_fit(SEXP intercept, SEXP k, SEXP lambda, SEXP niter, SEXP x, SEXP y);
extern SEXP R_svm_pegasos_pred(SEXP x_new, SEXP w, SEXP intercept);
extern SEXP R_svm_recode_response(SEXP response, SEXP validate_);

static const R_CallMethodDef CallEntries[] = {
  {"R_svm_pegasos_fit", (DL_FUNC) &R_svm_pegasos_fit, 6},
  {"R_svm_pegasos_pred", (DL_FUNC) &R_svm_pegasos_pred, 3},
  {"R_svm_recode_response", (DL_FUNC) &R_svm_recode_response, 2},
  {NULL, NULL, 0}
};

void R_init_ssvm(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}

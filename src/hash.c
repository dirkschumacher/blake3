#include "myrustlib/api.h"
#include <R.h>
#include <Rinternals.h>

SEXP hash(SEXP x) {
  const R_len_t n = length(x);
  SEXP result = PROTECT(allocVector(RAWSXP, 32));
  blake3_hash(RAW(x), n, (uint8_t*)RAW(result));
  UNPROTECT(1);
  return result;
}
// # nocov start
static const R_CallMethodDef callMethods[]  = {
  {"hash", (DL_FUNC) &hash, 1},
  {NULL, NULL, 0}
};

void R_init_miscset(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, callMethods, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
// # nocov end

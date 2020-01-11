#include "myrustlib/api.h"
#include <R.h>
#include <Rinternals.h>

SEXP hash(SEXP x) {
  const R_len_t n = length(x);
  const int OUT_LEN = 32;
  SEXP result = PROTECT(allocVector(RAWSXP, OUT_LEN));
  blake3_hash(RAW(x), n, (uint8_t*)RAW(result));
  UNPROTECT(1);
  return result;
}

static const R_CallMethodDef callMethods[]  = {
  {"hash", (DL_FUNC) &hash, 1},
  {NULL, NULL, 0}
};

void R_init_miscset(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, callMethods, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}

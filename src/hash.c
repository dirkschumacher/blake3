#include "myrustlib/api.h"
#include <R.h>
#include <Rinternals.h>

SEXP hash(SEXP x) {
  const R_len_t n = length(x);
  const int OUT_LEN = 32;
  SEXP result = PROTECT(allocVector(RAWSXP, OUT_LEN));
  uint8_t hash[OUT_LEN];
  blake3_hash(RAW(x), n, hash);
  for (R_len_t i = 0; i < OUT_LEN; i++) {
    RAW(result)[i] = (Rbyte)hash[i];
  }
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

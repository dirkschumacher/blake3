#include "myrustlib/api.h"
#include <R.h>
#include <Rinternals.h>

static const size_t OUT_LEN = 32;
static const size_t KEY_LEN = 32;

SEXP hash(SEXP x) {
  const R_len_t n = length(x);
  SEXP result = PROTECT(allocVector(RAWSXP, OUT_LEN));
  blake3_hash(RAW(x), n, (uint8_t*)RAW(result));
  UNPROTECT(1);
  return result;
}

SEXP keyed_hash(SEXP x, SEXP key) {
  const R_len_t n = length(x);
  SEXP result = PROTECT(allocVector(RAWSXP, KEY_LEN));
  blake3_keyed_hash(RAW(x), n, RAW(key), (uint8_t*)RAW(result));
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

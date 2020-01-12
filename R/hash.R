#' Hash a raw vector using BLAKE3
#' @param x a raw vector
#' @param key either NULL or a 32 byte long raw vector
#' @export
blake3_hash_raw <- function(x, key = NULL) {
  stopifnot(is.raw(x))
  stopifnot(is.null(key) || (is.raw(key) && length(key) == 32L))
  .Call("hash", x, key)
}

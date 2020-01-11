#' Hash a raw vector using BLAKE3
#' @param x a raw vector
#' @export
blake3_hash_raw <- function(x) {
  stopifnot(is.raw(x))
  .Call("hash", x)
}

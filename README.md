
<!-- README.md is generated from README.Rmd. Please edit that file -->

# blake3

<!-- badges: start -->

[![Lifecycle:
experimental](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://www.tidyverse.org/lifecycle/#experimental)
[![Travis build
status](https://travis-ci.org/dirkschumacher/blake3.svg?branch=master)](https://travis-ci.org/dirkschumacher/blake3)
[![Codecov test
coverage](https://codecov.io/gh/dirkschumacher/blake3/branch/master/graph/badge.svg)](https://codecov.io/gh/dirkschumacher/blake3?branch=master)
<!-- badges: end -->

`blake3` is an interface to the
[BLAKE3](https://github.com/BLAKE3-team/BLAKE3) cryptographic hash
function.

To quote blake3’s readme:

> BLAKE3 is a cryptographic hash function that is:
> 
>   - Much faster than MD5, SHA-1, SHA-2, SHA-3, and BLAKE2.
>   - Secure, unlike MD5 and SHA-1. And secure against length extension,
>     unlike SHA-2.
>   - Highly parallelizable across any number of threads and SIMD lanes,
>     because it’s a Merkle \> tree on the inside.
>   - Capable of verified streaming and incremental updates, again
>     because it’s a Merkle tree.
>   - A PRF, MAC, KDF, and XOF, as well as a regular hash.
>   - One algorithm with no variants, which is fast on x86-64 and also
>     on smaller architectures.

> *BLAKE3 is not a password hashing algorithm, because it’s designed to
> be fast, whereas password hashing should not be fast. If you hash
> passwords to store the hashes or if you derive keys from passwords, we
> recommend Argon2.*

If you want to store passwords in R, please also take a look at
[sodium::password\_store](https://download.libsodium.org/doc/password_hashing/default_phf).

## Installation

``` r
remotes::install_github("dirkschumacher/blake3")
```

Also make sure to have a very recent rust compiler. The best way to
install the rust toolchain is to use [rustup](https://rustup.rs/).

## API

It is still a very early version of the package. The api currently just
has one function to hash `RAW` vectors with an optional 32 byte `RAW`
key parameter.

## Example

``` r
library(blake3)

input <- "This is a string"
hash <- blake3_hash_raw(charToRaw(input))
(sodium::bin2hex(hash))
#> [1] "718b749f12a61257438b2ea6643555fd995001c9d9ff84764f93f82610a780f2"
```

``` r
# you can also hash arbitrary R objects by serializing it first
input <- serialize(LETTERS, NULL, version = 2)
hash <- blake3_hash_raw(input)
(sodium::bin2hex(hash))
#> [1] "7b2fe4e871bf4dfca892e9b46ae237f55103235e635d994f351e4553aced2bee"
```

``` r
# keyed hashes are also supported
key <- blake3_hash_raw(charToRaw("test"))
input <- serialize(LETTERS, NULL, version = 2)
hash <- blake3_hash_raw(input, key)
(sodium::bin2hex(hash))
#> [1] "0021965f7c0ca0233e576670b84d35506129ef4bd94c5c8a07b8bb4bdbfb6ce3"
```

## Benchmark

To get an idea about the speed we hash a random string of 1 million
characters and compare it to the `openssl` implementation of `sha1`,
`sha2` and `md5`.

``` r
library(openssl)
set.seed(42)
input <- charToRaw(paste0(sample(LETTERS, 1e6, replace = TRUE), collapse = ""))
microbenchmark::microbenchmark(
  md5 = md5(input),
  sha1 = sha1(input),
  sha2 = sha2(input),
  blake3 = blake3_hash_raw(input),
  times = 1000
)
#> Unit: microseconds
#>    expr      min       lq      mean   median        uq      max neval
#>     md5 1640.739 1679.727 1866.0004 1736.997 1904.4585 5902.874  1000
#>    sha1 1177.078 1206.927 1429.5398 1255.660 1502.0495 6223.994  1000
#>    sha2 2522.645 2589.403 2929.1884 2723.578 3054.4920 6785.628  1000
#>  blake3  389.721  413.038  575.0413  448.384  611.8085 3698.705  1000
```

## License

MIT

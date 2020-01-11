test_that("hashing works", {
  # checksum generated using b3sum
  result <- blake3_hash_raw(charToRaw("wat\n"))
  expect_equal(
    sodium::bin2hex(result),
    "ba352b2dd4b820c8e81701a064a477b1cd4e872ecb38b1e85da5e5541cecce36"
  )
})

test_that("hashing works", {
  # checksum generated using b3sum
  # echo -n "wat" | b3sum
  result <- blake3_hash_raw(charToRaw("wat"))
  expect_equal(
    sodium::bin2hex(result),
    "daad161f364eb7abd95a6ae159af6186f5a8003ced50d1dd82d21e91115ff36b"
  )
})

test_that("keyed hashing works", {
  # checksum generated using b3sum
  # echo -n "wat" > wat
  # echo -n "test" | b3sum | xxd -r -p | b3sum --keyed wat
  key <- blake3_hash_raw(charToRaw("test"))
  result <- blake3_hash_raw(charToRaw("wat"), key)
  expect_equal(
    sodium::bin2hex(result),
    "324cfa665e232acc5c287839bdb88e924add564cf0866f38042f2deca501adfb"
  )
})

test_that("key can either be NULL or 32 byte raw", {
  expect_error(
    blake3_hash_raw(raw(10), "test")
  )
  expect_error(
    blake3_hash_raw(raw(10), raw(10))
  )
  expect_silent(
    blake3_hash_raw(raw(10), raw(32))
  )
})

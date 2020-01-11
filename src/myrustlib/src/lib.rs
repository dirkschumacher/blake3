extern crate blake3;

#[no_mangle]
pub extern fn blake3_hash(data: *const u8, data_length: usize, out: *mut u8) ->() {
  let slice_data = unsafe { std::slice::from_raw_parts(data, data_length) };
  let hash = blake3::hash(slice_data);
  let result = hash.as_bytes();
  let slice_out = unsafe { std::slice::from_raw_parts_mut(out, 32) };
  for (i, v) in result.iter().enumerate() {
    slice_out[i] = v.clone();
  }
}

extern crate blake3;
use blake3::Hash;
use std::convert::TryInto;

#[no_mangle]
pub extern fn blake3_hash(data: *const u8, data_length: usize, out: *mut u8) ->() {
  let slice_data = unsafe { std::slice::from_raw_parts(data, data_length) };
  let hash = blake3::hash(slice_data);
  let pointer_out = unsafe { std::slice::from_raw_parts_mut(out, 32) };
  fill_out_pointer(hash, pointer_out)
}

#[no_mangle]
pub extern fn blake3_keyed_hash(data: *const u8, data_length: usize,
                                key: *const u8, out: *mut u8) ->() {
  let raw_data = unsafe { std::slice::from_raw_parts(data, data_length) };
  let raw_key = unsafe { std::slice::from_raw_parts(key, 32) };
  let hash = blake3::keyed_hash(to_fixed_size_array(raw_key), raw_data);
  let pointer_out = unsafe { std::slice::from_raw_parts_mut(out, 32) };
  fill_out_pointer(hash, pointer_out)
}

fn fill_out_pointer(hash: Hash, out: &mut [u8]) {
  for (i, v) in hash.as_bytes().iter().enumerate() {
    out[i] = v.clone();
  }
}

fn to_fixed_size_array(slice: &[u8]) -> &[u8; 32] {
  slice.try_into().expect("expect 32 bytes")
}

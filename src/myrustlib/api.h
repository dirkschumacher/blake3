#pragma once
#include <stdint.h>
#include <stdlib.h>

void blake3_hash(const uint8_t* data, size_t data_length, uint8_t* out);

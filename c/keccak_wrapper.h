#ifndef KECCAK_WRAPPER
#define KECCAK_WRAPPER

#include <stdint.h>

void keccak_wrapper(const uint8_t *in, const int in_bitlen, uint8_t *out, const int out_bitlen);

#endif  // KECCAK_WRAPPER


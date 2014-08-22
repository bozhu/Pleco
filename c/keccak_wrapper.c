#include <stdint.h>

#include "keccak/KeccakSponge.h"


void keccak_wrapper(const uint8_t *in, const int in_bitlen, uint8_t *out, const int out_bitlen) {
    Keccak_SpongeInstance sponge;
    Keccak_SpongeInitialize(&sponge, 1024, 576);

    uint64_t num_bytes = in_bitlen / 8;
    uint8_t num_last_bits = in_bitlen % 8;

    if (num_bytes > 0) {
        Keccak_SpongeAbsorb(&sponge, (unsigned char*)in, num_bytes);
    }
    if (num_last_bits > 0) {
        uint8_t last_byte = (1 << num_last_bits) | in[num_bytes];
        Keccak_SpongeAbsorbLastFewBits(&sponge, last_byte);
    }

    num_bytes = out_bitlen / 8;
    num_last_bits = out_bitlen % 8;
    if (out_bitlen % 8 == 0) {
        Keccak_SpongeSqueeze(&sponge, out, num_bytes);
    } else {
        Keccak_SpongeSqueeze(&sponge, out, num_bytes + 1);
        uint8_t last_byte_mask = (1 << num_last_bits) - 1;
        out[num_bytes] &= last_byte_mask;
    }
}

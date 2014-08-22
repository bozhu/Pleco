#include <stdint.h>
#include <stdio.h>

#include "KeccakSponge.h"

static void keccak_wrapper(const uint8_t *in, const int in_bitlen, uint8_t *out, const int out_bitlen) {
    Keccak_SpongeInstance sponge;
    Keccak_SpongeInitialize(&sponge, 1024, 576);
    // Keccak_SpongeInitialize(&sponge, 1344, 256);

    uint64_t num_bytes = in_bitlen / 8;
    uint8_t num_last_bits = in_bitlen % 8;

    if (num_bytes > 0) {
        Keccak_SpongeAbsorb(&sponge, (unsigned char*)in, num_bytes);
    }
    if (num_last_bits > 0) {
        uint8_t last_byte = (1 << num_last_bits) | in[num_bytes];
        if (Keccak_SpongeAbsorbLastFewBits(&sponge, last_byte))
            printf("Failed\n");
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

int main() {
    uint8_t in[] = {
        0xab, 0x06
    };
    uint8_t out[160] = {0};

    keccak_wrapper(in, 11, out, 1024);

    for (int i = 0; i < 160; i++) {
        printf("%02x", out[i]);
    }
    printf("\n");

    return 0;
}

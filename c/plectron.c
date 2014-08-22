#include <stdint.h>
#include <string.h>

#include "pleco.h"
#include "keccak_wrapper.h"

int plectron(
        uint8_t *out, uint64_t out_bitlen,
        const uint8_t *salt,
        const uint8_t *password, uint16_t password_bitlen,
        unsigned int t_cost, unsigned int m_cost) {

    uint8_t t[OUT_BYTES] = {0};

    int error_code = pleco(
            t,
            salt,
            (const uint8_t *)password, password_bitlen,
            t_cost, m_cost
    );
    if (0 != error_code)
        return error_code;

    keccak_wrapper(t, MOD_SIZE, out, out_bitlen);

    return 0;
}

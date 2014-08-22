#ifndef PLECTRON_H 
#define PLECTRON_H

#include <stdint.h>

int plectron(
        uint8_t *out, uint64_t out_bitlen,
        const uint8_t *salt,
        const uint8_t *password, uint16_t password_bitlen,
        unsigned int t_cost, unsigned int m_cost);

#endif  // PLECTRON_H 

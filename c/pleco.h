#ifndef PLECO_H 
#define PLECO_H


int pleco(
        uint8_t *out, 
        const uint8_t *salt,
        const uint8_t *password, uint16_t password_bitlen,
        unsigned int t_cost, unsigned int m_cost);

#include "rabin/rabin.h"

#endif  // PLECO_H 

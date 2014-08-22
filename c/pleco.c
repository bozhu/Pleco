#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "rabin/rabin.h"
#include "keccak_wrapper.h"
#include "pleco.h"

static void debug_print(const uint8_t *mem, const int len) {
    for (int i = 0; i < len; i++) {
        printf("%02x", mem[i]);
    }
    printf("\n");
}


static void add_one(uint8_t *arr) {
    while (1) {
        if (*arr == 0xFF) {
            *arr = 0;
            arr++;
        } else {
            (*arr)++;
            return;
        }
    }
}

// int enable_debug = 1;

static void H(const uint8_t *in, const int in_bitlen, uint8_t *out) {
    uint8_t temp[BYTE_LEN] = {0};

    /*
    if (enable_debug) {
        if (in_bitlen % 8) {
            debug_print(in, in_bitlen / 8 + 1);
        } else {
            debug_print(in, in_bitlen / 8);
        }
    }
    */

    keccak_wrapper(in, in_bitlen, temp, MOD_SIZE - 1);
    add_one(temp);
    // debug_print(temp, BYTE_LEN);
    RABIN_FUN(temp, out);
    // debug_print(out, BYTE_LEN);
}

static uint64_t str2uint(const uint8_t *str) {
    // uint64_t res = 0;  // 64 bits should be enough
    uint64_t *ptr = (uint64_t *)str;
    // uint64_t i;

    /*
    for (i = 0; i < 8; i++) {
        res += (((uint64_t)str[i]) << (8 * i));
    }
    if (res != *ptr) {
        printf("Error %llx %llx\n", res, *ptr);
    }

    return res;
    */
    return *ptr;
}

int pleco(
        uint8_t *tag, 
        const uint8_t *salt,
        const uint8_t *pass, uint16_t pass_bitlen,
        unsigned int tcost, unsigned int mcost)
{
    if (tcost < 1 || mcost < 1)
        return 1;
    if (pass_bitlen % 8 != 0)
        return 2;

    /*
    int N_BYTES = MOD_SIZE / 8;
    if (MOD_SIZE % 8)
        N_BYTES++;  // ceiling
    if (OUT_BYTES != N_BYTES)
        printf("Error!\n");
    */
    int L = 8 * OUT_BYTES - MOD_SIZE;

    // ctr || salt || len(pass) || pass
    // ctr || BYTE_LEN || BYTE_LEN 
    uint8_t state[128 / 8 + BYTE_LEN + BYTE_LEN] = {0};

    // padding
    memcpy(state + 16, salt, 16);
    *(state + 32) = pass_bitlen % 256;
    *(state + 33) = pass_bitlen / 256;
    memcpy(state + 34, pass, pass_bitlen / 8);
    // debug_print(state, (128 + 128 + 16 + 1024) / 8); 

    // uint8_t v[mcost][BYTE_LEN];
    uint8_t *vv = (uint8_t*) malloc(mcost * BYTE_LEN);
#define V(idx) (vv + (BYTE_LEN * (idx)))

    // 64-bit instead of 128-bit, should be good for now
    uint64_t *ctr = (uint64_t *)state;
    uint8_t *x = state + 16;

    H(state, 128 + 128 + 16 + 1024, x);
    // memset(x + BYTE_LEN, 0, BYTE_LEN);
    // return 0;

    for (int i = 0; i < tcost; i++) {
        for (int j = 0; j < mcost; j++) {
            memcpy(V(j), x, BYTE_LEN);
            (*ctr)++;
            H(state, 128 + MOD_SIZE, x);
        }
        // debug_print(x, BYTE_LEN); 
        for (int j = 0; j < mcost; j++) {
            uint64_t k = str2uint(x) % mcost;
            (*ctr)++;
            memcpy(x + OUT_BYTES, V(k), BYTE_LEN);
            H(state, 128 + MOD_SIZE + L + MOD_SIZE, x);
        }

        (*ctr)++;
        H(state, 128 + MOD_SIZE, x);
    }

#undef V
    free(vv);

    memcpy(tag, x, OUT_BYTES);
    return 0;
}

#ifndef RABIN_H
#define RABIN_H

#if defined RABIN_1024
    #define RABIN_FUN rabin_1024
    #define MOD_SIZE 1024
    #define BYTE_LEN 128  // for internal use only

#elif defined RABIN_2048
    #define RABIN_FUN rabin_2048
    #define MOD_SIZE 2048
    #define BYTE_LEN 256

#elif defined RABIN_3072
    #define RABIN_FUN rabin_3072
    #define MOD_SIZE 3072
    #define BYTE_LEN 384

#elif defined RABIN_1277
    #define RABIN_FUN rabin_mersenne_1277
    #define MOD_SIZE 1277
    #define BYTE_LEN 160

#elif defined RABIN_2137
    #define RABIN_FUN rabin_mersenne_2137
    #define MOD_SIZE 2137
    #define BYTE_LEN 268

#elif defined RABIN_3049
    #define MOD_SIZE 3049
    #define BYTE_LEN 384
    #define RABIN_FUN rabin_mersenne_3049

#else
    #define RABIN_FUN rabin_1024
    #define MOD_SIZE 1024
    #define BYTE_LEN 128

#endif


#if MOD_SIZE % 8 == 0
    #define OUT_BYTES ((MOD_SIZE) / 8)
#else
    #define OUT_BYTES ((MOD_SIZE) / 8 + 1)
#endif


void RABIN_FUN(uint8_t *msg, uint8_t *out);


#endif // RABIN_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "crypto_scrypt.h"

int main() {
    const char passwd[] = "pleaseletmein";
    const char salt[] = "SodiumChloride";
    uint8_t buf[64];
    clock_t begin, end;
    double time_spent;
    begin = clock();
    for (int i = 0; i < 1000; i++) {
        crypto_scrypt(
                (uint8_t *)passwd, strlen(passwd),
                (uint8_t *)salt, strlen(salt),
                16384, 8, 1,  // uint64_t N, uint32_t r, uint32_t p,
                buf, 64);
    }
    end = clock();
    time_spent = ((double)(end - begin)) / CLOCKS_PER_SEC;

    for (int i = 0; i < 64; i++)
        printf("%02x", buf[i]);
    printf("\n");

    printf("used time: %f seconds\n", time_spent);

    return 0;
}

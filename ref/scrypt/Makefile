CFLAGS = -Wall -O3 -DHAVE_CONFIG_H

test_scrypt.run: main.c crypto_scrypt-sse.c sha256.c
	gcc $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -rf *.out *.o *.run

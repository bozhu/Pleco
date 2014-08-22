CFLAGS := -Wall -O3
KECCAK_DEPS := KeccakF-1600-opt64.c KeccakSponge.c


test_keccak.run: main.c $(KECCAK_DEPS)
	gcc $(CFLAGS) $^ -o $@


.PHONY: clean
clean:
	rm -rf *.out *.o *.run *.dSYM

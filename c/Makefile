PKHASH := RABIN_1024

ifeq ($(PKHASH), RABIN_1024)
	PKHASH_DEPS := rabin/rabin_1024.c
else ifeq ($(PKHASH), RABIN_2048)
	PKHASH_DEPS := rabin/rabin_2048.c
else ifeq ($(PKHASH), RABIN_3072)
	PKHASH_DEPS := rabin/rabin_3072.c
else ifeq ($(PKHASH), RABIN_1277)
	PKHASH_DEPS := rabin/rabin_1277.c
else ifeq ($(PKHASH), RABIN_2137)
	PKHASH_DEPS := rabin/rabin_2137.c
else ifeq ($(PKHASH), RABIN_3049)
	PKHASH_DEPS := rabin/rabin_3049.c
else
	PKHASH_DEPS := notexist
endif

CFLAGS := -Wall -O3 -D$(PKHASH)
KECCAK_DEPS := keccak_wrapper.c keccak/KeccakF-1600-opt64.c keccak/KeccakSponge.c

all: test_pleco.run test_plectron.run

test_pleco.run: main_pleco.c pleco.c $(PKHASH_DEPS) $(KECCAK_DEPS)
	gcc $(CFLAGS) $^ -o $@

test_plectron.run: main_plectron.c plectron.c pleco.c $(PKHASH_DEPS) $(KECCAK_DEPS)
	gcc $(CFLAGS) $^ -o $@


.PHONY: clean
clean:
	rm -rf *.out *.o *.run *.dSYM

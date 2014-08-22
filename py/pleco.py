#!/usr/bin/env python

from Crypto.Util.number import long_to_bytes, bytes_to_long
from binascii import hexlify, unhexlify

from keccak_wrapper import keccak_fun


def ceil(a, b):
    # http://stackoverflow.com/a/17140347
    return a // b + (a % b != 0)


def long2bytes(number, num_bytes):
    string = long_to_bytes(number, num_bytes)
    assert len(string) == num_bytes
    # reverse the string, since we are using little-endian
    string = string[::-1]
    return string


def bytes2long(string):
    string = string[::-1]
    number = bytes_to_long(string)
    return number


class Pleco:
    """
    Unoptimized reference code for Pleco
    """
    def __init__(self,
                 mod,
                 tcost=1, mcost=1024,
                 verbose=False):
        assert mod > 100
        assert tcost > 0
        assert mcost > 0

        self._mod = mod  # n
        self._mod_size = len(bin(mod)) - 2  # N
        # self._bytelen = self._bitlen / 8

        self._tcost = tcost
        self._mcost = mcost

        self.verbose = verbose

    def _rabin(self, num):
        assert num < self._mod
        return pow(num, 2, self._mod)

    def _H(self, state, num_bits):
        assert num_bits in (
            128 + 128 + 16 + 1024,
            128 + self._mod_size,
            128 + 8 * ceil(self._mod_size, 8) + self._mod_size)
        assert len(state) * 8 - 7 <= num_bits <= len(state) * 8

        state = keccak_fun(state, num_bits, self._mod_size - 1)  # note the - 1
        number = bytes2long(state) + 1  # note the + 1
        number = self._rabin(number)
        state = long2bytes(number, ceil(self._mod_size, 8))
        # print hexlify(state)

        assert len(state) * 8 - 7 <= self._mod_size <= len(state) * 8
        return state

    def digest(self, salt, password):
        assert len(salt) == 128 / 8  # in byte
        assert len(password) <= 128

        v = [None] * self._mcost

        L = 8 * ceil(self._mod_size, 8) - self._mod_size
        assert 0 <= L <= 7
        x = salt \
            + long2bytes(len(password) * 8, 16 / 8) \
            + password.ljust(128, '\x00')
        # print hexlify(x)
        ctr = 0
        x = long2bytes(ctr, 128 / 8) + x
        x = self._H(x, len(x) * 8)
        # return ''

        for i in xrange(self._tcost):
            if self.verbose:
                print 'tcost round', i

            for j in xrange(self._mcost):
                v[j] = x
                ctr += 1
                x = long2bytes(ctr, 128 / 8) + x
                x = self._H(x, 128 + self._mod_size)

            # print hexlify(x)

            for j in xrange(self._mcost):
                k = bytes2long(x) % self._mcost
                ctr += 1
                # 0^L is omitted here since x is a multiple of bytes
                # and thus contains the zero padding already
                x = long2bytes(ctr, 128 / 8) + x + v[k]
                x = self._H(x, 128 + self._mod_size + L + self._mod_size)

            ctr += 1
            x = long2bytes(ctr, 128 / 8) + x
            x = self._H(x, 128 + self._mod_size)

        # print hexlify(x)
        return x

    def hexdigest(self, salt, password):
        return hexlify(self.digest(salt, password))


def main():
    # from example_params import modulus_1024 as modulus
    # from example_params import modulus_2048 as modulus
    # from example_params import modulus_3072 as modulus
    # from example_params import modulus_1277 as modulus
    # from example_params import modulus_2137 as modulus
    from example_params import modulus_3049 as modulus

    my_pleco = Pleco(
        mod=modulus,
        tcost=2,
        mcost=1024,
        verbose=True,
    )

    # from Crypto.Random.random import getrandbits
    # salt = long2bytes(getrandbits(128), 128 / 8)
    hexsalt = '4c880aa553669c3869f62b389c2c3499'
    salt = unhexlify(hexsalt)
    password = 'The quick brown fox jumps over the lazy dog'

    print 'hexsalt', hexlify(salt)
    print 'pass', password
    print 'hexpass', hexlify(password)
    hextag = my_pleco.hexdigest(salt, password)
    print 'hexhash', hextag


if __name__ == '__main__':
    main()

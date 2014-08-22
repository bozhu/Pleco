#!/usr/bin/env python

from binascii import hexlify, unhexlify
from keccak_wrapper import keccak_fun
from pleco import Pleco as _Pleco


class Plectron:
    """
    Unoptimized reference code for Plectron
    """
    def __init__(self,
                 mod,
                 tcost=1, mcost=1024,
                 hsize=256,
                 verbose=False):
        assert mod > 100
        assert tcost > 0
        assert mcost > 0
        assert hsize > 0
        assert hsize % 8 == 0

        self._mod = mod  # n
        self._mod_size = len(bin(mod)) - 2  # N

        self._tcost = tcost
        self._mcost = mcost
        self._hsize = hsize

        self.verbose = verbose

    def digest(self, salt, password):
        my_pleco = _Pleco(
            mod=self._mod,
            tcost=self._tcost,
            mcost=self._mcost,
            verbose=True,
        )
        t = my_pleco.digest(salt, password)
        assert 8 * len(t) - 7 <= self._mod_size <= 8 * len(t)

        # hex_msg = hexlify(t)
        # hashed = self.__kclass.Keccak(
        #     (self._mod_size, hex_msg),
        #     n=self._hsize
        # )

        hashed = keccak_fun(t, self._mod_size, self._hsize)

        return hashed

    def hexdigest(self, salt, password):
        return hexlify(self.digest(salt, password))


def main():
    # from example_params import modulus_1024
    from example_params import modulus_2137 as modulus

    my_plectron = Plectron(
        mod=modulus,
        tcost=2,
        mcost=1024,
        hsize=256,
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
    hextag = my_plectron.hexdigest(salt, password)
    print 'hexhash', hextag


if __name__ == '__main__':
    main()

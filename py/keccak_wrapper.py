from binascii import hexlify, unhexlify
from keccak import Keccak


def ceil(a, b):
    # http://stackoverflow.com/a/17140347
    return a // b + (a % b != 0)


def keccak_fun(msg, nbits_in, nbits_out):
    """
    a wrapper for Keccak's reference code
    using the default values r = 1024, c = 576
    """
    kclass = Keccak()

    assert len(msg) * 8 >= nbits_in > 0
    # the ref code of Keccak doesn't accept
    # output lengths that are not multiples of 8
    nbytes_out = ceil(nbits_out, 8)
    nbits_extra = nbytes_out * 8 - nbits_out
    assert 0 <= nbits_extra <= 7

    if nbits_in % 8:
        # to fix the bug (?) in Keccak's offical python code
        last_byte = ord(msg[-1])
        # last_byte = int('{:08b}'.format(last_byte)[::-1], 2)
        last_byte <<= 8 - (nbits_in % 8)
        msg = msg[:-1] + chr(last_byte)

    hex_msg = hexlify(msg)
    hashed = kclass.Keccak(
        (nbits_in, hex_msg),
        n=nbytes_out * 8
    )
    hashed = unhexlify(hashed)

    # truncate the output
    byte_mask = (1 << (8 - nbits_extra)) - 1
    hashed = hashed[:-1] + chr(ord(hashed[-1]) & byte_mask)
    assert len(hashed) * 8 - 7 <= nbits_out <= len(hashed) * 8

    return hashed

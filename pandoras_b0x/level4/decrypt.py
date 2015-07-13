#!/usr/bin/env python2
# encoding: utf-8

import struct


def crypt(data, pwd):
    res = ''
    for i, c in enumerate(data):
        res += chr((i & 0xff) ^ ord(pwd[i % len(pwd)]) ^ ord(c))
    return res


def get_checksum(data):
    checksum = 0xFFFFFFFF
    for c in data:
        c = ord(c)
        checksum = (checksum ^ c) & 0xFFFFFFFF
        for i in range(8):
            tmp = (-(checksum & 1)) & 0xFFFFFFFF
            checksum = ((tmp & 0xedb88320) ^ (checksum >> 1)) & 0xFFFFFFFF
    return (-checksum - 1) & 0xFFFFFFFF 


def load(fname):
    with open(fname, 'rb') as fp:
        data = fp.read()

    checksum1 = struct.unpack('i', data[:4])[0]
    print(hex(checksum1))
    checksum2 = get_checksum(data[4:])
    print(hex(checksum2))
    dec = crypt(data[4:], 'p4ssw0rd')
    checksum1 = struct.unpack('i', dec[:4])[0]
    print(hex(checksum1))
    checksum2 = get_checksum(dec[4:])
    print(hex(checksum2))
    print(dec[6:])

if __name__ == '__main__':
    import sys
    load(sys.argv[1])

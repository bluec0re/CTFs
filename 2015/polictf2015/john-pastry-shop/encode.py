#!/usr/bin/env python
# encoding: utf-8

import sys

INIT = 0x17
ESCAPE = 0x18
EXIT = 0x19


def encode(indata):

    out = [INIT]
    for i, c in enumerate(indata):
        if c in (INIT, EXIT, ESCAPE):
            out.append(ESCAPE)
            out.append(c)
        else:
            out.append(c)
    out.append(EXIT)
    return bytes(out)


with open(sys.argv[1], 'rb') as fp:
    indata = fp.read()

out = encode(indata)

with open(sys.argv[2], 'wb') as fp:
    fp.write(out)

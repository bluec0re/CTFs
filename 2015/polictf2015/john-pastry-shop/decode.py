#!/usr/bin/env python
# encoding: utf-8

import sys

with open(sys.argv[1], 'rb') as fp:
    indata = fp.read()


INIT = 0x17
ESCAPE = 0x18
EXIT = 0x19


valid = False
escape = False
closed = False


out = []

for i, c in enumerate(indata):
    if c == INIT and not escape:
        valid = True
        print(i, 'init')
    else:
        if c == EXIT and not escape:
            valid = False
            print(i, 'exit')
            break
        else:
            if not escape and c == ESCAPE:
                escape = True
                print(i, 'escape')
            else:
                if escape and not valid:
                    escape = False
                    print(i, 'unescape')
                else:
                    if valid:
                        escape = False
                        out.append(c)


with open(sys.argv[2], 'wb') as fp:
    fp.write(bytes(out))

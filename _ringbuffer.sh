#!/bin/bash

echo -e "gcc -g Example_RingBuffer.c RingBuffer.c -o a.out"
gcc -g Example_RingBuffer.c RingBuffer.c -o a.out

echo -e "./a.out"
./a.out

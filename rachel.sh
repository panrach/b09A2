#!/bin/sh

gcc sample-main.c
./a.out sample.dat
gcc print.c
echo "\nrunning print.c"
./a.out sample.dat
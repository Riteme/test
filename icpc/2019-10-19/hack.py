#!/usr/bin/python

from os import *
from sys import *

def sh(x):
    assert not system(x)

sh('cp sel.cpp /tmp/a.cpp')
sh('cp brute.cpp /tmp/b.cpp')
sh('cp gen.py /tmp')
chdir('/tmp')
sh('g++ a.cpp -O3 -o a.out')
sh('g++ b.cpp -O3 -o b.out')
cnt = 0
while True:
    cnt += 1
    print cnt
    sh('./gen.py %s > data.in' % ' '.join(argv[1:]))
    sh('./a.out < data.in > a.ans')
    sh('./b.out < data.in > b.ans')
    sh('diff a.ans b.ans')

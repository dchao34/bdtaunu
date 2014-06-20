#! /Library/Frameworks/Python.framework/Versions/2.7/bin/python

import random

w = open('new.txt', 'w')
f = open('sigmc_ml_assignment.txt', 'r')
iter_f = iter(f)
header = iter_f.next().strip()
header += '|division\n'
w.write(header)
while True:
    try:
        division = random.randint(1, 10)
        record = iter_f.next().strip()
        record += '|{0}\n'.format(division)
        w.write(record)
    except StopIteration:
        break

f.close()
w.close()

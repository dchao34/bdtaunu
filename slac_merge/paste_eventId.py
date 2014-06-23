#! /Library/Frameworks/Python.framework/Versions/2.7/bin/python

eventId_fname_list = [
    'old_generic_ml_assignment.txt',
    'sp1005r1.txt',
    'sp1005r2.txt',
    'sp1005r3.txt',
    'sp1005r4.txt',
    'sp1005r5.txt',
    'sp1005r6.txt',
    'sp1235r1.txt',
    'sp1235r2.txt',
    'sp1235r3.txt',
    'sp1235r4.txt',
    'sp1235r5.txt',
    'sp1235r6.txt',
    'sp1237r1.txt',
    'sp1237r2.txt',
    'sp1237r3.txt',
    'sp1237r4.txt',
    'sp1237r5.txt',
    'sp1237r6.txt',
    'sp998r1.txt',
    'sp998r2.txt',
    'sp998r3.txt',
    'sp998r4.txt',
    'sp998r5.txt',
    'sp998r6.txt'
]

output_fname = 'generic_ml_assignment.txt'
output_f = open(output_fname, 'w')
output_f.write('eventId|ml_sample\n')
for fname in eventId_fname_list:
    f = open(fname, 'r')
    for line in f:
        output_f.write(line)
    f.close()
output_f.close()

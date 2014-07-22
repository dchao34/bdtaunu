#! /Library/Frameworks/Python.framework/Versions/2.7/bin/python

import random

if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser(
        description='Undersample file.')
    parser.add_argument('file_type', type=str,
                        help='sig, cont, sigVsl, sigVhad, sigVall')
    parser.add_argument('ml_sample', type=str,
                        help='explore, train, validate, or test')
    parser.add_argument('--reduce_by_weight', action='store_true')
    parser.add_argument('--reduction_factor', type=float, default=1.0,
                        help=('Undersample uniformly by this factor.'
                              'e.g. 0.5 to cut in half'))

    args = parser.parse_args()

    input_data_fname = '{0}.{1}'.format(args.file_type, args.ml_sample)
    input_data_f = open(input_data_fname, 'r')
    iter_input_data = iter(input_data_f)

    input_weight_fname = '{0}.{1}.wgt'.format(args.file_type, args.ml_sample)
    input_weight_f = open(input_weight_fname, 'r')
    iter_input_weight = iter(input_weight_f)

    output_data_fname = '{0}.{1}.us'.format(args.file_type, args.ml_sample)
    output_weight_fname = '{0}.{1}.us.wgt'.format(args.file_type,
                                                  args.ml_sample)
    output_data_f = open(output_data_fname, 'w')
    output_weight_f = open(output_weight_fname, 'w')

    while True:
        try:
            input_data_line = iter_input_data.next()
            input_weight_line = iter_input_weight.next()

            reduction_factor = args.reduction_factor
            if args.reduce_by_weight:
                reduction_factor *= float(input_weight_line.strip())

            if random.random() < reduction_factor:
                output_data_f.write(input_data_line)
                output_weight_f.write(input_weight_line)

        except StopIteration:
            break

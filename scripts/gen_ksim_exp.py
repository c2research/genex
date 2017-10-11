#!/usr/bin/python
'''
Example:
    ./gen_ksim_exp.py 10 10 experiment.txt dataset.txt 0.3 -k 1 3 5 7 -m 1 2 3 4 5 6 7 --seed 23 -n 10
'''

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import argparse
import random


def pick_random(count, length, min_length=2, n=10):
    picked = []
    for i in range(n):
        idx = random.randint(0, count - 1)
        start = random.randint(0, length - min_length)
        end = start + random.randint(min_length, length - start)
        picked.append((idx, start, end))

    return picked


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Picks random time series given the '
                                                 'dimension of a dataset.')
    parser.add_argument('count', type=int, help='number of items in the dataset.')
    parser.add_argument('length', type=int, help='length of each item in the dataset.')
    parser.add_argument('exp_path', help='path to the GENEX experiment script')
    parser.add_argument('ds_path', help='path to the dataset used in the experiment')
    parser.add_argument('st', type=float, help='similarity threshold for the experiment')
    parser.add_argument('-k', nargs='+', 
                        help='number of similar time series to look for.'
                             'Multiple values can be specified (separated by space).')
    parser.add_argument('-m', nargs='+',
                        help='m*k = number of similar time series to examine.')
    parser.add_argument('-n', type=int, default=10,
                        help='number of sequences to be picked (default: 10).')
    parser.add_argument('--seed', type=int,
                        help='seed for the random number generator.')
    parser.add_argument('--min-length', type=int, default=2,
                        help='minimum length of each sequence (default: 2).')
    parser.add_argument('--fmt', default='{0} [{1}, {2}]',
                        help='python format for output (default: {0} [{1}, {2}])')

    args = parser.parse_args()

    random.seed(args.seed)

    seq = pick_random(args.count, args.length, args.min_length, args.n)
    for s in seq:
        print(args.fmt.format(s[0], s[1], s[2]))
    print()

    with open(args.exp_path, 'w') as f:
        print('load {}'.format(args.ds_path), file=f)
        print('group 0 {}'.format(args.st), file=f)
        for k in args.k:
            for m in args.m:
                for s in seq:
                    print('testSim {} {} 0 0 {} {} {}'.format(k, int(k)*int(m), s[0], s[1], s[2]), 
                          file=f)
    print('Experiment script is generated at {}'.format(args.exp_path))

#!/usr/bin/python3

import argparse
import os

parser = argparse.ArgumentParser()
parser.add_argument("dir", help="Directory which is scanned for files")
parser.add_argument("-n", "--number", help="Number of entries which can stay", type=int,
        default=5)
args = parser.parse_args()

keep = []
count = args.number

elems = os.listdir(args.dir)
elems.sort(reverse=True)

for e in elems:
    if count == 0:
        break
    keep.append(e)
    count -= count

print(keep)

#!/usr/bin/python3

import argparse
import random
import subprocess


def parse_args():
    parser = argparse.ArgumentParser(description="Skyscraper tester")
    parser.add_argument("filename")
    parser.add_argument("-n", type=int, default=20, help="Number of tests to run")
    parser.add_argument("-s", type=int, default=4, help="Size of puzzle")
    parser.add_argument("-v", "--verbose", action="store_true", help="Verbose output")
    return parser.parse_args()


def generate_puzzle(size):
    square = [[(row + col) % size + 1 for col in range(size)] for row in range(size)]
    random.shuffle(square)

    cols = list(range(size))
    random.shuffle(cols)
    square = [[row[col] for col in cols] for row in square]

    symbols = list(range(1, size + 1))
    random.shuffle(symbols)
    mapping = {old: new for old, new in zip(symbols, range(1, size + 1))}

    square = [[mapping[value] for value in row] for row in square]
    return square


def generate_clues(square):
    size = len(square)
    top, bottom, left, right = [], [], [], []
    for col in range(size):
        column = [square[row][col] for row in range(size)]
        top.append(visible_count(column))
        bottom.append(visible_count(reversed(column)))

    for row in range(size):
        line = square[row]
        left.append(visible_count(line))
        right.append(visible_count(reversed(line)))

    clues = top + bottom + left + right
    return " ".join(map(str, clues))


def visible_count(line):
    tallest = 0
    count = 0

    for value in line:
        if value > tallest:
            tallest = value
            count += 1
    return count


args = parse_args()

print("filename:", args.filename)
print("verbose:", args.verbose)
print("number of tests:", args.n)
print("size of puzzle:", args.s)

if args.n < 4 or args.s > 9:
    print("Invalid arguments")
    exit(1)

if args.s > 20:
    print("Too many iterations")
    exit(1)

for i in range(args.n):
    print(f"Test: {i + 1}", end="")
    if args.verbose:
        print()
    square = generate_puzzle(args.s)
    clues = generate_clues(square)
    if args.verbose:
        print("Clues:", clues)
    p = subprocess.Popen(
        ["./" + args.filename, clues],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    )
    out, err = p.communicate()
    solution = [[int(x) for x in line.split()] for line in out.splitlines()]
    if out == "Error\n":
        print("\033[31mError\033[0m")
        continue
    if generate_clues(solution) == clues:
        print("\033[32mCorrect\033[0m")
    else:
        print("\033[31mIncorrect\033[0m")
    if args.verbose:
        print(out)

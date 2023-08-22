#! /usr/bin/python3

if 0:
    input_ = "teste.txt"
else:
    input_ = "input.txt"

def priority(item):
    pri = ord(item)
    if pri >= ord('A') and pri <= ord('Z'):
        return pri - ord('A') + 27
    return pri - ord('a') + 1

def part1():
    with open(input_, 'r') as f:
        sacks = [x.strip() for x in f.readlines()]
        sacks = [(x[:int(len(x)/2)], x[int(len(x)/2):]) for x in sacks]
        sacks = [(set(x[0]), set(x[1])) for x in sacks]
        sacks = [''.join(x[0].intersection(x[1])) for x in sacks]
        sacks = [priority(x) for x in sacks]
        print(sum(sacks))

def part2():
    with open(input_, 'r') as f:
        sacks = [x.strip() for x in f.readlines()]
        sacks = [(sacks[x*3], sacks[x*3 + 1], sacks[x*3 + 2]) 
                for x in range(int(len(sacks) / 3))]
        sacks = [set(x[0]).intersection(set(x[1])).intersection(set(x[2])) for x in sacks]
        sacks = [''.join(x) for x in sacks]
        sacks = [priority(x) for x in sacks]
        print(sum(sacks))


part1()
part2()

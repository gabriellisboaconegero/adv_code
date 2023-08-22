#%%
import os
dir_path = os.path.dirname(os.path.realpath(__file__))

def toBinary(x, map1):
  if x == map1:
    return 0
  return 1

def toNum(bitArray: list):
  re = 0
  for pos, bit in enumerate(bitArray[::-1]):
    re += (2**pos)*bit
  return re


def main():
  first = 0
  second = 0
  with open(f'{dir_path}/input.txt', 'r') as data:
    data = [line.strip() for line in data.readlines()]
    ids = []
    for line in data:
      row = [toBinary(x, "F") for x in line[:7]]
      column = [toBinary(x, "L") for x in line[7:]]
      id = toNum(row) * 8 + toNum(column)
      ids.append(id)
      if id >= first:
        first = id
  ids.sort()
  for id in range(59, 905):
    if id not in ids:
      second = id
      break
  print(first)
  print(second)

if __name__ == '__main__':
    main()
# %%

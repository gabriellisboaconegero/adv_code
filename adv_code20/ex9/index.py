#%%
import os 
dir_path = os.path.dirname(os.path.realpath(__file__))

def isSumOfAny(preamble, num):
  for x in preamble:
    for y in preamble:
      if x + y  == num and x != y:
        return True
  return False

def invalidNumber(data, preambleLength):
  increment = 0
  for line in data[preambleLength:]:
    preamble = data[increment: preambleLength + increment]

    if not isSumOfAny(preamble, line):
      return line
    
    increment += 1

def main():
  first = 0
  second = 0
  with open(f'{dir_path}/input.txt', 'r') as data:
    data = [int(line.strip()) for line in data.readlines()]

    invalid = invalidNumber(data, 25)
    for pos, num in enumerate(data):
      if num == invalid:
        continue
      count = pos
      sum = 0
      while sum < invalid:
        sum += data[count]
        count += 1
      
      if sum == invalid:
        sumNumbers = data[pos: count]
        sumNumbers.sort()
        second = sumNumbers[0] + sumNumbers[-1]

    first = invalid
  print(first)
  print(second)

if __name__ == '__main__':
    main()
# %%

#%%
import os, datetime
dir_path = os.path.dirname(os.path.realpath(__file__))

def main():
  first = 0
  second = 0
  with open(f'{dir_path}/input.txt', 'r') as data:
    data = [int(line.strip()) for line in data.readlines()]
    data.sort()
    data.insert(0, 0)
    data.append(data[-1] + 3)
    diff = {1: 0, 2: 0, 3: 0}
    for i in range(1, len(data)):
      atual = data[i]
      prev = data[i-1]
      diff[atual - prev] += 1
    first = diff[1] * diff[3]

    def previousIsEndNode(nodeId: int) -> bool:
      return data[nodeId] - data[nodeId - 1] == 3

    def countPaths(begin: int, end: int, deep=0) -> int:
      acc = 0
      if begin == end:
        return 1
      for i in range(end-1, begin-1, -1):
        if (data[end] - data[i]) <= 3:
          print(" "*deep*2,data[end], data[i])
          acc += countPaths(begin, i, deep=deep+1)
      return acc

    acc = 1
    initNode = 0
    print(datetime.datetime.now())
    for i in range(1, len(data)):
      if previousIsEndNode(i):
        print(f"{data[initNode]}({initNode}){'==='*10}{data[i - 1]}({i - 1})")
        acc *= countPaths(initNode, i - 1)
        initNode = i - 1
    print(datetime.datetime.now())
    second = acc

  print(first)
  print(second)

if __name__ == '__main__':
    main()
# %%

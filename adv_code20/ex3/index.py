#%%
import os 
dir_path = os.path.dirname(os.path.realpath(__file__))

first = 0
second = 0

def get_trees(rows, dx, dy):
  posX = posY = count = 0
  max_x = len(rows[0])
  # print(max_x)
  while posY < len(rows):
    row = rows[posY]
    if row[posX] == "#":
      count += 1
    posY += dy
    posX += dx
    if posX >= max_x:
      posX -= max_x
  return count

def main():
  with open(f'{dir_path}/input.txt', 'r') as data:
    rows = [line.strip() for line in data.readlines()]
    second = 1
    first = get_trees(rows, 3, 1)
    for dx, dy in ((1,1), (3,1), (5,1), (7,1), (1,2)):
      second *= get_trees(rows, dx, dy)
  print(first)
  print(second)

if __name__ == '__main__':
    main()
# %%

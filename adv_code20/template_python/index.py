#%%
import os 
dir_path = os.path.dirname(os.path.realpath(__file__))

def main():
  first = 0
  second = 0
  with open(f'{dir_path}/input.txt', 'r') as data:
    data = [line.strip() for line in data.readlines()]
    for line in data:
      pass
  print(first)
  print(second)

if __name__ == '__main__':
    main()
# %%

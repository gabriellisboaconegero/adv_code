#%%
import os 
dir_path = os.path.dirname(os.path.realpath(__file__))

with open(f'{dir_path}/input.txt', 'r') as data:
  data = [line.strip() for line in data.readlines()]
  for (id1, num1) in enumerate(data):
    for (id2, num2) in enumerate(data[id1:]):
      if int(num1) + int(num2) == 2020:
        first = int(num1) * int(num2)
      for num3 in data[id1 + id2:]:
        if int(num1) + int(num2) + int(num3) == 2020:
          second = int(num1) * int(num2) * int(num3)     
print(first)
print(second)
# %%

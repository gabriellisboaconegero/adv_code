#%%
import os
dir_path = os.path.dirname(os.path.realpath(__file__))

def bagRuleParser(bagString:  str):
  bagColor = '-'.join(bagString.split()[:2])
  if "other" in bagString:
    return {
    "color":  bagColor,
    "content": None
  }
  
  contentBags = {"-".join(bag.split()[1:-1]): int(bag.split()[0]) for bag in bagString.split("contain ")[1].split(",")}
  return {
    "color":  bagColor,
    "content": contentBags
  }

def lookForBag(bagList, bagToLook, canContainBagCount=0, canContainBag=[]):
  for bag in bagList:
    if bag["content"] == None:
      continue
    
    if bag["color"] in canContainBag:
      continue

    contentBags = [x for x in bag["content"]]
    if bagToLook not in contentBags:
      continue
    
    print("  " * canContainBagCount + str(bag))
    canContainBag.append(bag["color"])
    lookForBag(bagList, bag["color"], canContainBagCount + 1, canContainBag)
  return len(canContainBag)

def howMany(bagList, bagColor, total=0):
  bag = list(filter(lambda bag: bag["color"] == bagColor, bagList))[0]
  print(bag)

  if bag["content"] == None:
    return 0

  for bagColor in bag["content"]:
    total += bag["content"][bagColor] + bag["content"][bagColor] * howMany(bagList, bagColor)
  return total

def main():
  first = 0
  second = 0
  with open(f'{dir_path}/input.txt', 'r') as data:
    data = list(map(bagRuleParser, [line.strip() for line in data.readlines()]))
    for x in data:
      print(x)
    print("---" * 10)
    first = lookForBag(data, "shiny-gold")
    second = howMany(data, "shiny-gold")
  print(first)
  print(second)

if __name__ == '__main__':
    main()
# %%

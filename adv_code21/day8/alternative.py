unique = {1: 2, 4: 4, 7: 3, 8: 7}
len5 = [2, 3, 5]
len6 = [0, 6, 9]

wireSegMap = {}
digitsMap = {
  0: {"a", "b", "c", "e", "f", "g"},
  1: {"c", "f"},
  2: {"a", "c", "d", "e", "g"},
  3: {"a", "c", "d", "f", "g"},
  4: {"b", "c", "d", "f"},
  5: {"a", "b", "d", "f", "g"},
  6: {"a", "b", "d", "e", "f", "g"},
  7: {"a", "c", "f"},
  8: {"a", "b", "c", "d", "e", "f", "g"},
  9: {"a", "b", "c", "d", "f", "g"},
}

wireMap = {
  "a": {2: 0, 3: 0, 4: 0, 7: 0, 5: 0, 6: 0},
  "b": {2: 0, 3: 0, 4: 0, 7: 0, 5: 0, 6: 0},
  "c": {2: 0, 3: 0, 4: 0, 7: 0, 5: 0, 6: 0},
  "d": {2: 0, 3: 0, 4: 0, 7: 0, 5: 0, 6: 0},
  "e": {2: 0, 3: 0, 4: 0, 7: 0, 5: 0, 6: 0},
  "f": {2: 0, 3: 0, 4: 0, 7: 0, 5: 0, 6: 0},
  "g": {2: 0, 3: 0, 4: 0, 7: 0, 5: 0, 6: 0}
}

for digit in digitsMap:
  for seg in digitsMap[digit]:
    if digit in unique.keys():
      wireMap[seg][unique[digit]] += 1
    elif digit in len5:
      wireMap[seg][5] += 1
    elif digit in len6:
      wireMap[seg][6] += 1


with open("input.txt", "r") as file:
  count = 0
  for line in  file.readlines():
    inputs = line.split(" | ")
    segments = inputs[0].split()
    fourNum = inputs[1].split()
    segmentsMap = {
      "a": {2: 0, 3: 0, 4: 0, 7: 0, 5: 0, 6: 0},
      "b": {2: 0, 3: 0, 4: 0, 7: 0, 5: 0, 6: 0},
      "c": {2: 0, 3: 0, 4: 0, 7: 0, 5: 0, 6: 0},
      "d": {2: 0, 3: 0, 4: 0, 7: 0, 5: 0, 6: 0},
      "e": {2: 0, 3: 0, 4: 0, 7: 0, 5: 0, 6: 0},
      "f": {2: 0, 3: 0, 4: 0, 7: 0, 5: 0, 6: 0},
      "g": {2: 0, 3: 0, 4: 0, 7: 0, 5: 0, 6: 0}
    }
    for seg in segments:
      for let in seg:
        segmentsMap[let][len(seg)] += 1
    for seg in segmentsMap:
      for wire in wireMap:
        if segmentsMap[seg] == wireMap[wire]:
          wireSegMap[seg] = wire
    total = 0
    for num in fourNum:
      mappedNumStr = ""
      for letter in num:
        mappedNumStr += wireSegMap[letter]
      for digit, segs in digitsMap.items():
        if set(mappedNumStr) == segs:
          total = total * 10 + digit
          break
    count += total
  print(count)

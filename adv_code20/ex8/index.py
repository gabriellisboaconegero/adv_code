#%%
import os 
dir_path = os.path.dirname(os.path.realpath(__file__))

def part1(commands):
  pointer = 0
  acc = 0
  cmdList = []
  while pointer <= len(commands):
    if pointer in cmdList:
      break
    cmd = commands[pointer]
    pointerIncrement = 1
    if cmd[0] == "nop":
      pass
    elif cmd[0] == "jmp":
      pointerIncrement = cmd[1]
    else:
      acc += cmd[1]
    cmdList.append(pointer)
    pointer += pointerIncrement
  return acc

def part2(globalCommands):
  def filtro(cmd):
    return cmd[1][0] == "jmp" or cmd[1][0] == "nop"

  commandsToChange = list(filter(filtro, enumerate(globalCommands)))
  
  for cmdToChange in commandsToChange:
    localCommands = [x for x in globalCommands]
    cmd = cmdToChange[1][0]
    if cmd == "jmp":
      localCommands[cmdToChange[0]] = ("nop", cmdToChange[1][1])
    elif cmd == "nop":
      localCommands[cmdToChange[0]] = ("jmp", cmdToChange[1][1])
        
    pointer = 0
    acc = 0
    cmdList = []
    while True:
      if pointer >= len(localCommands):
        return acc
      if pointer in cmdList:
        break
      cmd = localCommands[pointer]
      pointerIncrement = 1
      if cmd[0] == "nop":
        pass
      elif cmd[0] == "jmp":
        pointerIncrement = cmd[1]
      else:
        acc += cmd[1]
      cmdList.append(pointer)
      pointer += pointerIncrement
def main():
  first = 0
  second = 0
  with open(f'{dir_path}/input.txt', 'r') as data:
    commands = [(line.strip().split()[0], int(line.strip().split()[1])) for line in data.readlines()]
    first = part1(commands)
    second = part2(commands)
  print(first)
  print(second)

if __name__ == '__main__':
    main()
# %%

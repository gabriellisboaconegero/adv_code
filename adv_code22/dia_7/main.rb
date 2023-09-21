# frozen_string_literal: true

def part1(lines)
  size = 0
  stack = [0]
  lines[2..].each do |line|
    cmd = line.split
    if cmd[0] != '$'
      # Se nao for dir soma o size
      cmd[0].to_i.zero? || stack[-1] += cmd[0].to_i
    elsif cmd[1] == 'cd'
      if cmd[2] == '..'
        # tira da stack
        child_size = stack.pop
        child_size <= 100_000 && size += child_size
        stack[-1] += child_size
      else
        # coloca na stack novo valor com 0
        stack.push 0
      end
    else
      stack[-1] = 0
    end
  end
  print size
  print "\n"
end

def part2(lines)
  stack = [0]
  dir_sizes = []
  lines[2..].each do |line|
    cmd = line.split
    if cmd[0] != '$'
      # Se nao for dir soma o size
      cmd[0].to_i.zero? || stack[-1] += cmd[0].to_i
    elsif cmd[1] == 'cd'
      if cmd[2] == '..'
        # tira da stack
        child_size = stack.pop
        dir_sizes.push child_size
        stack[-1] += child_size
      else
        # coloca na stack novo valor com 0
        stack.push 0
      end
    else
      stack[-1] = 0
    end
  end

  unused_space = 70_000_000 - stack.sum
  needed = 30_000_000 - unused_space
  v = 0
  stack.reverse.each do |val|
    v += val
    dir_sizes.push v
  end
  print((dir_sizes.sort.drop_while { |num| num < needed })[0])
  print "\n"
end
# file = 'teste.txt'
file = 'input.txt'
lines = IO.readlines(file)
part2 lines

# frozen_string_literal: true

lines = IO.readlines('teste.txt')
# stack = Array.new

size = 0
lines[2..].each do |line|
  cmd = line.split
  if cmd[0] != '$'
    # se for file com tamanho
    if cmd[0].to_i != 0
      stack.last += cmd[0].to_i
    end
  elsif cmd[1] == 'cd'
    if cmd[2] == '..'
      # tira da stack
    else
      # coloca na stack novo valor com 0
      stack.push 0
    end
  end
end

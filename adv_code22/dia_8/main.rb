# frozen_string_literal: true

def visible?(xxx, yyy, trees)
  val = trees[yyy][xxx]
  x = xxx
  y = yyy

  r = (y + 1...trees.length).map { |y_| val > trees[y_][x] }.all?
  r ||= (x + 1...trees.length).map { |x_| val > trees[y][x_] }.all?
  r ||= (0...y).map { |y_| val > trees[y_][x] }.all?
  r ||= (0...x).map { |x_| val > trees[y][x_] }.all?

  r
end

def max(aaa, bbb)
  aaa > bbb ? aaa : bbb
end

def scenic_score(xxx, yyy, trees)
  val = trees[yyy][xxx]
  x = xxx
  y = yyy

  m = 1

  s = 0
  trees[y][x + 1..].each do |v|
    s += 1
    break if val <= v
  end
  m *= s

  s = 0
  trees[y][0...x].reverse.each do |v|
    s += 1
    break if val <= v
  end
  m *= s

  s = 0
  (y + 1...trees.length).each do |y_|
    s += 1
    break if val <= trees[y_][x]
  end
  m *= s

  s = 0
  (y - 1).downto(0).each do |y_|
    s += 1
    break if val <= trees[y_][x]
  end
  m *= s

  m
end

def part1(trees)
  # Arvores ao redor sao sempre visiveis
  visible = trees.length * 2 + 2 * (trees[0].length - 2)
  (1..trees.length - 2).each do |y|
    (1..trees[y].length - 2).each do |x|
      visible?(x, y, trees) && visible += 1
    end
  end

  puts visible
end

def part2(trees)
  # Arvores ao redor sao sempre visiveis
  m = 0
  (1..trees.length - 2).each do |y|
    (1..trees[y].length - 2).each do |x|
      # print "(#{x}, #{y}) #{scenic_score(x, y, trees)}\n"
      m = max(m, scenic_score(x, y, trees))
    end
  end

  puts m
end

file = 'input.txt'
# file = 'teste.txt'
lines = IO.readlines(file)
lines.map! { |l| l.strip.split('').map(&:to_i) }

part2 lines

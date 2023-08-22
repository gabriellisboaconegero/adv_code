#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

size_t part1(FILE *file){
  char buf[128];
  int64_t depth = 0, horizontalPos = 0;
  while((fgets(buf, sizeof buf, file) != NULL)){
    char instruction = *buf;
    long value = strtol(&buf[strlen(buf) - 2], 0, 0);
    switch (instruction)
    {
    case 'f':
      horizontalPos += value;
      break;
    case 'u':
      depth -= value;
      break;
    
    default:
      depth += value;
      break;
    }
  }
  return depth * horizontalPos;
}

size_t part2(FILE *file){
  char buf[128];
  int64_t depth = 0, horizontalPos = 0, aim = 0;
  while((fgets(buf, sizeof buf, file) != NULL)){
    char instruction = *buf;
    int value = strtoul(&buf[strlen(buf) - 2], 0, 0);
    switch (instruction){
    case 'f':
      horizontalPos += value;
      depth += aim * value;
      break;
    case 'u':
      aim -= value;
      break;
    default:
      aim += value;
      break;
    }
  }
  return horizontalPos * depth;
}

int main(int argc, char **argv){
  FILE *file;
  file = fopen(argv[1], "r");

  if(file == NULL){
    printf("File %s cannot be open", argv[1]);
  }

  printf("Part1: %lu\n", part1(file));
  fseek(file, 0, 0);
  printf("Part2: %lu\n", part2(file));

  fclose(file);
  return 0;
}
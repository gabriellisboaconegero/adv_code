#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#if 1
#define INPUT 1
#else
#define INPUT 2
#endif

#define DAYS_PASSED 256

int64_t daysTable[DAYS_PASSED];

int64_t getChildren(int64_t days, int64_t day){
  if (day >= DAYS_PASSED){
    return 0;
  }
  int64_t firstZeroCount = DAYS_PASSED - day - days;
  if (firstZeroCount <= 0){
    return 0;
  }
  int64_t zeroCount = ((firstZeroCount - 1) / 7) + 1;
  int64_t childrenCount = zeroCount;
  for (int i = 0; i < zeroCount; i++){
    if (daysTable[day + days + 7 * i + 1]){
      childrenCount += daysTable[day + days + 7 * i + 1];
    }else{
      int64_t childrens = getChildren(8, day + days + 7 * i + 1);
      daysTable[day + days + 7 * i + 1] = childrens;
      childrenCount += childrens;
    }
  }
  return childrenCount;
}

size_t part1(FILE *file){
  char *buf = NULL;
  size_t size = 0;
  size_t lineSize = getline(&buf, &size, file);
  int initialStateSize = lineSize / 2 + 1;
  int64_t initialState[initialStateSize];
  int64_t count = initialStateSize;
  int c = 0;
  while (c < initialStateSize){
    count += getChildren(strtol(buf, &buf, 0), 0);
    buf++;
    c++;
  }
  return count;
}


size_t part2(FILE *file){
  char *buf = NULL;
  size_t size = 0;
  size_t lineSize = 0;
  while((lineSize = getline(&buf, &size, file)) != -1){
  }
  return 0;
}

int main(int argc, char **argv){
  FILE *file;
  file = fopen(argv[INPUT], "r");

  if(file == NULL){
    printf("File %s cannot be open", argv[INPUT]);
  }
  printf("Part1: %lu\n", part1(file));
  fseek(file, 0, 0);
  printf("Part2: %lu\n", part2(file));

  fclose(file);
  return 0;
}
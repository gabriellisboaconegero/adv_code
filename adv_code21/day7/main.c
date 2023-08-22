#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>

#if 1
#define INPUT 1
#else
#define INPUT 2
#endif

int64_t fuelChangeUp = 0;
int64_t fuelChangeDown = 0;
int64_t top = 8;
int64_t down = 0;

void dupChange(int64_t value, int64_t up, int64_t down){
  printf("[%" PRId64 "] (%" PRId64 ", %"PRId64 ")\n", value, up, down);
}

void getNumChange(int64_t value, int64_t d1, int64_t d2){
  if ( value > top ){
    fuelChangeUp += -d1;
    fuelChangeDown += d2;
    // dupChange(value, -d1, d2);
  }else if (value < top){
    fuelChangeUp += d2;
    fuelChangeDown += -d1;
    // dupChange(value, d2, -d1);
  }else{
    fuelChangeUp += d2;
    fuelChangeDown += d2;
    // dupChange(value, d2, d2);
  }
}

void getFuelDiff(int64_t *list, size_t size, int64_t (*func1)(int64_t), int64_t (*func2)(int64_t)){
  fuelChangeUp = 0;
  fuelChangeDown = 0;
  // printf("Line %"PRId64"\n", top);
  for (int i = 0; i < size; i++) {
    getNumChange(list[i], (*func1)(list[i]), (*func2)(list[i]));
  }
  // printf("ChangeInUp: %" PRId64 " ChangeInDown: %"PRId64 "\n", fuelChangeUp, fuelChangeDown);
}

int updateLine(){
  if (fuelChangeUp < 0){
    top++;
  }else if (fuelChangeDown < 0){
    top--;
  }else{
    return 1;
  }
  return 0;
}

int64_t dist1(int64_t x){
  return 1;
}

size_t part1(FILE *file){
  char *buf = NULL;
  size_t size = 0;
  size_t lineSize = getline(&buf, &size, file);
  char *line = buf;

  size_t listSize = lineSize / 2;
  int64_t list[listSize];

  int c = 0;
  while(*line){
    char *endp;
    size_t value = strtol(line, &endp, 0);
    getNumChange(value, 1, 1);
    list[c] = value;
    line = endp + 1;
    c++;
  }
  listSize = c;
  // printf("ChangeInUp: %" PRId64 " ChangeInDown: %"PRId64 "\n", fuelChangeUp, fuelChangeDown);

  int findBestLine = 0;
  for (; !findBestLine; findBestLine = updateLine()){
    getFuelDiff(list, listSize, dist1, dist1);
  }

  size_t count = 0;
  for (int64_t i = 0; i < listSize; i++){
    count += abs(list[i] - top);
  }
  return count;
}

size_t fuelNedded(size_t from, size_t to){
  size_t fuel = 0;
  for (int i = 1; i <= abs(from - to); i++){
    fuel += i;
  }
  return fuel;
}

int64_t dist2(int64_t value){
  return abs(value - top);
}
int64_t dist3(int64_t value){
  return abs(value - top) + 1;
}

size_t part2(FILE *file){
  char *buf = NULL;
  size_t size = 0;
  size_t lineSize = getline(&buf, &size, file);
  char *line = buf;

  size_t listSize = lineSize / 2;
  int64_t list[listSize];

  int c = 0;
  while(*line){
    char *endp;
    size_t value = strtol(line, &endp, 0);
    getNumChange(value, abs(value - top), abs(value - top) + 1);
    list[c] = value;
    line = endp + 1;
    c++;
  }
  listSize = c;
  printf("ChangeInUp: %" PRId64 " ChangeInDown: %"PRId64 "\n", fuelChangeUp, fuelChangeDown);

  int findBestLine = 0;
  for (; !findBestLine; findBestLine = updateLine()){
    getFuelDiff(list, listSize, dist2, dist3);
  }

  size_t count = 0;
  for (int64_t i = 0; i < listSize; i++){
    count += fuelNedded(list[i], top);
  }
  return count;
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
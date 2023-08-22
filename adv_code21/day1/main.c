#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

size_t part1(FILE *file){
  char buf[128];
  size_t count = 0;
  size_t previus  = 0;
  size_t current = 0;
  while((fgets(buf, sizeof buf, file)) != NULL){
    current = strtoul(buf, 0, 0);
    if (previus > 0){
      if (current > previus){
        count++;
      }
    }
    previus = current;
  }
  return count;
}

size_t part2(FILE *file){
  char buf[128];
  int64_t window1 = 0;
  int64_t window2 = 0;
  int64_t window3 = 0;
  int64_t window4 = 0;
  int count1 = 0;
  int count2 = -1;
  int count3 = -2;
  int count4 = -3;

  int increased = 0;
  while((fgets(buf, sizeof buf, file) != NULL)){
    size_t measure = strtoul(buf, 0, 0);
    if (count1 == 3){
      window1 -= measure;
      if (window1 < 0){
        increased++;
      }
      window1 = 0;
      count1 = -1;
    }else if (count1 == 0){
      window1 = measure;
    }
    // window2
    if (count2 == 3){
      window2 -= measure;
      if (window2 < 0){
        increased++;
      }
      window2 = 0;
      count2 = -1;
    }else if (count2 == 0){
      window2 = measure;
    }
    // window3
    if (count3 == 3){
      window3 -= measure;
      if (window3 < 0){
        increased++;
      }
      window3 = 0;
      count3 = -1;
    }else if (count3 == 0){
      window3 = measure;
    }
    // window4
    if (count4 == 3){
      window4 -= measure;
      if (window4 < 0){
        increased++;
      }
      window4 = 0;
      count4 = -1;
    }else if (count4 == 0){
      window4 = measure;
    }

    count1++;
    count2++;
    count3++;
    count4++;
  }
  return increased;
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
}
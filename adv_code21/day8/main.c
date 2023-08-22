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

int tableSize[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

size_t part1(FILE *file){
  char *buf = NULL;
  size_t size = 0;
  size_t lineSize = 0;
  char *line;
  char *pttStr;
  char *out;
  char *uniquePattern;

  int count = 0;
  while((lineSize = getline(&buf, &size, file)) != -1){
    line = buf;
    pttStr = strchr(line, '|');
    pttStr += 2;
    while (pttStr){
      uniquePattern = strsep(&pttStr, " ");
      int size = strlen(uniquePattern);
      if (!pttStr){
        size--;
      }
      if (size == tableSize[1] || size == tableSize[4] || size == tableSize[7] || size == tableSize[8]){
        count++;
      }
    }
  }

  return count;
}

struct Map{
  char inputLetter;
  char outLetter;
};

int arraySum(int *array, int size,int *last1){
  int res = 0;
  for (int i = 0; i < size; i++){
    res += array[i];
    if (array[i]){
      *last1 = i;
    }
  }
  return res;
}

int inMap(struct Map *map, int letter){
  for (int i = 0; i < 10; i++){
    if (map[i].outLetter == letter + 'a'){
      return 1;
    }
  }
  return 0;
}

void mapping(int mapPatterPesos[7], int mapPesos[7], struct Map *map){
  int possibilityTable[7][7] = {0};
  int lastEqual = 0;
  for (int i = 0; i < 7; i++){
    if (map[i].inputLetter != '\0') continue;
    for (int j = 0; j < 7; j++){
        if (mapPatterPesos[i] == mapPesos[j] && !inMap(map, j)){
          possibilityTable[i][j] = 1;
        }
    }
    if (arraySum(possibilityTable[i], 7, &lastEqual) == 1){
      map[i].inputLetter = 'a' + i;
      map[i].outLetter = 'a' + lastEqual;
    }
  }
}

int letterCount(int letter){
  int res = 0;
  for (int i = 0; i < 7; i++){
    res += (letter >> i) & 1;
  }
  return res;
}

void changePesos(int mapPatterPesos[7], int mapPesos[7], int patterns[10], int cmpPatterns[10], int len, int op(int, int)){
  for (int j = 0; j < 10; j++){
    if (letterCount(cmpPatterns[j]) == len){
      for (int i = 0; i < 7; i++){
        mapPesos[i] = op(mapPesos[i] , (cmpPatterns[j] >> i) & 1);
      }
    }
    if (letterCount(patterns[j]) == len){
      for (int i = 0; i < 7; i++){
        mapPatterPesos[i] = op(mapPatterPesos[i], (patterns[j] >> i) & 1);
      }
    }
  }
}

int plus(int x, int y){
  return x + y;
}
int minus(int x, int y){
  return x - y;
}
size_t part2(FILE *file){
  int cmpPatterns[10] = {
    (int)strtoul("1110111", 0, 2), 
    (int)strtoul("0100100", 0, 2),
    (int)strtoul("1011101", 0, 2),
    (int)strtoul("1101101", 0, 2),
    (int)strtoul("0101110", 0, 2),
    (int)strtoul("1101011", 0, 2),
    (int)strtoul("1111011", 0, 2),
    (int)strtoul("0100101", 0, 2),
    (int)strtoul("1111111", 0, 2),
    (int)strtoul("1101111", 0, 2),
  };
  
  char *buf = NULL;
  size_t size = 0;
  size_t lineSize = 0;
  char *line;

  //                 a b c d e f g
  int mapPesos[7] = {8,6,8,7,4,9,7};
  int mapPatterPesos[7];
  struct Map map[7];
  memset(map, 0, 7*sizeof(struct Map));
  int patterns[10];

  char *out;
  char *uniquePattern;
  
  int count = 0;
  while((lineSize = getline(&buf, &size, file)) != -1){
    memset(patterns, 0, 10*sizeof(int));
    memset(mapPatterPesos, 0, 7*sizeof(int));
    memset(map, 0, 7*sizeof(struct Map));

    line = buf;
    out = strchr(line, '|');
    int c = 0;
    while (line < out){
      uniquePattern = strsep(&line, " ");
      int size = strlen(uniquePattern);
      uint pattern = 0;
      for (int i = 0; i < size;  i++){
        pattern |= (1 << uniquePattern[i] - 'a');
        mapPatterPesos[ uniquePattern[i] - 'a']++;
      }
      patterns[c] = pattern;
      c++;
    }
    mapping(mapPatterPesos,mapPesos, map);
    changePesos(mapPatterPesos, mapPesos, patterns, cmpPatterns, 2, minus);
    mapping(mapPatterPesos, mapPesos, map);
    changePesos(mapPatterPesos, mapPesos, patterns, cmpPatterns, 2, plus);
    mapping(mapPatterPesos, mapPesos, map);
    changePesos(mapPatterPesos, mapPesos, patterns, cmpPatterns, 4, minus);
    mapping(mapPatterPesos, mapPesos, map);
    changePesos(mapPatterPesos, mapPesos, patterns, cmpPatterns, 4, plus);

    // for (int j = 0; j < 7; j++){
    //   printf("%c -> %c\n", map[j].inputLetter,  map[j].outLetter);
    // }
    out += 2;
    int num = 0;
    while (out){
      uniquePattern = strsep(&out, " ");
      int size = strlen(uniquePattern);
      if (!out){
        size--;
      }
      int binPattern = 0;
      for (int i = 0; i < size; i++){
        binPattern |= (1 << (map[uniquePattern[i] - 'a'].outLetter - 'a'));
      }
      for (int i = 0; i < 10; i++){
        if (binPattern == cmpPatterns[i]){
          num = num * 10 + i;
        }
      }
    }
    printf("-> %d\n", num);
    count += num;
  }
  return count;
}

int main(int argc, char **argv){
  FILE *file;
  file = fopen(argv[INPUT], "r");

  if(file == NULL){
    printf("File %s cannot be open", argv[INPUT]);
  }
  // printf("Part1: %lu\n", part1(file));
  // fseek(file, 0, 0);
  printf("Part2: %lu\n", part2(file));

  fclose(file);
  return 0;
}
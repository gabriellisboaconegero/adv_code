#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

uint64_t bintodec(uint64_t *binList, size_t n){
  uint64_t sum = 0;
  for (int i = 0; i < n; i++){
    sum += binList[i]*(int)pow((double)2, (double)n - 1 - i);
  }
  return sum;
}

uint64_t strbintodec(char *binList, size_t n){
  uint64_t sum = 0;
  for (int i = 0; i < n; i++){
    sum += (*binList - '0')*(int)pow((double)2, (double)n - 1 - i);
    binList++;
  }
  return sum;
}

size_t part1(FILE *file){
  char buf[128];
  size_t bitsSize = strlen(fgets(buf, sizeof buf, file)) - 1;
  if (buf == NULL){
    return 1;
  }
  uint64_t gammaRates[bitsSize];
  for (int i = 0; i < bitsSize; i++){
    gammaRates[i] = 0;
  }
  size_t count = 0;
  fseek(file, 0, 0);
  while((fgets(buf, sizeof buf, file) != NULL)){
    for (int i = 0; i < bitsSize; i++){
      gammaRates[i] += buf[i] - '0';
    }
    count++;
  }
  for (int i = 0; i < bitsSize; i++){
    if (gammaRates[i] < count / 2){
      gammaRates[i] = 0l;
    }else{
      gammaRates[i] = 1l;
    }
  }
  uint64_t gammarate = bintodec(gammaRates, bitsSize);

  return gammarate * ((~gammarate << 64 - bitsSize)>> 64 - bitsSize);
}

uint64_t findGammaRate(uint64_t *binList, int n, int from, int binSize){
  // if (n == 2 || n == 1){
  //   return 1;
  // }
  uint64_t gammaRate = 0;
  for (int i = 0; i < n; i++){
    gammaRate += (binList[i] >> (binSize - from)) & 1;
  }
  if (gammaRate >= n - gammaRate){
    return 1;
  }
  return 0;
}
uint64_t findGammaRateNot(uint64_t *binList, int n, int from, int binSize){
  // if (n == 2 || n == 1){
  //   return 0;
  // }
  uint64_t gammaRate = 0;
  for (int i = 0; i < n; i++){
    gammaRate += (binList[i] >> (binSize - from)) & 1;
  }
  if (gammaRate >= n - gammaRate){
    return 0;
  }
  return 1;
}

uint64_t oxygenGenRate(uint64_t size, uint64_t bitsSize, uint64_t binList[size]){
  for (int i = 0; i < bitsSize; i++){
    if (size <= 1){
      return binList[0];
    }
    uint64_t temp[size];
    for (int j = 0; j < size; j++){
      temp[j] = 0;
    }
    int c = 0;
    uint64_t gammaRate  = findGammaRate(binList, size, i + 1, bitsSize);
    for (int j = 0; j < size; j++){
      if (((binList[j] >> (bitsSize - i - 1)) & 1) == gammaRate){
        temp[c] = binList[j];
        c++;
      }
    }
    for (int i = 0; i < size; i++){
      if (i <= c){
        binList[i] = temp[i];
      }else{
        binList[i] = 0;
      }
    }
    size = c;
  }
  return binList[0];
}

uint64_t CO2ScrubberRate(uint64_t size, uint64_t bitsSize, uint64_t binList[size]){
  for (int i = 0; i < bitsSize; i++){
    if (size <= 1){
      return binList[0];
    }
    uint64_t temp[size];
    for (int j = 0; j < size; j++){
      temp[j] = 0;
    }
    int c = 0;
    uint64_t gammaRate  = findGammaRateNot(binList, size, i + 1, bitsSize);
    for (int j = 0; j < size; j++){
      if (((binList[j] >> (bitsSize - i - 1)) & 1) == gammaRate){
        temp[c] = binList[j];
        c++;
      }
    }
    for (int i = 0; i < size; i++){
      if (i <= c){
        binList[i] = temp[i];
      }else{
        binList[i] = 0;
      }
    }
    size = c;
  }
  return binList[0];
}


size_t part2(FILE *file){
  char buf[128];
  size_t bitsSize = strlen(fgets(buf, sizeof buf, file)) - 1;
  if (buf == NULL){
    return 1;
  }
  uint64_t gammaRate = 0;
  size_t count = 0;
  fseek(file, 0, 0);
  uint64_t binList1[1000];
  uint64_t binList2[1000];
  while((fgets(buf, sizeof buf, file) != NULL)){
    binList1[count] = strbintodec(buf, bitsSize);
    binList2[count] = strbintodec(buf, bitsSize);
    count++;
  }
  return CO2ScrubberRate(1000, bitsSize, binList2) * oxygenGenRate(1000, bitsSize, binList1);
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
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t aplyMask(char mask[37], uint64_t value){
  for (int i = 0; i < 36; i++){
    if (mask[i] == '0'){
      value &= ~(1ULL << (36 - i - 1));
    }else if(mask[i] == '1'){
      value |= (1ULL << (36 - i - 1));
    }
  }
  return value;
}

int main(int argc, char **argv){
  FILE *file;
  file = fopen(argv[1], "r");

  if (file ==  NULL){
    printf("Arquivo %s não existe\n", argv[1]);
  }

  char buf[128];
  char mask[37] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
  char value[32];
  uint64_t mem[100000];
  for (int64_t i = 0; i < sizeof(mem) / sizeof(uint64_t); i++){
    mem[i] = 0;
  }
  while (fgets(buf, sizeof buf, file) != NULL){
    if (strncmp(buf, "mask", 4) == 0){
      strncpy(mask, &buf[7], 36);
    }else{
      char temp[10];
      char *rest = strtok(buf, " ");
      strcpy(temp, &rest[4]);
      temp[strlen(temp) - 1] = '\0';
      rest = strtok(NULL, " ");
      rest = strtok(NULL, " ");
      strcpy(value, rest);
      value[strlen(value) - 1] = '\0';
      uint16_t temMem = strtoul(temp, 0, 0);
      mem[temMem] = aplyMask(mask, (uint64_t)strtol(value, 0, 0));
    }
  }
  uint64_t count = 0;
  for (int64_t i = 0; i < 100000; i++){
    if (mem[i] > 0){
      count += mem[i];
    }
  }

  printf("Solução 1: %llu\n", count);

  fclose(file);
  return 0; 
}
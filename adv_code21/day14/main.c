#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>

#if 1
#define INPUT 1
#define POLYMERER_CAP 19457
#define INITIAL_POLYMER_LEN 20
#define INSERTION_CAP 100
#else
#define INPUT 2
#define POLYMERER_CAP 3073
#define INITIAL_POLYMER_LEN 2
#define INSERTION_CAP 16
#endif

#define STEPS 40

char polymer[POLYMERER_CAP] = {0};
int polymer_sz = 0;

char insertion_map[INSERTION_CAP][3];
int inserion_sz = 0;

uint64_t elements_count[26]= {0};

uint64_t total_len(int steps){
  uint64_t count = INITIAL_POLYMER_LEN;
  for (int i = 0; i < steps; i++){
      count += count - 1; 
  }
  return count;
}

void  dump_polymer(){
  for (int i = 0; i < polymer_sz;  i++){
    printf("%c", polymer[i]);
  }
  printf("\n");
}
void dump_insertion(){
  for (int i = 0; i < inserion_sz; i++){
    printf("%c%c -> %c\n", insertion_map[i][0], insertion_map[i][1], insertion_map[i][2]);
  }
  printf("\n");
}
void dump_elements_count(){
  for (int i = 0; i < 26; i++){
    printf("%c -> %llu\n", i + 'A', elements_count[i]);
  }
  printf("\n");
}

char search_pair(char c1, char c2){
  for (int i = 0; i < inserion_sz; i++){
    if (c1 == insertion_map[i][0] && c2 == insertion_map[i][1]){
      return insertion_map[i][2];
    }
  }
  return '\0';
}

void next_insertions(){
  for (int i = 0; i < polymer_sz; i+=2){
    int j = i + 1;
    char to_insert = search_pair(polymer[i], polymer[j]);
    if (to_insert){
      memmove(polymer + j + 1, polymer + j, polymer_sz - i - 1);
      polymer[j] = to_insert;
      polymer_sz++;
    }
  }
}

uint64_t max(){
  uint64_t res = 0;
  for (int i = 0;  i < 26; i++){
    if (elements_count[i] > res){
      res = elements_count[i];
    }
  }
  return res;
}

uint64_t min(){
  uint64_t res = UINT64_MAX;
  for (int i = 0;  i < 26; i++){
    if (elements_count[i] < res && elements_count[i] != 0){
      res = elements_count[i];
    }
  }
  return res;
}

uint64_t part1(FILE *file){
  char *buf =  NULL;
  size_t size = 0;
  size_t line_sz = 0;
  char *line;

  line_sz = getline(&buf, &size, file);
  line = buf;
  for( ; *line != '\n' && *line; line++){
    polymer[polymer_sz] = *line;
    polymer_sz++;
  }
  getline(&buf, &size, file);
  while ((line_sz = getline(&buf, &size, file)) != EOF){
    line = buf;
    insertion_map[inserion_sz][0] = *line;
    line++;
    insertion_map[inserion_sz][1] = *line;
    line += 5;
    insertion_map[inserion_sz][2] = *line;
    inserion_sz++;
  }
  for (int i = 0; i < STEPS;  i++){
    next_insertions();
  }
  for (int i = 0; i < polymer_sz; i++){
    elements_count[polymer[i] - 'A']++;
  }
  return max() - min();
}

typedef struct Hash {
  char key[2];
  uint64_t count;
} Hash;

Hash count_table[INSERTION_CAP] = {0};

int table_index(char *value){
  for (int i = 0; i < inserion_sz; i++){
    if (count_table[i].key[0] == value[0] && count_table[i].key[1] == value[1]){
      return i;
    }
  }
  return -1;
}

void next(){
  uint64_t new_counts[INSERTION_CAP] = {0};
  for (int i = 0; i < inserion_sz; i++){
    char element[2] = {insertion_map[i][0], insertion_map[i][2]};
    int index = table_index(element);
    
    new_counts[index] += count_table[i].count;
    element[0] = insertion_map[i][2];
    element[1] = insertion_map[i][1];
    index = table_index(element);
    new_counts[index] += count_table[i].count;
  }
  for (int i = 0; i < inserion_sz; i++){
    count_table[i].count = new_counts[i];
  }
}

void dup_count_table(){
  for (int i = 0; i < inserion_sz; i++){
    printf("%c%c -> %llu\n", count_table[i].key[0], count_table[i].key[1], count_table[i].count);
  }
  printf("\n");
}

uint64_t part2(FILE *file){
  char *buf =  NULL;
  size_t size = 0;
  size_t line_sz = 0;
  char *line;

  line_sz = getline(&buf, &size, file);
  line = buf;
  for( ; *line != '\n' && *line; line++){
    polymer[polymer_sz] = *line;
    polymer_sz++;
  }
  getline(&buf, &size, file);
  while ((line_sz = getline(&buf, &size, file)) != EOF){
    line = buf;
    insertion_map[inserion_sz][0] = *line;
    count_table[inserion_sz].key[0] = *line;
    line++;
    insertion_map[inserion_sz][1] = *line;
    count_table[inserion_sz].key[1] = *line;
    line += 5;
    insertion_map[inserion_sz][2] = *line;
    inserion_sz++;
  }
  for (int i = 0; i < polymer_sz - 1; i++){
    char element[2] = {polymer[i], polymer[i+1]};
    count_table[table_index(element)].count += 1;
  }
  for (int i = 0; i < STEPS; i++){
    next();
  }
  dup_count_table();
  for (int i = 0; i < inserion_sz; i++){
    elements_count[count_table[i].key[0] - 'A'] += count_table[i].count;
    elements_count[count_table[i].key[1] - 'A'] += count_table[i].count;
  }
  dump_elements_count();
  for (int i = 0; i < 26; i++){
    elements_count[i] = (uint64_t)ceill((long double)elements_count[i] / 2);
  }
  dump_elements_count();

  return max() - min();
}

int main(int argc, char **argv){
  system("clear");
  FILE *file;
  file = fopen(argv[INPUT], "r");

  if(file == NULL){
    printf("File %s cannot be open", argv[INPUT]);
  }
  // printf("Part1: %lu\n", part1(file));
  // fseek(file, 0, 0);
  printf("Part2: %llu\n", part2(file));

  fclose(file);
  return 0;
}
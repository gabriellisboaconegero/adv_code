#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>

#if 1
#define INPUT 1
#define GRID_COLUMNS 100
#define GRID_ROWS 100
#else
#define INPUT 2
#define GRID_COLUMNS 10
#define GRID_ROWS 5
#endif

int heightMap[GRID_ROWS][GRID_COLUMNS] = {0};
int low_points[GRID_ROWS][GRID_COLUMNS] = {0};

int adjLower(int i, int j){
  for (int l = -1; l <= 1; l++){
    for (int k = -1; k <= 1; k++){
      if (i + l < 0 || j + k < 0 || i + l >= GRID_ROWS || j + k >= GRID_COLUMNS ){
        continue;
      }
      if (heightMap[i + l][j + k] < heightMap[i][j]){
        return 1;
      }
    }
  }
  return 0;
}

size_t part1(FILE *file){
  int value;
  int rows_ct = 0;
  int columns_ct = 0;
  while((value = fgetc(file)) != EOF){
    if (value == '\n'){
      rows_ct++;
      columns_ct = 0;
    }else{
      heightMap[rows_ct][columns_ct] = value - '0';
      columns_ct++;
    }
  }
  rows_ct++;

  for (int i = 0; i < rows_ct; i++){
    for (int j = 0; j < columns_ct; j++){
      if (!adjLower(i, j)){
        low_points[i][j] = 1;
      }
    }
  }

  int count = 0;
  for (int i = 0; i < rows_ct; i++){
    for (int j = 0; j < columns_ct; j++){
      count += heightMap[i][j] * low_points[i][j] + low_points[i][j];
    }
  }
  return count;
}
int searched_points[GRID_ROWS][GRID_COLUMNS] = {0};
int map[GRID_ROWS][GRID_COLUMNS] = {0};

void show_lava_map(){
  system("clear");
  for (int i = 0; i < GRID_ROWS; i++){
    for (int j = 0; j < GRID_COLUMNS; j++){
      int v = map[i][j];
      if (!v){
        putchar('#');
      }else {
        putchar(map[i][j]);
      }
    }
    putchar('\n');
  }
  // usleep(100);
}

int basin(int i, int j){
  if (!(i < 0 || j < 0 || i >= GRID_ROWS || j >= GRID_COLUMNS)){
    if (heightMap[i][j] == 9){
      map[i][j] = '#';
    }else if (!map[i][j]){
      map[i][j] = '.';
    }
    // show_lava_map();
  }
  if (heightMap[i][j] == 9 || i < 0 || j < 0 || i >= GRID_ROWS || j >= GRID_COLUMNS || searched_points[i][j]){
    return 0;
  }
  int count = 1;
  searched_points[i][j] = 1;
  int v = 0;

  v = basin(i - 1, j);
  if (v){
    count += v;
    searched_points[i - 1][j] = 1;
  }
  v = basin(i + 1, j);
  if (v){
    count += v;
    searched_points[i + 1][j] = 1;
  }
  v = basin(i, j - 1);
  if (v){
    count += v;
    searched_points[i][j - 1] = 1;
  }
  v = basin(i, j + 1);
  if (v){
    count += v;
    searched_points[i][j + 1] = 1;
  }

  return count;
}

size_t part2(){
  int count = 1;
  int max3[3] = {0};
  for (int i = 0; i < GRID_ROWS; i++){
    for (int j = 0; j < GRID_COLUMNS; j++){
      if (low_points[i][j]){
        map[i][j] = '^';
        int v = basin(i, j);
        for (int l = 0; l < 3; l++){
          if (v > max3[l]){
            for (int h = l + 1; h < 3; h++){
              max3[h] = max3[ h - 1];
            }
            max3[l] = v;
            break;
          }
        }
      }
    }
  }
  for (int h = 0; h < 3; h++){
    count *= max3[h];
  }
  show_lava_map();
  return count;
}

int main(int argc, char **argv){
  system("clear");
  FILE *file;
  file = fopen(argv[INPUT], "r");

  if(file == NULL){
    printf("File %s cannot be open", argv[INPUT]);
  }
  printf("Part1: %lu\n", part1(file));
  printf("Part2: %lu\n", part2());

  fclose(file);
  return 0;
}
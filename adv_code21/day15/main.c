#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>

#if 0
#define INPUT 1
#define GRID_SZ 100
#else
#define INPUT 2
#define GRID_SZ 10
#endif

int grid[GRID_SZ][GRID_SZ] = {0};
int cols = 0;
int rows = 0;

int weight_grid[GRID_SZ][GRID_SZ] = {0};

void dump_grid(int grid[GRID_SZ][GRID_SZ], char *sep){
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      printf("%d%s", grid[i][j], sep);
    }
    printf("\n");
  }
}

int weight(int i, int j){
  int count = 0;
  for (int y = -1; y <= 1; y++){
    for (int x = -1; x <= 1; x++){
      if (!(i + y < 0 || i + y >= rows || j + x < 0 || j + x >= cols )){
        count += grid[i + y][j + x];
      }
    }
  }
  return count; //grid[i][j] + (int) sqrt(pow(rows - i, 2) + pow(cols - j, 2));
}

int part1(FILE *file){
  char *buf = NULL;
  char *line = NULL;
  size_t size = 0;
  size_t line_sz = 0;
  while ((line_sz = getline(&buf, &size, file)) != EOF){
    line = buf;
    cols = 0;
    while (*line && *line != '\n'){
      grid[rows][cols] = *line - '0';
      cols++;
      line++;
    }
    rows++;
  }
  dump_grid(grid, "");
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      weight_grid[i][j] = weight(i, j);
    }
  }
  dump_grid(weight_grid, " ");
  return 0;
}

int part2(FILE *file){
  return 0;
}

int main(int argc, char **argv){
  FILE *file;
  file = fopen(argv[INPUT], "r");

  if(file == NULL){
    printf("File %s cannot be open", argv[INPUT]);
  }
  printf("Part1: %d\n", part1(file));
  fseek(file, 0, 0);
  printf("Part2: %d\n", part2(file));

  fclose(file);
  return 0;
}
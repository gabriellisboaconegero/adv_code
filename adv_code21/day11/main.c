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
#define GRID_SZ 10

int grid[GRID_SZ][GRID_SZ];
int flashed[GRID_SZ][GRID_SZ] = {0};
int count = 0;
int flash_cnt = 0;

void flash(int x, int y){
  flash_cnt++;
  for (int i = -1; i <= 1; i++){
    for (int j = -1; j <= 1; j++){
      int nx = x + i;
      int ny = y + j;
      if (!(nx < 0 || ny < 0 || nx >= GRID_SZ || ny >= GRID_SZ || (i == 0 && j == 0) || flashed[nx][ny])){
        grid[nx][ny] += 1;
        if (grid[nx][ny] >= 10){
          grid[nx][ny] = 0;
          flashed[nx][ny] = 1;
          count++;
          flash(nx, ny);
        }
      }
    }
  }
}

void  showGrid(){
  for (int i = 0; i < GRID_SZ; i++){
    for (int j = 0; j < GRID_SZ; j++){
      printf("%d ", grid[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

size_t part1(FILE *file){
  char cha;
  int cols = 0;
  int rows = 0;
  while((cha = fgetc(file)) != EOF){
    if (cha != '\n'){
      grid[rows][cols] = cha - '0';
      cols++;
    }else{
      cols = 0;
      rows++;
    }
  }
  rows++;

  int step = 0;
  while (flash_cnt < GRID_SZ * GRID_SZ){
    memset(flashed, 0, GRID_SZ * GRID_SZ * sizeof(int));
    flash_cnt = 0;
    for (int i = 0; i < rows; i++){
      for (int j = 0; j < cols; j++){
        if (!flashed[i][j]){
          grid[i][j] += 1;
          if (grid[i][j] >= 10){
            grid[i][j] = 0;
            flashed[i][j] = 1;
            count++;
            flash(i, j);
          }
        }
      }
    }
    step++;
  }
  return step;
}

int main(int argc, char **argv){
  system("clear");
  FILE *file;
  file = fopen(argv[INPUT], "r");

  if(file == NULL){
    printf("File %s cannot be open", argv[INPUT]);
  }
  printf("Part1: %lu\n", part1(file));

  fclose(file);
  return 0;
}
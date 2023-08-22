#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#if 1
#define INPUT 1
#define GRID_SZ 1000
#else
#define INPUT 2
#define GRID_SZ 10
#endif

struct Point{
  size_t x;
  size_t y;
};

union Grid {
  int g[GRID_SZ][GRID_SZ];
  int l[GRID_SZ * GRID_SZ];
} grid;


void dupPoint(struct Point *p){
  printf("[%lu,%lu]\n", p->x, p->y);
}

void showGrid(){
  for (int i = 0; i < GRID_SZ; i++){
    for (int j = 0; j < GRID_SZ; j++){
      if (grid.g[j][i]){
        printf("%d", grid.g[j][i]);
      }else{
        printf(".");
      }
    }
    printf("\n");
  }
  printf("\n");
}

void getDiagonalLines(struct Point *p1, struct Point *p2){
  int iccX = p1->x > p2->x ? -1 : 1;
  int iccY = p1->y > p2->y ? -1 : 1;
  int x = 0, y = 0;
  while(p1->x + x != p2->x + iccX && p1->y + y != p2->y + iccY){
    grid.g[p1->x + x][p1->y + y]++;
    x += iccX;
    y += iccY;
  }
  
}

void getHorizontalVerticalLines(struct Point *p1, struct Point *p2, int part1){
  if (p1->x != p2->x && p1->y != p2->y) {
    if(!part1) getDiagonalLines(p1, p2);
    return;
  }
  int diffX = p1->x - p2->x;
  int diffY = p1->y - p2->y;
  int icc = 1;
  if (diffX){
    if (diffX > 0){
      icc *= -1;
    }
    for (int x = p1->x; x != p2->x + icc; x += icc){
      grid.g[x][p1->y]++;
    }
  }else{
    if (diffY > 0){
      icc *= -1;
    }
    for (int y = p1->y; y != p2->y + icc; y += icc){
      grid.g[p1->x][y]++;
    }
  }
}

size_t part1(FILE *file){
  char *buf = NULL;
  size_t size = 0;
  size_t lineSize = 0;
  memset(&grid.l, 0, GRID_SZ * GRID_SZ * sizeof(int));

  struct Point p1;
  struct Point p2;
  int c = 0;
  while((lineSize = getline(&buf, &size, file)) != -1){
    char *line =  buf;
    p1.x = strtoul(line, &line, 0);
    line++;
    p1.y = strtoul(line, &line, 0);
    line+=4;
    p2.x = strtoul(line, &line, 0);
    line++;
    p2.y = strtoul(line, &line, 0);
    // showGrid();
    getHorizontalVerticalLines(&p1, &p2, 1);
    c++;
  }
  int count = 0;
  for (int i = 0; i < GRID_SZ; i++){
    for (int j = 0; j < GRID_SZ; j++){
      if (grid.g[j][i] >= 2){
        count++;
      }
    }
  }
  return count;
}


size_t part2(FILE *file){
  char *buf = NULL;
  size_t size = 0;
  size_t lineSize = 0;
  memset(&grid.l, 0, GRID_SZ * GRID_SZ * sizeof(int));

  struct Point p1;
  struct Point p2;
  int c = 0;
  while((lineSize = getline(&buf, &size, file)) != -1){
    char *line =  buf;
    p1.x = strtoul(line, &line, 0);
    line++;
    p1.y = strtoul(line, &line, 0);
    line+=4;
    p2.x = strtoul(line, &line, 0);
    line++;
    p2.y = strtoul(line, &line, 0);
    // showGrid();
    getHorizontalVerticalLines(&p1, &p2, 0);
    // showGrid();
    c++;
  }
  int count = 0;
  for (int i = 0; i < GRID_SZ; i++){
    for (int j = 0; j < GRID_SZ; j++){
      if (grid.g[j][i] >= 2){
        count++;
      }
    }
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
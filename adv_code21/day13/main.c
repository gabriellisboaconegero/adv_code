#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>

#if 1
#define INPUT 1
#define POITS_CNT 836
#define MAX_FOLDS 12
#define MAX_NUMBER 1400
#else
#define INPUT 2
#define POITS_CNT 18
#define MAX_FOLDS 2
#define MAX_NUMBER 15
#endif

int points[POITS_CNT][2] = {0};
int points_sz = 0;

int counted[MAX_NUMBER][MAX_NUMBER] = {0};

typedef struct Fold {
  int axis;
  int value;
} Fold;

void foldPaper(Fold *fold){
  for (int i = 0; i < points_sz; i++){
    int value_on_axis = points[i][fold->axis];
    points[i][fold->axis] = -(abs(-value_on_axis + fold->value) - fold->value);
  }
}

int isPoint(int y, int x){
  for  (int i = 0; i < points_sz;  i++){
    if (points[i][0] == x && points[i][1] == y){
      return 1;
    }
  }
  return 0;
}

void dumpPaper(){
  for (int i = 0; i < 6; i++){
    for (int j = 0; j < 39; j++){
      if (isPoint(i, j)){
        printf("@");
      }else{
        printf(" ");
      }
    }
    printf("\n");
  }
  printf("\n");
}

int coutPoits(){
  memset(counted, 0, MAX_NUMBER * MAX_NUMBER * sizeof(int));
  int count = 0;
  for (int i = 0; i < points_sz; i++){
    int x = points[i][0];
    int y = points[i][1];
    if (!counted[x][y]){
      counted[x][y] = 1;
      count++;
    }
  }
  return count;
}

Fold *folds[MAX_FOLDS];
int folds_sz = 0;

size_t part1(FILE *file){
  char *buf = NULL;
  size_t size = 0;
  size_t line_sz = 0;
  char *line = NULL;

  while ((line_sz = getline(&buf, &size, file)) != -1){
    line = buf;
    if (line_sz > 1 && line_sz < 13){
      char *x = strsep(&line, ",");
      char *y = strsep(&line, "\n");
      points[points_sz][0] = strtol(x, NULL, 10);
      points[points_sz][1] = strtol(y, NULL, 10);
      points_sz++;
    }else if (line_sz >= 13){
      line += 11;
      char *axis = strsep(&line, "=");
      char *value = strsep(&line, "\n");
      Fold *fold = malloc(sizeof(Fold));
      fold->axis = *axis - 'x';
      fold->value = strtol(value, NULL, 10);
      folds[folds_sz] = fold;
      folds_sz++;
    }
  }
  printf("Poits number: %d\n", coutPoits());
  for (int i = 0; i < folds_sz; i++){
    foldPaper(folds[i]);
  }
  dumpPaper();
  return coutPoits();
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
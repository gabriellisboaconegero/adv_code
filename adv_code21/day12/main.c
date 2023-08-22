#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>

#if 1
#define INPUT 1
#define MAX_CONECTIONS 25
#else
#define INPUT 2
#define MAX_CONECTIONS 7
#endif

typedef struct Cave {
  int conections[MAX_CONECTIONS];
  int con_sz;
  char *id;
  int big;
  int visited;
} Cave;

Cave *start;
Cave *end;
Cave *caves[MAX_CONECTIONS];
int caves_sz = 0;
int count = 0;

int caveId(char *id){
  for (int i = 0; i < caves_sz; i++){
    if (strcmp(caves[i]->id, id) == 0){
      return i;
    }
  }
  return -1;
}

Cave *newCave(char *id, int *index){
  *index = caves_sz;
  Cave *cave = malloc(sizeof(Cave));
  cave->id = malloc(strlen(id));
  if (*id >= 'A' && *id <= 'Z'){
    cave->big = 1;
  }
  strcpy(cave->id, id);
  caves_sz++;
  return cave;
}

void nextCave(Cave *cave){
  if (!cave->big){
    cave->visited = 1;
  }
  if (cave == end){
    count++;
    return;
  }
  for (int i = 0; i < cave->con_sz; i++){
    Cave *nCave = caves[cave->conections[i]];
    if (nCave != start && !nCave->visited){
      nextCave(nCave);
      nCave->visited = 0;
    }
  }
}

int canVisit(Cave *cave){
  int smallWithTwoVisit = 0;
  for (int i = 0; i < caves_sz;  i++){
    if (caves[i]->visited == 2){
      smallWithTwoVisit = 1;
      break;
    }
  }
  return cave != start && !(smallWithTwoVisit && cave->visited);
}

void nextCave2(Cave *cave){
  if (!cave->big){
    cave->visited += 1;
  }
  if (cave == end){
    count++;
    return;
  }
  for (int i = 0; i < cave->con_sz; i++){
    Cave *nCave = caves[cave->conections[i]];
    if (canVisit(nCave)){
      nextCave2(nCave);
      if (nCave->visited >= 1){
        nCave->visited -= 1;
      }
    }
  }
}

size_t part1(FILE *file){
  memset(caves, 0, MAX_CONECTIONS * sizeof(Cave));
  char *line = NULL;
  size_t size = 0;
  int line_sz = 0;

  char *left = NULL;
  char *right = NULL;

  while((line_sz = getline(&line, &size, file)) != -1){
    right = line;
    left = strsep(&right, "-");
    line = right;
    right = strsep(&line, "\n");

    int leftId = caveId(left);
    int rightId = caveId(right);
    if (leftId == -1){
      caves[caves_sz] = newCave(left, &leftId);
    }
    if (rightId == -1){
      caves[caves_sz] = newCave(right, &rightId);
    }
    caves[leftId]->conections[caves[leftId]->con_sz] = rightId;
    caves[rightId]->conections[caves[rightId]->con_sz] = leftId;
    caves[leftId]->con_sz++;
    caves[rightId]->con_sz++;
    if (strcmp(left, "start") == 0){
      start = caves[leftId];
    }else if(strcmp(right, "start") == 0){
      start = caves[rightId];
    }
    if (strcmp(left, "end") == 0){
      end = caves[leftId];
    }else if(strcmp(right, "end") == 0){
      end = caves[rightId];
    }
  }
  nextCave(start);
  return count;
}

size_t part2(FILE *file){
  memset(caves, 0, MAX_CONECTIONS * sizeof(Cave));
  char *line = NULL;
  size_t size = 0;
  int line_sz = 0;

  char *left = NULL;
  char *right = NULL;

  while((line_sz = getline(&line, &size, file)) != -1){
    right = line;
    left = strsep(&right, "-");
    line = right;
    right = strsep(&line, "\n");

    int leftId = caveId(left);
    int rightId = caveId(right);
    if (leftId == -1){
      caves[caves_sz] = newCave(left, &leftId);
    }
    if (rightId == -1){
      caves[caves_sz] = newCave(right, &rightId);
    }
    caves[leftId]->conections[caves[leftId]->con_sz] = rightId;
    caves[rightId]->conections[caves[rightId]->con_sz] = leftId;
    caves[leftId]->con_sz++;
    caves[rightId]->con_sz++;
    if (strcmp(left, "start") == 0){
      start = caves[leftId];
    }else if(strcmp(right, "start") == 0){
      start = caves[rightId];
    }
    if (strcmp(left, "end") == 0){
      end = caves[leftId];
    }else if(strcmp(right, "end") == 0){
      end = caves[rightId];
    }
  }
  nextCave2(start);
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
  // fseek(file, 0, 0);
  // printf("Part2: %lu\n", part2(file));

  fclose(file);
  return 0;
}
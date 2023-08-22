#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#if 1
#define INPUT 1
#define BOARD_GAMES 100
#else
#define INPUT 2
#define BOARD_GAMES 3
#endif

int boards[BOARD_GAMES][25];
int boards_marked[BOARD_GAMES][25];
int winners[BOARD_GAMES];

void getBoards(FILE *file){
  char *buf = NULL;
  ssize_t size = 0;

  int i = -1;
  int j = 0;
  ssize_t lineSize;
  ssize_t previusLineSize = 0;

  while ((lineSize = getline(&buf, &size, file)) != -1){
    char *line = buf;
    if (lineSize != 1){
      while (*line != '\n' && *line != '\0'){
        char *endptr;
        boards[i][j] = (int)strtol(line, &endptr, 0);
        boards_marked[i][j] = 0;
        line = endptr;
        j++;
      }
    }else if(previusLineSize == 1){
      j = 0;
      i++;
    }
    previusLineSize = lineSize;
  }
}

void boardsMarkNum(int num){
  for (int i = 0; i < BOARD_GAMES; i++){
    for (int j = 0; j < 25; j++){
      if (boards[i][j] == num){
        boards_marked[i][j] = 1;
      }
    }
  }
}

void getWinners(int *lastWinner){
  for (int i = 0; i < BOARD_GAMES; i++){
    if (winners[i]){
      continue;
    }
    int sumRow = 0;
    int sumCols[5];
    memset(sumCols, 0, 5*sizeof(int));
    for (int j = 0; j < 25; j++){
      if (j % 5 == 0){
        if (sumRow == 5){
          winners[i] = 1;
          *lastWinner = i;
          break;
        }
        sumRow = 0;
      }
      if (boards_marked[i][j]){
        sumRow++;
        sumCols[j % 5]++;
      }
    }
    for (int x = 0; x < 5; x++){
      if (sumCols[x] == 5){
        winners[i] = 1;
        *lastWinner = i;
        break;
      }
    }
  }
}

size_t part1(FILE *file){
  memset(winners, 0, BOARD_GAMES * sizeof(int));
  memset(boards, 0, BOARD_GAMES * sizeof(int));
  memset(boards_marked, 0, BOARD_GAMES * sizeof(int));

  char *line = NULL;
  size_t size = 0;
  size_t lineSize = getline(&line, &size, file);

  int drawNumbers[lineSize];
  char *drawNum = NULL;
  int drawNumSize = 0;

  while ((drawNum = strsep(&line, ",")) != 0){
    drawNumbers[drawNumSize] = strtol(drawNum, 0, 0);
    drawNumSize++;
  }

  getBoards(file);

  int winner = -1;
  int i = 0;
  while (i < drawNumSize){
    boardsMarkNum(drawNumbers[i]);
    getWinners(&winner);
    if (winner != -1){
      break;
    }
    i++;
  }

  int lastDrawNumber = drawNumbers[i];
  int sumUnchked = 0;
  for (int i = 0; i < 25; i++){
    if (!boards_marked[winner][i]){
      sumUnchked += boards[winner][i];
    }
  }

  return sumUnchked * lastDrawNumber;
}


size_t part2(FILE *file){
  memset(winners, 0, BOARD_GAMES * sizeof(int));
  memset(boards, 0, BOARD_GAMES * sizeof(int));
  memset(boards_marked, 0, BOARD_GAMES * sizeof(int));

  char *line = NULL;
  size_t size = 0;
  size_t lineSize = getline(&line, &size, file);

  int drawNumbers[lineSize];
  char *drawNum = NULL;
  int drawNumSize = 0;

  while ((drawNum = strsep(&line, ",")) != 0){
    drawNumbers[drawNumSize] = strtol(drawNum, 0, 0);
    drawNumSize++;
  }

  getBoards(file);

  int i = 0;
  int lastWinner = 0;
  while (i < drawNumSize){
    boardsMarkNum(drawNumbers[i]);
    getWinners(&lastWinner);
    int winnerCount = 0;
    for (int j = 0; j < BOARD_GAMES; j++){
      if (winners[j]){
        winnerCount++;
      }
    }
    if (winnerCount == BOARD_GAMES){
      break;
    }
    i++;
  }

  int lastDrawNumber = drawNumbers[i];
  int sumUnchked = 0;
  for (int i = 0; i < 25; i++){
    if (!boards_marked[lastWinner][i]){
      sumUnchked += boards[lastWinner][i];
    }
  }
  return sumUnchked * lastDrawNumber;
}

int main(int argc, char **argv){
  FILE *file;
  file = fopen(argv[INPUT], "r");

  if(file == NULL){
    printf("File %s cannot be open", argv[INPUT]);
  }
  printf("Começando\n");
  printf("Part1: %lu\n", part1(file));
  fseek(file, 0, 0);
  printf("Part2: %lu\n", part2(file));

  fclose(file);
  return 0;
}
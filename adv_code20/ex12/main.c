#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_INSTRUCTIONS 759

enum INSTRUCTIONS {ILeft = 'L', IRight = 'R', IForward = 'F', IWest = 'W', IEast = 'E', ISouth = 'S', INorth = 'N'};
enum ROTATIONS {REast = 0, RNorth = 90, RWest = 180, RSouth = 270};

struct Instruction {
  char movType;
  int value;
};

struct Vector {
  int x;
  int y;
};

void part1(struct Instruction program[MAX_INSTRUCTIONS]){
  int facingDirect = REast;
  int latitude, longitude = 0;

  for (int i = 0; i < MAX_INSTRUCTIONS; i++){
    if (program[i].movType == INorth || (program[i].movType == IForward && facingDirect == RNorth)){
      latitude += program[i].value;
    }else if (program[i].movType == ISouth || (program[i].movType == IForward && facingDirect == RSouth)){
      latitude -= program[i].value;
    }else if (program[i].movType == IEast || (program[i].movType == IForward && facingDirect == REast)){
      longitude += program[i].value;
    }else if (program[i].movType == IWest || (program[i].movType == IForward && facingDirect == RWest)){
      longitude -= program[i].value;
    }else if (program[i].movType == IRight){
      facingDirect -= program[i].value;
    }else if (program[i].movType == ILeft){
      facingDirect += program[i].value;
    }

    if (facingDirect >= 360){
      facingDirect -= 360;
    }else if (facingDirect < 0){
      facingDirect += 360;
    }
  }
  printf("Solução 1: %d\n", abs(longitude) + abs(latitude));
}

void part2(struct Instruction program[MAX_INSTRUCTIONS]){
  struct Vector boat;
  struct Vector waypoint;
  boat.x = 0;
  boat.y = 0;
  waypoint.x = 10;
  waypoint.y = 1;

  for (int i = 0; i  < MAX_INSTRUCTIONS; i++){
    double angle = ((double)program[i].value / 180) * M_PI;
    struct Vector temp;
    if (program[i].movType == IForward){
      boat.x += waypoint.x * program[i].value;
      boat.y += waypoint.y * program[i].value;
    }else if (program[i].movType == IEast){
      waypoint.x += program[i].value;
    }else if (program[i].movType == IWest){
      waypoint.x -= program[i].value;
    }else if (program[i].movType == INorth){
      waypoint.y += program[i].value;
    }else if (program[i].movType == ISouth){
      waypoint.y -= program[i].value;
    }else if (program[i].movType == IRight){
      temp.x = (waypoint.x * (int)cos(-angle)) - (waypoint.y * (int)sin(-angle));
      temp.y = (waypoint.x * (int)sin(-angle)) + (waypoint.y * (int)cos(-angle));
      waypoint.x = temp.x;
      waypoint.y = temp.y;
    }else if (program[i].movType == ILeft){
      temp.x = (waypoint.x * (int)cos(angle)) - (waypoint.y * (int)sin(angle));
      temp.y = (waypoint.x * (int)sin(angle)) + (waypoint.y * (int)cos(angle));
      waypoint.x = temp.x;
      waypoint.y = temp.y;
    }
  }
  printf("Solução 2: %d\n", abs(boat.x) + abs(boat.y));
}

int main(int argc, char **argv){
  printf("%lf\n", cos(((double)360 / 180) * M_PI));
  FILE *file;
  file = fopen(argv[1], "r");
  if (file == NULL){
    printf("Não existe o arquivo %s", argv[1]);
  }

  struct Instruction program[MAX_INSTRUCTIONS];
  char *line = NULL;
  ssize_t len = 0;
  ssize_t read;
  int count = 0;
  while ((read = getline(&line, &len, file)) != -1){
    char intructionValueStr[read - 2];
    program[count].movType = line[0];
    program[count].value = 0;
    memcpy(intructionValueStr, &line[1], read - 2);
    for (int i = 0; i < read - 2; i++){
      program[count].value *= 10; 
      program[count].value += ((int)intructionValueStr[i] - '0');
    }
    count++;
  }

  part1(program);
  part2(program);
  fclose(file);
  return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>

#if 1
#define INPUT 1
#define POINTS_SZ 90
#else
#define INPUT 2
#define POINTS_SZ 10
#endif

void push(char *stack, size_t *n, char value){
  stack[*n] = value;
  *n += 1;
}

char pop(char *stack, size_t *n){
  *n -= 1;
  return stack[*n];
}

const char opClMap[4][2] = {
  {'(', ')'},
  {'[', ']'},
  {'{', '}'},
  {'<', '>'},
};

int matchClosing(char *stack, size_t *n, char close){
  char open = pop(stack, n);
  for (int i = 0; i < 4; i++){
    if (open == opClMap[i][0]){
      if (close != opClMap[i][1]){
        return 0;
      }
      break;
    }
  }
  return 1;
}

int computeCorruptedPoints(char value){
  switch (value)
  {
  case ')':
    return 3;
    break;
  case ']':
    return 57;
    break;
  case '}':
    return 1197;
    break;
  case '>':
    return 25137;
    break;
  default:
    printf("Unreacheble");
    break;
  }
}

int computeIncompletePoints(char value){
  switch (value){
  case '(':
    return 1;
    break;
  case '[':
    return 2;
    break;
  case '{':
    return 3;
    break;
  case '<':
    return 4;
    break;
  default:
    printf("Unreacheble");
    break;
  }
}

size_t part1(FILE *file){
  char *buf = NULL;
  size_t size = 0;
  char *line;
  size_t line_sz = 0;
  int ln_cnt =  0;

  int count = 0;
  while((line_sz = getline(&buf, &size, file)) != -1){
    line = buf;
    char stack[line_sz];
    size_t stack_sz = 0;
    while (*line != '\n' && *line){
      if (*line == opClMap[0][0] || *line == opClMap[1][0] || *line == opClMap[2][0] || *line == opClMap[3][0]){
        push(stack, &stack_sz, *line);
      }else{
        char close = *line;
        if (!matchClosing(stack, &stack_sz, close)){
          printf("Linha %d \n%sCorrompida em ` %lu : %c `\n\n", ln_cnt, buf, line - buf, close);
          count += computeCorruptedPoints(close);
          break;
        }
      }
      line++;
    }
    ln_cnt++;
  }

  return count;
}

void swap(size_t *xp, size_t *yp)
{
    size_t temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
// Function to perform Selection Sort
void selectionSort(size_t *arr, int n)
{
    size_t min_idx;
 
    // One by one move boundary of unsorted subarray
    for (int i = 0; i < n - 1; i++) {
 
        // Find the minimum element in unsorted array
        min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
 
        // Swap the found minimum element
        // with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}

size_t part2(FILE *file){
  char *buf = NULL;
  size_t size = 0;
  char *line;
  size_t line_sz = 0;
  int ln_cnt =  0;
  size_t points[POINTS_SZ] = {0};
  int incomplete_sz = 0;
  while((line_sz = getline(&buf, &size, file)) != -1){
    line = buf;
    char stack[line_sz];
    size_t stack_sz = 0;
    int incomplete = 1;
    while (*line != '\n' && *line){
      if (*line == opClMap[0][0] || *line == opClMap[1][0] || *line == opClMap[2][0] || *line == opClMap[3][0]){
        push(stack, &stack_sz, *line);
      }else{
        char close = *line;
        if (!matchClosing(stack, &stack_sz, close)){
          // printf("Linha %d \n%sCorrompida em ` %lu : %c `\n\n", ln_cnt, buf, line - buf, close);
          incomplete = 0;
          break;
        }
      }
      line++;
    }
    if (incomplete){
      stack[stack_sz] = '\0';
      printf("Linha %d\nNão corrompida\n Stack restante ` %s `\n", ln_cnt, stack);
      for (int i = stack_sz - 1;  i >= 0; i -= 1){
        points[incomplete_sz] = points[incomplete_sz] * 5 + computeIncompletePoints(stack[i]);
      }
      printf("Points: %lu\n\n", points[incomplete_sz]);
      incomplete_sz++;
    }
    ln_cnt++;
  }
  selectionSort(points, incomplete_sz);
  return points[incomplete_sz / 2];
}

int main(int argc, char **argv){
  system("clear");
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
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void part1(size_t nRows, size_t nColumns, char grid[nRows][nColumns]){
  char newGrid[nRows][nColumns];
  int nOccupiedSeats = 0;
  while (1){
    // Para cada célula atualizar de acordo com os  vizinhos
    for (int i = 0; i < nRows; i++){
      for (int j = 0; j < nColumns; j++){
        int pesoAdjacentes = 0;
        for (int l = -1; l <= 1; l++){
          for (int k = -1; k <= 1; k++){
            if (l == 0 && k == 0){
              continue;
            }
            if (i + l < 0 || j + k < 0 || i + l >= nRows || j + k >= nColumns){
              continue;
            }
            if (grid[i + l][j + k] == '#'){
              pesoAdjacentes++;
            }
          }
        }
        char celula = grid[i][j];
        //If a seat is empty (L) and there are no occupied seats adjacent to it, the seat becomes occupied.
        if (celula == 'L' && pesoAdjacentes == 0){
          newGrid[i][j] = '#';
        }
        //2. If a seat is occupied (#) and four or more seats adjacent to it are also occupied, the seat becomes empty.
        else if(celula == '#' && pesoAdjacentes >= 4){
          newGrid[i][j] = 'L';
        } else {
          newGrid[i][j] = celula;
        }
      }
    }
    if (memcmp(&grid[0][0], &newGrid[0][0], nColumns * nRows) == 0){
      break;
    }
    nOccupiedSeats = 0;
    for (int i = 0; i < nRows; i++){
      for (int j = 0; j < nColumns; j++){
        grid[i][j] = newGrid[i][j];
        if (grid[i][j] == '#'){
          nOccupiedSeats++;
        }
      }
    }
  }
  
  printf("Count: %d\n", nOccupiedSeats);
}

void part2(size_t nRows, size_t nColumns, char grid[nRows][nColumns]){
  char newGrid[nRows][nColumns];
  int nOccupiedSeats = 0;
  while (1){
    // Para cada célula atualizar de acordo com os  vizinhos
    for (int i = 0; i < nRows; i++){
      for (int j = 0; j < nColumns; j++){
        int occupiedSeats = 0;
        for (int l = -1; l <= 1; l++){
          for (int k = -1; k <= 1; k++){
            if (l == 0 && k == 0){
              continue;
            }
            if (i + l < 0 || j + k < 0 || i + l >= nRows || j + k >= nColumns){
              continue;
            }
            int dist = 1;
            while (!(i + l * dist < 0 || j + k * dist < 0 || i + l * dist >= nRows || j + k * dist >= nColumns)){
              if (grid[i + l * dist][j + k * dist] != '.'){
                if (grid[i + l * dist][j + k * dist] == '#'){
                  occupiedSeats++;
                }
                break;
              }
              dist++;
            }
          }
        }
        char celula = grid[i][j];
        //If a seat is empty (L) and there are no occupied seats adjacent to it, the seat becomes occupied.
        if (celula == 'L' && occupiedSeats == 0){
          newGrid[i][j] = '#';
        }
        //2. If a seat is occupied (#) and four or more seats adjacent to it are also occupied, the seat becomes empty.
        else if(celula == '#' && occupiedSeats >= 5){
          newGrid[i][j] = 'L';
        } else {
          newGrid[i][j] = celula;
        }
      }
    }
    if (memcmp(&grid[0][0], &newGrid[0][0], nColumns * nRows) == 0){
      break;
    }
    nOccupiedSeats = 0;
    for (int i = 0; i < nRows; i++){
      for (int j = 0; j < nColumns; j++){
        grid[i][j] = newGrid[i][j];
        if (grid[i][j] == '#'){
          nOccupiedSeats++;
        }
      }
    }
  }
  
  printf("Count: %d\n", nOccupiedSeats);
}

int main(int *argc, char **argv){
  FILE *file;
  file = fopen(argv[1], "r");

  fseek(file, 0L, SEEK_END);
  long int fileSize = ftell(file);
  rewind(file);
  char *line = NULL;
  size_t len = 0;
  ssize_t read = getline(&line, &len, file);

  size_t nColumns = read - 1;
  size_t nRows = fileSize / read;
  char grid[nRows][nColumns];
  int count = 0;

  rewind(file);
  while ((read = getline(&line, &len, file)) != -1){
    memccpy(grid[count], line, 10, read);
    count++;
  }

  part1(nRows, nColumns, grid);

  rewind(file);
  count = 0;
  while ((read = getline(&line, &len, file)) != -1){
    memccpy(grid[count], line, 10, read);
    count++;
  }

  part2(nRows, nColumns, grid);

  fclose(file);
  return 0; 
}
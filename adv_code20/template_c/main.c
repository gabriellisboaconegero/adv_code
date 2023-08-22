#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv){
  FILE *file;
  file = fopen(argv[1], "r");

  if (file ==  NULL){
    printf("Arquivo %s não existe\n", argv[1]);
  }

  fseek(file, 0L, SEEK_END);
  long int fileSize = ftell(file);
  rewind(file);
  char *line = NULL;
  size_t len = 0;
  ssize_t read = getline(&line, &len, file);

  fclose(file);
  return 0; 
}
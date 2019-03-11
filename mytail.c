//alejandra sanchez
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

  int size;

void addToArray(char *val, char **array, int *sum, int size) {
  if (*sum == 0) array[0] = val;
  else array[(*sum)%size] = val;
  (*sum)++;

}
void printArray(char **array, int *sum, int size) {
  for (int i = 0; i < size; i++) {
    printf("%s", array[(*sum) % size]);
    (*sum)++;

  }
}

char *readaline(int maxLength) {
  char *line = (char*)malloc(maxLength * sizeof(char));
  char *toReturn = fgets(line, maxLength, stdin);

  if (toReturn == NULL) {
    free(line);
    return NULL;
  }
  return line;


}

int main(int argc, char* argv[]){
  size = 0;
  if (argc == 1) {
    size = 10; // default
  }
  else {
    char* string = argv[1];
    int len = strlen(string);
    int i;
    for (i = 0; i <len; i++){
      size = size*10 + (string[i] - '0');
    }
  }

  int sum;
  char **array = (char**)malloc(size * sizeof(char*));
  while(1) {
    char *nextLine = readaline(80);
    if (nextLine == NULL) break;
    addToArray(nextLine, array, &sum, size);
  }
  printArray(array, &sum, size);

  int line;
  for (line = 0; line < size; line++){
    free(array[line]);
   }
   free(array);

}

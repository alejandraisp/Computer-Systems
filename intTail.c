//alejandra sanchez
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

void addToArray(int val, int *array, int *sum, int size) {
  //printf("adding %d sum= %d size= %d", val, *sum, size);
  if (*sum == 0) array[0] = val;
  else array[(*sum)%size] = val;
  (*sum)++;
}
void printArray(int *array, int *sum, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", array[(*sum) % size]);
    (*sum)++;
  }
}

int main(int argc, char *argv[]) {
  int size = 0;
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

  printf("please enter positive integers with a space in between them:");
  int *array = (int*)malloc(size * sizeof(int));
  int sum = 0;

  while (1) {
    int nextVal;
    scanf("%d" , &nextVal);
    //printf("%d\n", nextVal);
    if (nextVal == -1) break;

    addToArray(nextVal, array, &sum, size);
  }
  //print arr
  //int size;
  printf("here are the last %d values\n", size);
  printArray(array, &sum, size);
  printf("\n");

  return 0;
}

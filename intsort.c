#include <stdio.h>
#include <stdlib.h>
#include "intsort.h"

int main() {
  printf("Enter some numbers, ending with -1: ");
  IntNode *header;
  header = NULL;

  while(1) {
    int nextVal;
    scanf("%d", &nextVal);
    if (nextVal == -1) {
      break;
    }

    if (header == NULL) { // first item to be added
      header = createNode(nextVal);
      continue;
    }
    insert(header, nextVal);

  }
  printAll(header);

}


IntNode *createNode(int val) {
  IntNode *newNode;
  newNode = malloc(sizeof(IntNode));
  newNode->item = val;
  newNode->next = NULL;
  return newNode;
}

// insert a node into the chain, in sorted order
void insert(IntNode *header, int val) {
  IntNode *current = header;
  // if this item will be the first in the list
  if (val < current->item) {
    int temp = current->item;
    current->item = val;
    IntNode *newNode = createNode(temp);
    newNode->next = current->next;
    current->next = newNode;
  }
  // otherwise
  else {
    while (current->next != NULL && current->next->item < val) {
      current = current->next;
    }
    IntNode *newNode = createNode(val);
    newNode->next = current->next;
    current->next = newNode;
  }
}


void printAll(IntNode *header) {
  IntNode *current = header;
  printf("The sorted numbers are......\n");
  while(current != NULL) {
    printf("%d ", current->item);
    current = current->next;
  }
  printf("\n");
}

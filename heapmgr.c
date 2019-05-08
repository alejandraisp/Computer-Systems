#include <stdio.h>
#include <stdlib.h>
#include "memorymgr.h"

int *sentinelBlock;
int *beginBlock;


int isAllocated(int *p) {
  if (*p / 2 * 2 == *p) {
    return 0;
  }
  else {
    return 1;
  }
}

void initmemory(int size) {

  int memSize = size + 4; // header
  while (memSize%8 != 0) { // total size of block
    memSize++;
  }
  int totalSize = memSize+8; // add padding and sentinel

  beginBlock = (int*)malloc(totalSize);
  beginBlock += 1; // ignore the beginning padding
  *beginBlock = memSize - 4;
  //sentinelBlock = beginBlock + ((memSize/4) - 1) - 2;
  sentinelBlock = nextBlock(beginBlock);
  *sentinelBlock = 0;

}

void *myalloc(int length) {
  // format length to an appropriate size
  int lenSize = length + 4;
  while(!(lenSize%8 == 0)) {
    lenSize++;
  }
  lenSize = lenSize - 4;

  // find the first big enough block
  int *p = beginBlock;
  while(*p < lenSize || isAllocated(p)) {
    p = nextBlock(p);
    if (p == sentinelBlock) {
      return NULL;
    }
  }
  int leftOverBlockSize = *p -  (lenSize + 4);
  *p = lenSize + 1; // adjust header
  if (leftOverBlockSize > 0) // create left over block
  {
    int* leftOverBlockSizeP = nextBlock(p);
    *leftOverBlockSizeP = leftOverBlockSize;
  }
  return p+1;
}

void myfree(void *ptr) {
  int *p = ptr;
  p--;
  *p = *p - 1;

}

void coalesce() {
  int *p = beginBlock;
  int *next = nextBlock(p);
  while (next != sentinelBlock) {
    if (isAllocated(p) == 0 && isAllocated(next) == 0) {
      *p = *p + *next + 4;
      next = nextBlock(p);
    }
    else {
      p = nextBlock(p);
      next = nextBlock(next);
    }
  }
}

void printallocation() {
  int *p = beginBlock;

  int blockNumber = 0;
  int i;
  while ((int)p != (int)sentinelBlock) {
    int size = (*p / 2) * 2 + 4;
    printf("Block %d: %d bytes, ", blockNumber, size);
    if (isAllocated(p)) {
      printf("allocated\n");
    }
    else {
      printf("unallocated\n");
    }

    blockNumber++;
    p = nextBlock(p);
  }

}



int *nextBlock(int *p) {
  int val = *p;
  val = val / 2 * 2; // get rid of the allocated bit
  val /= 4;

  return p + val + 1;
}


int *firstBlock() {
  return beginBlock;
}


int *lastBlock() {
  return sentinelBlock;
}

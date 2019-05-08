#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include <string.h>


struct wordcount {
  char word[80];
  int count;
};
typedef struct wordcount WordCount;

WordCount* mostFreq(BSTnode *wc) {
  if (wc == NULL) {
    return NULL;
  }

  WordCount* mostFreqLeft = mostFreq(wc->left);
  WordCount* mostFreqRight = mostFreq(wc->right);
  WordCount* rootItem = (WordCount*)(wc->item);

  int leftCount;
  if (mostFreqLeft == NULL) {
    leftCount = 0;
  }
  else {
    leftCount = mostFreqLeft->count;
  }

  int rightCount;
  if (mostFreqRight == NULL) {
    rightCount = 0;
  }
  else {
    rightCount = mostFreqRight->count;
  }

  int rootCount = rootItem->count;

  if (rightCount >= rootCount && rightCount >= leftCount) {
    return mostFreqRight;
  }
  else if (leftCount >= rootCount && leftCount >= rightCount) {
    return mostFreqLeft;
  }
  else {
    return rootItem;
  }
}

int compareWord(void* v1, void* v2) {
  WordCount *wc1 = (WordCount*)v1;
  WordCount *wc2 = (WordCount*)v2;

  return (strcmp(wc1->word, wc2->word));
}

int main() { //finish
  int totalWords = 0;

  BSTnode *tree;

  while(1) {
    char word[80];
    int val = scanf("%s", word);

    if (val == EOF) break;

    totalWords++;

    WordCount *wc = malloc(sizeof(WordCount));
    strcpy(wc->word, word);
    wc->count = 1;

    if (totalWords == 1) {
      tree = createNode((void*)wc);
      continue;
    }

    BSTnode *searchResult = find(tree, wc, compareWord);
    WordCount *searchResultItem = (WordCount*)searchResult->item;


    if (compareWord(wc, searchResultItem) == 0) {             //if the found word and wc are the same
      searchResultItem->count = searchResultItem->count + 1; //then increment the frequency
      continue;
    }

    insert(tree, wc, compareWord); //otherwise add to the tree


  }

  WordCount *mostFreqItem = mostFreq(tree);
  printf("The most frequent word is \"%s\" which appears %d times\n", mostFreqItem->word, mostFreqItem->count);

  return 0;
}

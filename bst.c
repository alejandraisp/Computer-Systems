//Alejandra sanchez

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"


BSTnode *createNode(void *item){
  BSTnode *new_node;
  new_node = malloc(sizeof(BSTnode));
  new_node->item = item;
  new_node->left = NULL;
  new_node->right = NULL;
  return new_node;
}

// Search the tree rooted at node n for the node matching the specified item.
// If the item exists, return its node.  If not, return the node that would be its parent.
// The function "compare" compares items.

BSTnode *find(BSTnode *n, void *item, int compare(void *, void *)) {

  if (compare(item, n->item) == 0) {
    return n;
  }
  else if (compare(item, n->item) > 0) {
    if (n->right == NULL) return n;
    return find(n->right, item, compare);
  }
  else {
    if (n->left == NULL) return n;
    return find(n->left, item, compare);
  }
}

void insert(BSTnode *n, void *item, int compare(void *, void *)) {
  if (compare(item, n->item) > 0) {
    if (n->right == NULL) {
      n->right = createNode(item);
      return;
    }
    insert(n->right, item, compare); // do we need to pass three arguments here?
  }
  if(compare(item, n->item) < 0) {
    if (n->left == NULL) {
      n->left = createNode(item);
      return;
    }
    insert(n->left, item, compare);
  }
}

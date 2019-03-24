//Simple calculator program on C

//alejandra sanchez
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pushValStack(int *valStack, int *valTop, int value) {
  *valTop += 1;
  valStack[*valTop] = value;

}

int popValStack(int *valStack, int *valTop) {
  int Val;
  Val = valStack[*valTop];
  *valTop -= 1;
  return Val;

}

void pushOpStack(char **stack, int *opTop, char *value) {
  *opTop += 1;
  stack[*opTop] = value;

}

char *popOpStack(char **stack, int *opTop) {
  char *Val;
  Val = stack[*opTop];
  *opTop -= 1;
  return Val;
}



int main(int argc, char* argv[]) {
  char **stack = malloc(50 * sizeof(char*));
  int *valStack = malloc(50 * sizeof(int));
  int valTop = -1;
  int opTop = -1;
  int value;


  int i;
  for ( i = 1; i < argc; i++){
    char *token = argv[i];

    // token is an operator - push to stack
    if ((strcmp(token, "x") == 0 )|| (strcmp(token, "+") == 0) || (strcmp(token, "[") == 0)) {
      pushOpStack(stack, &opTop, token);
    }

    // token is a right paren - pop to values and push result
    else if (strcmp(token, "]") == 0 ) {
      char *poppedOp = "";
      while (1) {
        poppedOp = popOpStack(stack, &opTop);

        if (strcmp(poppedOp, "[") == 0) break;

        if (strcmp(poppedOp, "x") == 0 || strcmp(poppedOp, "+") == 0) {
          int firstVal = popValStack(valStack, &valTop);
          int secondVal = popValStack(valStack, &valTop);
          if (strcmp(poppedOp, "x") == 0) {
            int result = (firstVal * secondVal);
            pushValStack(valStack, &valTop, result);
          }
          else if (strcmp(poppedOp, "+") == 0) {
            int result = (firstVal + secondVal);
            pushValStack(valStack, &valTop, result);
          }
        }

      }
    }

    else { // token is a number - push to stack
      int tokenVal = atoi(token);
      pushValStack(valStack, &valTop, tokenVal);
    }
  }

  while (opTop > -1) {
    int firstVal = popValStack(valStack, &valTop);
    int secondVal = popValStack(valStack, &valTop);
    char *poppedOp = popOpStack(stack, &opTop);
    if (strcmp(poppedOp, "x") == 0) {
      int result = (firstVal * secondVal);
      pushValStack(valStack, &valTop, result);

    }
    else if (strcmp(poppedOp, "+") == 0) {
      int result = (firstVal + secondVal);
      pushValStack(valStack, &valTop, result);
    }

  }

  int finalResult = popValStack(valStack, &valTop);
  printf("Result: %d \n" , finalResult);

}

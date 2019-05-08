//Alejandra Sanchez

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10

int searchPosition(int i);
void* search(void*);

#define TEXT_LEN 1000000

// The pattern and text strings are global variables
char *pattern;
char text[TEXT_LEN];
int result = -1; // a positive value indicates the location of the match
pthread_mutex_t mutex;
int *check_pat;
int patlen;
int textlen;
int next = 0;

int main(int argc, char *argv[]) {

   // Step 1: Extract the pattern string from the command line.

   pattern = argv[1];
   patlen = strlen(pattern);

   check_pat = (int*)malloc(textlen * sizeof(int));
   int i;
   for (i = 0; i < textlen; i++) {
     check_pat[i] = 0;
   }

   // Step 2: Create and populate the text string.
   // Note that it isn't a proper "string" in the C sense,
   // because it doesn't end in '\0'.

   textlen = TEXT_LEN; // will be overridden by the actual length
   int count = 0;
   while (count < TEXT_LEN) {
       int status = scanf("%c", &text[count]);
       count++;
       if (status == EOF) {
          textlen = count;
          break;
       }
   }

   pthread_mutex_init(&mutex, NULL);

   // Step 3: Search for the pattern in the text string
   pthread_t thd[NUM_THREADS];
   for (i = 0; i<NUM_THREADS; i++) {
     pthread_create(thd + i, NULL, search, NULL);
   }
   for (i = 0; i<NUM_THREADS; i++) {
     pthread_join(thd[i], NULL);
   }


   // Step 4: Determine the result and print it

   if (result == -1)
       printf("Pattern not found\n");
   else
       printf("Pattern begins at character %d\n", result);
}

void* search(void*arg) {
  while(1) {
    pthread_mutex_lock(&mutex);
    if (result > 0 || next > (textlen - patlen)) {
      pthread_mutex_unlock(&mutex);
      break; // a thread has found the answer
    }

    int i = next;
    next++;
    pthread_mutex_unlock(&mutex);


    int f = searchPosition(i);
      pthread_mutex_lock(&mutex);
        if (f > 0) {
      result = i;
      }

    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

    /* pthread_mutex_lock(&mutex);
    int j;
    for (j = 0; j<textlen; j++) {
      if (check_pat[j] != 1 ) {
        check_pat[j] = 1;
        break;
      }
    }
    pthread_mutex_unlock(&mutex);
    if (j == textlen) {
      return NULL; // there's nothing left to search
    }



    if (searchPosition(j) == 1) {
      result = j;
      return NULL; // we found the answer
    }
  }
}
*/
// returns 1 if a match is found
int searchPosition(int i) {

 int j;
 for (j=0;j<patlen; j++)
     if (text[i+j] != pattern[j])
        return 0;
 return 1;
}

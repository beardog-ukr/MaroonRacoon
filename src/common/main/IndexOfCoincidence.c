#include "IndexOfCoincidence.h"
#include "CosetFunctions.h"

#include <float.h> //DBL_MAX
// #include <stdio.h> //printf, fgetc, fopen, snprintf
#include <string.h> // strlen
#include <stdlib.h>

// ============================================================================

double calculateIndexOfCoincidence(const char* const line,
                                   const AlphabetTransform* const at) {
  int counters[at->n] ;
  for (int i=0; i<at->n; i++) {
    counters[i] =0;
  }

  const int lineLength = strlen(line);
  const char* const lineEnd = &line[lineLength];
  for (const char * chi = &line[0]; chi<lineEnd; chi++) {
    int tpos = findAlphabetPos(at->basic, *chi);
    if ( (tpos>=0) && (tpos <at->n)) {
      counters[tpos]++ ;
    }
  }

  int csum = 0;
  for (int i=0; i<at->n; i++) {
    if (counters[i] >0) {
      csum += counters[i]*(counters[i]-1) ;
    }
    //printf("Counter %c is %u (%u)\n", at->basic[i], counters[i], csum);
  }

  //printf("And line length is %u (%u)\n", lineLength, csum );
  double result = lineLength*(lineLength-1);
  result = csum / result;

  return result;
}

// ============================================================================

int guessKeyLengthIOC(const char* const line,const AlphabetTransform* const at) {
  const int maxKeyLength = 12 ; //as specified in the task

  const int lineLen = strlen(line) ;
  char* cosetBuf = malloc(lineLen+1);

  int guessedLength = 0;
  double aiocgl = 0; // average IoC for guessed length

  for(int li=1; li<=maxKeyLength; li++) { //iteration over possible length
    double aiocAcc = 0;
    for(int ci=0; ci<li; ci++) {
      readCosetFromLine(line, ci, li, cosetBuf, lineLen);
      double tmpd = calculateIndexOfCoincidence(cosetBuf, at);
      //printf("IOC: %f %s (%u:%u)\n", tmpd, cosetBuf, ci, li);
      aiocAcc += tmpd;
    }
    double currentAioc = aiocAcc/li;
    if (currentAioc> aiocgl) {
      aiocgl = currentAioc;
      guessedLength = li;
    }
  }

  free(cosetBuf) ;
  return guessedLength ;
}

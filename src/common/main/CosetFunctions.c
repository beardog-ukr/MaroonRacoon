#include "CosetFunctions.h"

#include <float.h> //DBL_MAX
#include <stdbool.h> //bool
#include <stdio.h> //fgetc, fopen
#include <stdlib.h> // malloc
#include <string.h> //strlen

// ===========================================================================

int readCosetFromLine(const char * const line,
                      const int cosetIndex, const int cosetNumber,
                      char* resultBuf, const int resultLen){
  const int lineLen = strlen(line) ;

  int ci = cosetIndex;
  int ri=0;
  while ( (ci<lineLen)&&(ri<(resultLen-1)) ) {
    resultBuf[ri] = line[ci];
    ci += cosetNumber ;
    ri++;
  }

  resultBuf[ri] = '\0' ;

  return 0;
}

// ===========================================================================

char getShiftedCosetSymbol(const char ch, const AlphabetTransform* const at,
                          const int shift){
  int chPos = findAlphabetPos(at->basic, ch) ;
  int resultPos = chPos -shift;
  if (resultPos <0) {
    resultPos = at->n + resultPos ;
  }

  if ((resultPos>=0)&&(resultPos<at->n)) {
    return at->basic[resultPos];
  }
  else {
    return '\0' ;
  }
}

// ===========================================================================

#include "Breaker.h"

#include "Chi2Decode.h"
#include "CosetFunctions.h" //readCosetFromLine
#include "IndexOfCoincidence.h"
#include "FileUtils.h" //readFullFile

#include <stdio.h>
#include <stdlib.h>

// ===========================================================================

int performBreak(const char* const inFilename, const char* const outFilename,
                 const AlphabetTransform* at, const FrequencyInfo* finfo) {
  //
  int result =0;
  const int fileBufLength = 500*1024 ;
  char* fileBuf = malloc(fileBufLength);

  result = readFullFile(inFilename, fileBuf, fileBufLength);
  if (result!=0) {
    free(fileBuf) ;
    return result;
  }

  const int keyLength = guessKeyLengthIOC(fileBuf,at);

  char key[keyLength+1] ;
  char* cosetBuf = malloc(fileBufLength) ;

  for(int i=0; i<keyLength; i++ ) {
    result = readCosetFromLine(fileBuf, i, keyLength, cosetBuf, fileBufLength);
    char tch = decodeChi2ForCoset(cosetBuf, at, finfo);
    if (tch=='\0') {
      tch = '#';
    }
    key[i] = tch;
  }
  key[keyLength] = '\0';

  printf("Key is guessed as \"%s\"\n", key) ;

  free(cosetBuf) ;
  free(fileBuf) ;

  //---
  result = performDecoding(inFilename, outFilename, key, at);

  //finally
  return result;
}

// ===========================================================================

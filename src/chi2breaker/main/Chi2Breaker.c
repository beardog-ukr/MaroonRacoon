#include "Chi2Breaker.h"
#include "Chi2Decode.h"
#include "FileUtils.h"

#include <stdbool.h> //bool
#include <stdio.h> //fgetc, fopen
#include <stdlib.h> // malloc
#include <string.h> //strlen

enum Chi2BreakerErrorCodes {
  C2EC_FAILED_READ_SOURCE ,
  C2EC_FAILED_WRITE_RESULT,
  C2EC_EMPTY_KEY
};

//static const char PECM_FAILED_READ_ALPHABET[] = "Failed to read alphabet file\n";

// ===========================================================================

int performChi2Break(const char* const inFilename, const char* const outFilename,
                     const int keyLength,
                     const AlphabetTransform* at, const FrequencyInfo* finfo) {
  int result =0;
  const int fileBufLength = 500*1024 ;
  char* fileBuf = malloc(fileBufLength);

  result = readFullFile(inFilename, fileBuf, fileBufLength);
  if (result!=0) {
    free(fileBuf) ;
    return result;
  }

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

  printf("Key is guessed as %s\n", key) ;

  free(cosetBuf) ;
  free(fileBuf) ;
  return result;
}

// ===========================================================================

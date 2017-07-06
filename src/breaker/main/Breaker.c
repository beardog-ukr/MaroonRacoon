#include "Breaker.h"

#include "BasicDecode.h"
#include "Chi2Decode.h"
#include "CosetFunctions.h" //readCosetFromLine
#include "IndexOfCoincidence.h"
#include "FileUtils.h" //readFullFile

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum BreakerErrorCodes {
  BEC_FAILED_READ =1,
  BEC_EMPTY_FILE,
  BEC_FAILED_KEY,
  BEC_FAILED_DECODING
};

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
    return BEC_FAILED_READ;
  }

  if (strlen(fileBuf)==0 ) {
    return BEC_EMPTY_FILE;
  }

  const int keyLength = guessKeyLengthIOC(fileBuf,at);

  char key[keyLength+1] ;
  char* cosetBuf = malloc(fileBufLength) ;

  bool gotError = false;
  for(int i=0; i<keyLength; i++ ) {
    result = readCosetFromLine(fileBuf, i, keyLength, cosetBuf, fileBufLength);
    char tch = decodeChi2ForCoset(cosetBuf, at, finfo);
    if (tch=='\0') {
      tch = '#';
      gotError = true;
    }
    key[i] = tch;
  }
  key[keyLength] = '\0';

  free(cosetBuf) ;
  free(fileBuf) ;

  if (gotError) {
    return BEC_FAILED_KEY;
  }

  printf("Key is guessed as \"%s\"\n", key) ;

  //---
  if ( performDecoding(inFilename, outFilename, key, at) !=0 ) {
    return BEC_FAILED_DECODING;
  }
  //finally
  return result;
}

// ===========================================================================

void printBreakerError(const int errorCode){
  switch (errorCode) {
    case BEC_FAILED_READ:
      printf("Failed to read source file\n");
    break;
    case BEC_EMPTY_FILE:
      printf("Source file is empty or contains no letters\n");
    break;
    case BEC_FAILED_KEY:
      printf("Failed to guess key\n");
    break;
    case BEC_FAILED_DECODING:
      printf("Failed during decoding\n");
    break;
    default:
      printf("Unknown breaker error\n");;
  }
}

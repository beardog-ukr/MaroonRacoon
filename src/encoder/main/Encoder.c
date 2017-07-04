#include "Encoder.h"

#include <stdbool.h> //bool
#include <stdio.h> //fgetc, fopen
#include <stdlib.h> // malloc
#include <string.h> //strlen

enum PreprocessorErrorCodes {
  EEC_FAILED_READ_SOURCE ,
  EEC_FAILED_WRITE_RESULT,
  EEC_EMPTY_KEY
};

//static const char PECM_FAILED_READ_ALPHABET[] = "Failed to read alphabet file\n";

// ===========================================================================

char encodeOneChar(const AlphabetTransform* at,
                    const char* key, const int keyLen,
                    const int keyPos, const char symbol) {
  const char keyChar = key[(keyPos % keyLen)] ;
  int ksPos = findAlphabetPos(at->basic, keyChar);
  int psPos = findAlphabetPos(at->basic, symbol);
  int cPos = (ksPos + psPos) % at->n;

  return at->basic[cPos];
}

// ===========================================================================

void encodeLine(const AlphabetTransform* at, char* line,
                const char* key, const int keyLen, const int startPos,
                char* result, const int resultLimit){
  const int lineLen = strlen(line);

  int charPos = startPos;
  int ri=0;
  for(int i=0; i<lineLen; i++) {
    char tch = encodeOneChar(at, key, keyLen, charPos, line[i]);
    result[ri] = tch;
    ri++;
    if (ri>=resultLimit) {
      result[ri-1] = '\0';
      return;
    }

    charPos++;
  }

  result[ri] = '\0';
}

// ===========================================================================

int performEncoding(const char* inFilename, const char* outFilename,
                    const char* key, const AlphabetTransform* at) {
  const int keyLen = strlen(key);
  if (keyLen==0) {
    return EEC_EMPTY_KEY;
  }

  FILE* fp;
  FILE* resultFile;

  //printf("Starting for %s \n", inFilename);

  fp = fopen(inFilename, "r");
  if (fp == NULL) {
    //printf("Failed to read %s \n", inFilename);
    return EEC_FAILED_READ_SOURCE;
  }

  resultFile = fopen(outFilename, "w");
  if (resultFile == NULL) {
    return EEC_FAILED_WRITE_RESULT;
  }

  const int bufSize = 8192;
  char* buf = malloc(bufSize);
  char* cBuf = malloc(bufSize);
  char* eBuf = malloc(bufSize);

  int charPos =0;

  while ( fgets(buf, bufSize, fp) != NULL) {
    int rbl = strlen(buf) ;
    if (buf[rbl-1]=='\n') {
      buf[rbl-1]='\0';
      rbl--;
    }
    convertLine(at, buf, cBuf, bufSize);
    encodeLine(at, cBuf, key, keyLen, charPos, eBuf, bufSize);
    fprintf(resultFile, "%s\n", eBuf);
    //printf("Basic: %s\n", buf);
    //printf("Conv : %s\n", cBuf);
    //printf("Enc  : %s\n", eBuf);

    charPos += strlen(cBuf);
  }

  fclose(fp);
  fclose(resultFile);

  free(buf);
  free(cBuf);
  free(eBuf);

  return 0;
}

// ===========================================================================

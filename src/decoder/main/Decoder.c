#include "Decoder.h"

#include <stdbool.h> //bool
#include <stdio.h> //fgetc, fopen
#include <stdlib.h> // malloc
#include <string.h> //strlen

enum PreprocessorErrorCodes {
  DEC_FAILED_READ_SOURCE ,
  DEC_FAILED_WRITE_RESULT,
  DEC_EMPTY_KEY
};

//static const char PECM_FAILED_READ_ALPHABET[] = "Failed to read alphabet file\n";

// ===========================================================================

char decodeOneChar(const AlphabetTransform* at,
                    const char* key, const int keyLen,
                    const int keyPos, const char symbol) {
  const char keyChar = key[(keyPos % keyLen)] ;
  int ksPos = findAlphabetPos(at->basic, keyChar);
  int csPos = findAlphabetPos(at->basic, symbol);
  int psPos = (csPos - ksPos) ;//
  if (psPos<0) {
    psPos = at->n + psPos ;
  }
  psPos = psPos % at->n;

  return at->basic[psPos];
}

// ===========================================================================

void decodeLine(const AlphabetTransform* at, char* line,
                const char* key, const int keyLen, const int startPos,
                char* result, const int resultLimit){
  const int lineLen = strlen(line);

  int charPos = startPos;
  int ri=0;
  for(int i=0; i<lineLen; i++) {
    char tch = decodeOneChar(at, key, keyLen, charPos, line[i]);
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

int performDecoding(const char* inFilename, const char* outFilename,
                    const char* key, const AlphabetTransform* at) {
  const int keyLen = strlen(key);
  if (keyLen==0) {
    return DEC_EMPTY_KEY;
  }

  FILE* fp;
  FILE* resultFile;

  //printf("Starting for %s \n", inFilename);

  fp = fopen(inFilename, "r");
  if (fp == NULL) {
    //printf("Failed to read %s \n", inFilename);
    return DEC_FAILED_READ_SOURCE;
  }

  resultFile = fopen(outFilename, "w");
  if (resultFile == NULL) {
    return DEC_FAILED_WRITE_RESULT;
  }

  const int bufSize = 8192;
  char* buf = malloc(bufSize);
  char* dBuf = malloc(bufSize);

  int charPos =0;

  while ( fgets(buf, bufSize, fp) != NULL) {
    int rbl = strlen(buf) ;
    if (buf[rbl-1]=='\n') {
      buf[rbl-1]='\0';
      rbl--;
    }

    decodeLine(at, buf, key, keyLen, charPos, dBuf, bufSize);
    fprintf(resultFile, "%s\n", dBuf);
    printf("Basic: %s\n", buf);
    printf("Enc  : %s\n", dBuf);

    charPos += strlen(buf);
  }

  fclose(fp);
  fclose(resultFile);

  free(buf);
  free(dBuf);

  return 0;
}

// ===========================================================================

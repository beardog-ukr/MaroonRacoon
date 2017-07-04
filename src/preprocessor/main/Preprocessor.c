#include "Preprocessor.h"

#include <stdbool.h> //bool
#include <stdio.h> //fgetc, fopen
#include <stdlib.h> // malloc
#include <string.h> //strlen


enum PreprocessorErrorCodes {
  PEC_FAILED_READ_SOURCE =1,
  PEC_FAILED_WRITE_RESULT
};

// ===========================================================================

int preprocessFiles(char* inFilename, char* outFilename, AlphabetTransform* at)  {
  FILE* fp;
  FILE* resultFile;

  printf("Starting for %s \n", inFilename);

  fp = fopen(inFilename, "r");
  if (fp == NULL) {
    //printf("Failed to read %s \n", inFilename);
    return PEC_FAILED_READ_SOURCE;
  }

  resultFile = fopen(outFilename, "w");
  if (resultFile == NULL) {
    return PEC_FAILED_WRITE_RESULT;
  }

  const int bufSize = 8192;
  char* buf = malloc(bufSize);
  const int cSize = 8192; //converted size
  char* cBuf = malloc(cSize);

  while ( fgets(buf, bufSize, fp) != NULL) {
    int rbl = strlen(buf) ;
    if (buf[rbl-1]=='\n') {
      buf[rbl-1]='\0';
    }
    convertLine(at, buf, cBuf, cSize);
    fprintf(resultFile, "%s\n", cBuf);
  }

  fclose(fp);
  fclose(resultFile);

  free(buf);
  free(cBuf);

  return 0;
}

// ===========================================================================

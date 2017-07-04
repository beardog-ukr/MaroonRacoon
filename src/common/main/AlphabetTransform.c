#include "AlphabetTransform.h"

#include <stdbool.h> //bool
#include <stdio.h> //fgetc, fopen
#include <stdlib.h> // malloc
#include <string.h> //strlen

// ===========================================================================

enum PreprocessorErrorCodes {
  ATEC_FAILED_READ_ALPHABET =1,
  ATEC_ALPHABET_BAD_FORMAT
};

// ===========================================================================

int getAlphabetLoaderError(const int errorCode, char* line, const int lineLim) {
  int result =0;
  switch (errorCode) {
    case ATEC_FAILED_READ_ALPHABET:
      snprintf(line, lineLim, "Failed to read alphabet file\n");
    break;
    case ATEC_ALPHABET_BAD_FORMAT:
      snprintf(line, lineLim, "Incorrect format of the alphabet file\n");
    break;
    default:
      result =1;
  }

  return result ;
}

// ===========================================================================

void printAlphabetLoaderError(const int errorCode){
  const int ebs = 1024;
  char errbuf[ebs];
  if ( getAlphabetLoaderError(errorCode, errbuf, ebs) ==0) {
    fprintf(stderr, "%s\n", errbuf);
  }
  else {
    fprintf(stderr, "Unknown internal error (alphabet, %u)\n", errorCode);
  }
}

// ===========================================================================

AlphabetTransform* createAlphabetTransform() {
  AlphabetTransform* result = malloc(sizeof (AlphabetTransform) );
  result->basic = 0;
  result->transformation =0;
  result->transConfirm =0;
  result->n =0;
  return result;
}

// ===========================================================================

AlphabetTransform* freeAlphabetTransform(AlphabetTransform* at) {
  if (at==0) {
    return 0;
  }

  free(at->basic);
  free(at->transformation);
  free(at->transConfirm);

  free(at);

  return 0;
}

// ===========================================================================

int loadAlphabetFile(const char* filename, AlphabetTransform* at) {
  FILE* fp;
  int result =0;

  // printf("Starting read alphabet file %s \n", filename);

  fp = fopen(filename, "r");
  if (fp == NULL) {
    // printf("Failed to read %s \n", filename);
    return ATEC_FAILED_READ_ALPHABET;
  }

  size_t len = 0;
  const int bufSize = 300;
  char* basicBuf = malloc(bufSize);
  char* tBuf = malloc(bufSize);
  char* tcBuf = malloc(bufSize);

  if (fgets(basicBuf, bufSize, fp) == NULL) {
    result = ATEC_FAILED_READ_ALPHABET;
  }

  if (!result) {
    if (fgets(tBuf, bufSize, fp) == NULL) {
      result = ATEC_FAILED_READ_ALPHABET;
    }
  }

  if (!result) {
    if (fgets(tcBuf, bufSize, fp) == NULL) {
      result = ATEC_FAILED_READ_ALPHABET;
    }
  }

  fclose(fp);

  if (!result) {
    int bl = strlen(basicBuf) ;
    int tl = strlen(tBuf);
    int tcl = strlen(tcBuf);

    if (basicBuf[bl-1]=='\n') {
      basicBuf[bl-1]='\0';
      bl--;
    }
    if (tBuf[tl-1]=='\n') {
      tBuf[tl-1]='\0';
      tl--;
    }
    if (tcBuf[tcl-1]=='\n') {
      tcBuf[tcl-1]='\0';
      tcl--;
    }

    if ( (bl==tl)&&(bl==tcl)&&(bl>0) ) {
      // printf("Got %u bytes each line\n", bl);
      len = bl ;
    }
    else {
      result = ATEC_ALPHABET_BAD_FORMAT;
    }
  }

  if (!result) {
    at->basic = realloc(at->basic, len+1);
    strcpy(at->basic, basicBuf );
    at->n = len;

    at->transformation = realloc(at->transformation, len+1);
    strcpy(at->transformation, tBuf );

    at->transConfirm = realloc(at->transConfirm, len+1);
    strcpy(at->transConfirm, tcBuf );
  }

  free(basicBuf) ;
  free(tBuf) ;
  free(tcBuf);

  return result;
}

// ===========================================================================

int findAlphabetPos(const char* row, const char sample) {
  const int rowLen = strlen(row);
  for(int i=0; i<rowLen; i++) {
    if (row[i]==sample){
      return i;
    }
  }
  return -1;
}

// ===========================================================================

char transformOneChar(const AlphabetTransform* at, const char symbol) {
  int basicPos = findAlphabetPos(at->basic, symbol);
  if (basicPos>=0) {
    return symbol;
  }

  int transPos = findAlphabetPos(at->transformation, symbol);
  if (transPos>=0) {
    if (at->transConfirm[transPos]=='^') {
      return at->basic[transPos];
    }
  }

  return '\0';
}

// ===========================================================================

void convertLine(const AlphabetTransform* at, char* line,
                 char* result, const int resultLimit) {
  //printf("Will convert line %s\n", line);
  const int lineLen = strlen(line);

  int ri=0;
  for(int i=0; i<lineLen; i++) {
    char tch = transformOneChar(at, line[i]);
    if (tch!='\0') {
      result[ri] = tch;
      ri++;
      if (ri>=resultLimit) {
        result[ri-1] = '\0';
        return;
      }
    }
  }

  result[ri] = '\0';
}

// ===========================================================================
